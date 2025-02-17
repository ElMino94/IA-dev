#include "Entity.hpp"

Entity::Entity(float x, float y) {
    shape.setSize({ 35, 35 });
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}
