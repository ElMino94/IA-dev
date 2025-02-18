#include "Entity.hpp"

Entity::Entity(float x, float y) {
    shape.setSize({ 35, 35 });
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}

Vector2f Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Vector2f& pos) {
    position = pos;
    shape.setPosition(position);
}
