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

#include "Entity.hpp"
#include <SFML/Graphics/RectangleShape.hpp>


Entity::Entity(sf::Texture *texture)
{
	mShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(boxSize, boxSize));
    mShape->setTexture(texture);

    mCollider = std::make_unique<Collider>(*mShape);
}


sf::Shape &Entity::getShape() const noexcept
{
    return *mShape;
}


void Entity::setPosition(int x, int y) noexcept
{
    mShape->setPosition(x, y);
}


void Entity::setPosition(const sf::Vector2f& position) noexcept
{
    mShape->setPosition(position);
}


sf::Vector2f Entity::getPosition() const noexcept
{
    return mShape->getPosition();
}


Collider Entity::getCollider() const noexcept
{
    return *mCollider;
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(*mShape, state);
}
