#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

using namespace sf;
using namespace std;

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Entity(float x, float y, sf::Color color);
    virtual void update(float deltaTime, Grid& grid) = 0;
};

#endif // ENTITY_HPP