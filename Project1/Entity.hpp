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

    Entity(float x, float y);
    virtual void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) = 0;
};

#endif // ENTITY_HPP