#include "Hunter.hpp"

Hunter::Hunter(float x, float y) : Entity(x, y), lastPathNode(-1, -1) {}

void Hunter::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    if (needsRepath || path.empty()) {
        sf::Vector2i start;

        if (lastPathNode != sf::Vector2i(-1, -1)) {
            start = lastPathNode;
        }
        else {
            start = sf::Vector2i(static_cast<int>(shape.getPosition().x / CELL_SIZE),
                static_cast<int>(shape.getPosition().y / CELL_SIZE));
        }

        sf::Vector2i end(static_cast<int>(playerPosition.x / CELL_SIZE),
            static_cast<int>(playerPosition.y / CELL_SIZE));

        path = Pathfinding::findPath(grid, start, end);
        pathIndex = 1;
        needsRepath = false;
    }

    if (!path.empty() && pathIndex < path.size()) {
        sf::Vector2i currentTargetNode = path[pathIndex];
        sf::Vector2f targetPosition(currentTargetNode.x * CELL_SIZE, currentTargetNode.y * CELL_SIZE);
        sf::Vector2f direction = targetPosition - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }

        sf::Vector2f nextPosition = shape.getPosition() + direction * speed * deltaTime;
        setPosition(nextPosition);

        if (length < 5.f) {
            lastPathNode = currentTargetNode;
            needsRepath = true;
        }
    }

    if (pathIndex >= path.size()) {
        needsRepath = true;
    }
}

void Hunter::draw(sf::RenderWindow& window) {
    window.draw(shape);
}
