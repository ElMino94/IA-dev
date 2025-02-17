#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

using namespace sf;
using namespace std;

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);
    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) override;
    void check_collision(const Entity& player); 
};

#endif // ENEMY_HPP
