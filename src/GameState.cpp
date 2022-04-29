/* MIT License
 *
 * Copyright (c) 2022 Enyklace
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <GameState.hpp>
#include <LostState.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Game.hpp>


GameState::GameState(Game *game) : State(game)
{
    mHeadTexture = getTexture(GameTextures::head);
    mSnake = std::make_unique<Snake>(mHeadTexture);

    mFoodTexture = getTexture(GameTextures::food);
    mFoods.push_back(Food(mFoodTexture));
    mFoods.front().update(mRandom.getRandomCoord(getWinSize()));

    mWallTexture = getTexture(GameTextures::wall);
    drawWalls();

    mPauseText.setCharacterSize(64);
    mPauseText.setString("Pause");
    mPauseText.setFont(*getFont());
    mPauseText.setFillColor(sf::Color::White);
    mPauseText.setPosition(getWinSize().x / 2 - mPauseText.getGlobalBounds().width / 2,
                           getWinSize().y / 2);
}


void GameState::draw(sf::RenderWindow& w) noexcept
{
    for(const Food& f : mFoods)
    {
        w.draw(f);
    }

    for(const auto& wa : mWalls)
    {
        w.draw(wa);
    }

    w.draw(*mSnake);

    if(mPause)
    {
        w.draw(mPauseText);
    }
}


StateCode GameState::update(int interval) noexcept
{
    if(!mPause)
    {
        if(mClock.getElapsedTime() > sf::milliseconds(interval))
        {
            mSnake->update();

            mClock.restart();

            if(mSnake->checkCollision())
                return StateCode::LoseGame;

            for(Wall& w : mWalls)
            {
                if(mSnake->getCollider().checkCollision(w.getCollider()))
                {
                    return StateCode::LoseGame;
                }
            }

            for(Food& f : mFoods)
            {
                auto& tails {mSnake->getTail()};
                for(const auto& t : tails)
                {
                    if(f.getCollider().checkCollision(t.getCollider())){
                        f.update(mRandom.getRandomCoord(getWinSize()));
                       }
                }

                if(mSnake->getCollider().checkCollision(f.getCollider()))
                {
                    f.update(mRandom.getRandomCoord(getWinSize()));
                    mSnake->growTail();
                    return StateCode::IncScore;
                }

            }
        }
    }


    return StateCode::Nothing;
}


void GameState::keyPressEvent(const sf::Event::KeyEvent &ev)
{
    switch(ev.code)
    {
    case sf::Keyboard::Up:
        if(mSnake->getDirection() != Direction::Down)
            mSnake->setDirection(Direction::Up);
        break;
    case sf::Keyboard::Right:
        if(mSnake->getDirection() != Direction::Left)
            mSnake->setDirection(Direction::Right);
        break;
    case sf::Keyboard::Down:
        if(mSnake->getDirection() != Direction::Up)
            mSnake->setDirection(Direction::Down);
        break;
    case sf::Keyboard::Left:
        if(mSnake->getDirection() != Direction::Right)
            mSnake->setDirection(Direction::Left);
        break;
    case sf::Keyboard::Space:
        mPause = mPause ? false : true;
        break;

    default: ;
    }
}


void GameState::drawWalls() noexcept
{
	auto s {Entity::boxSize};
    auto w {getWinSize().x / s};
    auto h {getWinSize().y / s};

    for(auto i {0}; i < w; ++i)
    {
        for(auto j {0}; j < h; ++j)
        {
            Wall wa {mWallTexture};
            wa.setPosition(i * s, j * s);

            if((j == 0 || j == h-1) || (i == 0) || (i == w-1))
                mWalls.push_back(std::move(wa));
        }
    }
}
