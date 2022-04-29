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


#ifndef GAME_HPP
#define GAME_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <State.hpp>
#include <memory>
#include <map>







class Game
{
    friend State;
    static constexpr const char* mGameTitle {"SFML-Snake"};


    std::unique_ptr<sf::RenderWindow> mWindow;
    sf::Font mFont;
    unsigned int mWidth;
    unsigned int mHeight;
    int mScore;

    std::map<StateCode, std::unique_ptr<State>> mStates;
    State* mCurrentState;
    StateCode mCurrentStateCode;



    std::map<GameTextures, std::unique_ptr<sf::Texture>> mTextures;

public:
    explicit Game(unsigned int width, unsigned int height) noexcept;
    ~Game() noexcept = default;

    bool start() noexcept;


private:
    void exec() noexcept;
    void eventLoop() noexcept;
    void gameLoop() noexcept;
    void StateCodeManagement() noexcept;
    void drawScore() noexcept;
};


#endif // GAME_HPP
