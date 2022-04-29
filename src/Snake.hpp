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

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Entity.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <Tail.hpp>


class Snake : public Entity
{
    std::vector<Tail> mTails;
    sf::Texture mTailTexture;

public:
    enum class Direction { Up, Right, Down, Left };
    Direction mDirection;

    explicit Snake(sf::Texture* texture, int size = 3) noexcept;

    const std::vector<Tail>& getTail() const noexcept;
    void growTail() noexcept;
    bool checkCollision() const noexcept;
    void setDirection(Direction direction);
    Direction getDirection() const noexcept;

    void update() noexcept;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateTail() noexcept;
};

#endif // SNAKE_HPP
