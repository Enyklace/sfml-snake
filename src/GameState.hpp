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

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <State.hpp>
#include <Random.hpp>
#include <Snake.hpp>
#include <Food.hpp>
#include <Wall.hpp>

#include <SFML/Graphics/Text.hpp>
#include <string>

using namespace std::string_literals;

class GameState : public State
{
    using Direction = Snake::Direction;

    std::unique_ptr<Snake> mSnake;
    sf::Texture* mHeadTexture;
    Direction mDirection;

    std::vector<Food> mFoods;
    sf::Texture* mFoodTexture;

    std::vector<Wall> mWalls;
    sf::Texture* mWallTexture;

    sf::Clock mClock;
    Random mRandom;

    bool mPause {false};
    sf::Text mPauseText;

public:
    explicit GameState(Game* game = nullptr);

    void draw(sf::RenderWindow& w) noexcept override;
    StateCode update(int interval = 0) noexcept override;


protected:
    void keyPressEvent(const sf::Event::KeyEvent& ev) override;


private:
    void drawWalls() noexcept;
};

#endif // GAMESTATE_HPP
