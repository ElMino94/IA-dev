#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}

void Enemy::update(float deltaTime, Grid& grid) {

}

void Enemy::check_collision(const Entity& player) {

    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        shape.setFillColor(sf::Color::Green); 
    }
    else {
        shape.setFillColor(sf::Color::Red); 
    }
}
