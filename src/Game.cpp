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


#include "Game.hpp"
#include <State.hpp>
#include <GameState.hpp>
#include <LostState.hpp>
#include <SFML/Graphics/Text.hpp>



Game::Game(unsigned int width, unsigned int height) noexcept
    : mWidth {width}
    , mHeight {height}
    , mScore {0}
{
    mFont.loadFromFile("../ressources/arial.ttf");

    mTextures[GameTextures::head] = std::make_unique<sf::Texture>();
    mTextures[GameTextures::head]->loadFromFile("../ressources/head.png");
    mTextures[GameTextures::tail] = std::make_unique<sf::Texture>();
    mTextures[GameTextures::tail]->loadFromFile("../ressources/tail.png");
    mTextures[GameTextures::food] = std::make_unique<sf::Texture>();
    mTextures[GameTextures::food]->loadFromFile("../ressources/food.png");
    mTextures[GameTextures::wall] = std::make_unique<sf::Texture>();
    mTextures[GameTextures::wall]->loadFromFile("../ressources/wall.png");

    mStates[StateCode::NewGame] = std::make_unique<GameState>(this);
    mStates[StateCode::LoseGame] = std::make_unique<LostState>(this);

    mCurrentState = mStates[StateCode::NewGame].get();
}



bool Game::start() noexcept
{
    mWindow = std::make_unique<sf::RenderWindow>();
    mWindow->create(sf::VideoMode(mWidth, mHeight), mGameTitle, sf::Style::Default);
    mWindow->setVerticalSyncEnabled(true);

    exec();

    return 0;
}



void Game::exec() noexcept
{
    while(mWindow->isOpen())
    {
        mWindow->clear();

        eventLoop();
        gameLoop();
        StateCodeManagement();

        mWindow->display();
    }
}



void Game::eventLoop() noexcept
{
    mCurrentState->manageEvent(*mWindow);
}



void Game::gameLoop() noexcept
{
    mCurrentState->draw(*mWindow);
    mCurrentStateCode = mCurrentState->update(90);
    drawScore();
}



void Game::StateCodeManagement() noexcept
{
    switch(mCurrentStateCode)
    {
    case StateCode::Nothing:
        break;
    case StateCode::IncScore:
        ++mScore;
        break;
    case StateCode::NewGame:
        mScore = 0;
        mStates[StateCode::NewGame] = std::make_unique<GameState>(this);
        mCurrentState = mStates[mCurrentStateCode].get();
        break;
    case StateCode::LoseGame:
        mStates[StateCode::LoseGame] = std::make_unique<LostState>(this);
        mCurrentState = mStates[mCurrentStateCode].get();
        break;
    }
}



void Game::drawScore() noexcept
{
    std::string strscore {"Score : "};
    strscore += std::to_string(mScore);
    sf::Text scoreText {strscore, mFont};

    scoreText.setPosition(mWidth / 2 - scoreText.getLocalBounds().width / 2, 32);
    scoreText.setFillColor(sf::Color(255, 255, 168, 210));

    mWindow->draw(scoreText);
}
