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

#include "Snake.hpp"
#include <SFML/Graphics/RectangleShape.hpp>


Snake::Snake(sf::Texture *texture, int size) noexcept
    : Entity(texture)
{

	setPosition(32, 32);

    mDirection = Direction::Right;

    mTailTexture.loadFromFile("../ressources/tail.png");

    for(size_t i{0}; i < size; ++i)
    {
        growTail();
    }
}


void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(getShape(), states);

    for(const auto& tail : mTails)
    {
        target.draw(tail);
    }
}


void Snake::update() noexcept
{
    if(!mTails.empty())
        updateTail();

    auto position {getPosition()};
    switch(mDirection)
    {
    case Direction::Up:
        position.y -= boxSize;
        break;
    case Direction::Right:
        position.x += boxSize;
        break;
    case Direction::Down:
        position.y += boxSize;
        break;
    case Direction::Left:
        position.x -= boxSize;
        break;
    }
    setPosition(position);
}


void Snake::updateTail() noexcept
{
    for(size_t i {mTails.size() - 1}; i > 0; --i)
    {
        auto p {mTails[i - 1].getPosition()};
        mTails[i].setPosition(p);
    }

    auto headPos {getPosition()};
    mTails[0].setPosition(headPos);
}


const std::vector<Tail>& Snake::getTail() const noexcept
{
    return mTails;
}


void Snake::growTail() noexcept
{
    Tail tl {&mTailTexture};
    tl.setPosition(getPosition());
    mTails.push_back(std::move(tl));
}


bool Snake::checkCollision() const noexcept
{
    for(const auto& t : mTails)
    {
        if(getCollider().checkCollision(t.getCollider()))
        {
            return 1;
        }
    }

    return 0;
}


void Snake::setDirection(Direction direction)
{
    mDirection = direction;
}


Snake::Direction Snake::getDirection() const noexcept
{
    return mDirection;
}
