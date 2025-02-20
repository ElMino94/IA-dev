#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Enemy.hpp"
#include "Grid.hpp"
#include "Pathfinding.hpp"


class Hunter : public Entity {
public:
    Hunter(float x, float y);

    bool hasLineOfSight(const Vector2f& start, const Vector2f& end, const Grid& grid);

    void update(float deltaTime, Grid& grid, Vector2f playerPosition) override;
    void draw(RenderWindow& window);
    void check_collision(const Entity& player);
private:
    float speed = 100.0f; 
    vector<Vector2i> path;
    int pathIndex = 0;
    Clock moveClock;
    bool needsRepath = false;
    Vector2i last_Path_Node; 
    Vector2f last_Position;
};

#endif
