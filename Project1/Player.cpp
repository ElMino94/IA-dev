// player.cpp
#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(float x, float y) : Entity(x, y), speed(n_speed), boostDuration(0), isBoosted(false) {}

void Player::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    shape.setFillColor(sf::Color::Blue);
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) movement.y -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed * deltaTime;

    sf::Vector2f newPosition = shape.getPosition() + movement;
    sf::FloatRect newBounds(newPosition, shape.getSize());

    if (isBoosted) {
        boostDuration -= deltaTime;
        if (boostDuration <= 0) {
            resetBoost(); 
        }
    }

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    if (isWalkable(newBounds.left, newBounds.top) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
        isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
        isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1)) {
        shape.move(movement);
    }
}

void Player::activateBoost(float duration) {
    isBoosted = true;
    boostDuration = duration;
    speed = b_speed;
}

void Player::resetBoost() {
    isBoosted = false;
    speed = n_speed;
}