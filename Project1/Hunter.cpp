#include "Hunter.hpp"

Hunter::Hunter(float x, float y) : Entity(x, y), last_Path_Node(0, 0), last_Position(-1.f, -1.f) {}

bool Hunter::hasLineOfSight(const Vector2f& start, const Vector2f& end, const Grid& grid) {
    Vector2f direction = end - start;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length == 0) return true; 
    direction /= length;

    for (float distance = 10.0f; distance < length; distance += CELL_SIZE) {
        Vector2f checkPosition = start + direction * distance;
        int x = static_cast<int>(checkPosition.x / CELL_SIZE);
        int y = static_cast<int>(checkPosition.y / CELL_SIZE);

        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            if (!grid.getCell(x, y).walkable) {
                return false; 
            }
        }
    }
    return true; 
}

void Hunter::update(float deltaTime, Grid& grid, Vector2f playerPosition) {
    if (hasLineOfSight(shape.getPosition(), playerPosition, grid)) {
        last_Position = playerPosition;

        if (needsRepath || path.empty()) {
            Vector2i start;

            if (last_Path_Node != Vector2i(0, 0)) {
                start = last_Path_Node;
            }
            else {
                start = Vector2i(static_cast<int>(shape.getPosition().x / CELL_SIZE),
                    static_cast<int>(shape.getPosition().y / CELL_SIZE));
            }
            Vector2i end(static_cast<int>(playerPosition.x / CELL_SIZE), static_cast<int>(playerPosition.y / CELL_SIZE));
            path = Pathfinding::findPath(grid, start, end);
            pathIndex = 1;
            needsRepath = false;
        }
    }
    if (last_Position != Vector2f(-1.f, -1.f)) {
        Vector2i start;

        if (last_Path_Node != Vector2i(0, 0)) {
            start = last_Path_Node;
        }
        else {
            start = Vector2i(static_cast<int>(shape.getPosition().x / CELL_SIZE), static_cast<int>(shape.getPosition().y / CELL_SIZE));
        }
        Vector2i end(static_cast<int>(last_Position.x / CELL_SIZE), static_cast<int>(last_Position.y / CELL_SIZE));
        path = Pathfinding::findPath(grid, start, end);
        pathIndex = 1;
        needsRepath = false;
    }
    if (!path.empty() && pathIndex < path.size()) {
        Vector2i currentTargetNode = path[pathIndex];
        Vector2f targetPosition(currentTargetNode.x * CELL_SIZE, currentTargetNode.y * CELL_SIZE);
        Vector2f direction = targetPosition - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }
        Vector2f nextPosition = shape.getPosition() + direction * speed * deltaTime;
        setPosition(nextPosition);

        if (length < 5.f) {
            last_Path_Node = currentTargetNode;
            needsRepath = true;
        }
    }
    if (pathIndex >= path.size()) {
        needsRepath = true;
    }
}

void Hunter::draw(RenderWindow& window) {
    window.draw(shape);
}

void Hunter::check_collision(const Entity& player)
{
    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        shape.setFillColor(Color::Green);
    }
    else {
        shape.setFillColor(Color::Red);
    }
}
