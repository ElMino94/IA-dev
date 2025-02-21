#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"
#include "Grid.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);
    void update(float deltaTime, Grid& grid, Vector2f playerPosition) override;
    void check_collision(const Entity& player); 
};

#endif 
