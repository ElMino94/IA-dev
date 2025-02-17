#pragma once 

#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Entity.hpp"
#include "Grid.hpp"

class Hunter : public Entity {
public:
    Hunter(float x, float y, sf::Color color);

    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition);

private:
    float speed = 100.0f; // Vitesse du hunter
};

#endif // HUNTER_HPP