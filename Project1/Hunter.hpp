#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Entity.hpp"
#include "Grid.hpp"

class Hunter : public Entity {
public:
    Hunter(float x, float y);

    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) override;
    bool isPathClear(sf::Vector2f start, sf::Vector2f end, Grid& grid);

private:
    float speed = 100.0f;
};

#endif // HUNTER_HPP
