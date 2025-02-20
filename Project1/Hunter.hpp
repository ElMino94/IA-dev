#ifndef HUNTER_HPP
#define HUNTER_HPP

#include "Enemy.hpp"
#include "Pathfinding.hpp"

class Hunter : public Entity {
public:
    Hunter(float x, float y);

    bool has_Line_Of_Sight(const Vector2f& start, const Vector2f& end, const Grid& grid);

    void update(float deltaTime, Grid& grid, Vector2f playerPosition) override;
    void draw(RenderWindow& window);
    void check_collision(const Entity& player);

private:
    float speed = 100.0f; 
    int path_Index = 0;
    bool needs_Repath = false;
    Clock move_Clock;
    vector<Vector2i> path;
    Vector2i last_Path_Node; 
    Vector2f last_Position;
};

#endif
