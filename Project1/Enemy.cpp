#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y) {}

void Enemy::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {

}

void Enemy::check_collision(const Entity& player) {

    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        shape.setFillColor(sf::Color::Green); 
    }
    else {
        shape.setFillColor(sf::Color::Red); 
    }
}
