#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Entity.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"

class Hunter : public Entity {
public:
    Hunter(float x, float y);

    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) override;
    void draw(sf::RenderWindow& window);

private:
    float speed = 100.0f; 
    std::vector<sf::Vector2i> path;
    int pathIndex = 0;
    sf::Clock moveClock;
    bool needsRepath = false;
    sf::Vector2i lastPathNode; 
};

#endif
