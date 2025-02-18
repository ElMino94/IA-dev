#include "Hunter.hpp"
#include <cmath>

Hunter::Hunter(float x, float y) : Entity(x, y), lastPathNode(0, 0) {}

void Hunter::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    auto isLineOfSightClear = [&](sf::Vector2f start, sf::Vector2f end) -> bool {
        int x1 = static_cast<int>(start.x / CELL_SIZE);
        int y1 = static_cast<int>(start.y / CELL_SIZE);
        int x2 = static_cast<int>(end.x / CELL_SIZE);
        int y2 = static_cast<int>(end.y / CELL_SIZE);
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (!grid.getCell(x1, y1).walkable) {
                return false;
            }
            if (x1 == x2 && y1 == y2) {
                break;
            }
            int e2 = err * 2;

            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
        }
        return true;
        };
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

        if (isLineOfSightClear(shape.getPosition(), playerPosition)) {
            path = Pathfinding::findPath(grid, start, end);
            pathIndex = 1;
            needsRepath = false;
        }
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
