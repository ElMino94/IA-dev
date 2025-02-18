#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Enemy.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"

class Hunter : public Entity {
public:
    Hunter(float x, float y);

    bool hasLineOfSight(const sf::Vector2f& start, const sf::Vector2f& end, const Grid& grid);

    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) override;
    void draw(sf::RenderWindow& window);
    void check_collision(const Entity& player);

private:
    float speed = 100.0f; 
    std::vector<sf::Vector2i> path;
    int pathIndex = 0;
    sf::Clock moveClock;
    bool needsRepath = false;
    sf::Vector2i last_Path_Node; 
    sf::Vector2f last_Position;
};

#endif
