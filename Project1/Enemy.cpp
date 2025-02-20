#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y) {}

void Enemy::update(float deltaTime, Grid& grid, Vector2f playerPosition) {

}

void Enemy::check_collision(const Entity& player) {

    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        shape.setFillColor(Color::Green); 
    }
    else {
        shape.setFillColor(Color::Red); 
    }
}
