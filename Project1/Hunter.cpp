#include "Hunter.hpp"
#include <cmath>
#include <SFML/Graphics.hpp>

Hunter::Hunter(float x, float y) : Entity(x, y) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Red);
}

void Hunter::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {

    sf::Vector2f direction = playerPosition - shape.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
    }

    if (isPathClear(shape.getPosition(), playerPosition, grid)) {
        shape.move(direction * speed * deltaTime);
    }
    else {

    }
}

bool Hunter::isPathClear(sf::Vector2f start, sf::Vector2f end, Grid& grid) {
    sf::Vector2f direction = end - start;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; 

    float stepSize = 5.f; 
    for (float t = 0; t < length; t += stepSize) {
        sf::Vector2f point = start + direction * t;
        int gridX = static_cast<int>(point.x / CELL_SIZE);
        int gridY = static_cast<int>(point.y / CELL_SIZE);

        if (gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT) {
            if (!grid.getCell(gridX, gridY).walkable) {
                return false; 
            }
        }
    }
    return true; 
}
