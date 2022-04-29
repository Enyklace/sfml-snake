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

#include "LostState.hpp"
#include <SFML/Graphics/Text.hpp>
#include <Game.hpp>


LostState::LostState(Game *game) : State(game)
{
    sf::Font* font {getFont()};
    auto windowSize {getWinSize()};

    sf::Text str1 {"You lost", *font};
    str1.setPosition(windowSize.x / 2 - str1.getLocalBounds().width / 2,
                     windowSize.y / 2);

    mTexts.push_back(std::move(str1));



    sf::Text str2 {"Press SPACE to play again", *font};
    str2.setPosition(windowSize.x / 2 - str2.getLocalBounds().width / 2,
                     windowSize.y / 2 + 50);

    mTexts.push_back(std::move(str2));
}


void LostState::draw(sf::RenderWindow &w) noexcept
{
    for(const auto& t : mTexts)
        w.draw(t);
}


StateCode LostState::update(int interval) noexcept
{
	return mNextState;
}


void LostState::keyPressEvent(const sf::Event::KeyEvent &ev)
{
	if(ev.code == sf::Keyboard::Space)
	{
        mNextState = StateCode::NewGame;
	}
}
