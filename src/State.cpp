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


#include <State.hpp>
#include <Game.hpp>
#include <SFML/Window/Event.hpp>


State::State(Game *game) noexcept
    : mGame(game)
{
    if(mGame != nullptr)
    {
        mWinSize = {mGame->mWidth, mGame->mHeight};
        mFont = &mGame->mFont;
    }
}


void State::manageEvent(sf::RenderWindow& w) noexcept
{
    sf::Event ev;
    while(w.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
            quitEvent(w);

        if(ev.type == sf::Event::KeyPressed)
            keyPressEvent(ev.key);
        else if(ev.type == sf::Event::MouseButtonPressed)
            mouseClickEvent(ev.mouseButton);
    }
}


sf::Vector2u State::getWinSize() const noexcept
{
    return mWinSize;
}


sf::Font* State::getFont() const noexcept
{
    return mFont;
}



sf::Texture* State::getTexture(GameTextures gameTexture) const noexcept
{
    return mGame->mTextures[gameTexture].get();
}



void State::quitEvent(sf::RenderWindow &w) noexcept
{
    w.close();
}
