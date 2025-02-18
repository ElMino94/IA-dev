#include "Hunter.hpp"

Hunter::Hunter(float x, float y) : Entity(x, y), last_Path_Node(0, 0), last_Position(-1.f, -1.f) {}


bool Hunter::hasLineOfSight(const sf::Vector2f& start, const sf::Vector2f& end, const Grid& grid) {
    sf::Vector2f direction = end - start;
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length == 0) return true; 
    direction /= length;
    const float paddingDistance = 10.0f; 

    for (float distance = paddingDistance; distance < length; distance += CELL_SIZE) {
        sf::Vector2f checkPosition = start + direction * distance;
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

void Hunter::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    if (hasLineOfSight(shape.getPosition(), playerPosition, grid)) {
        last_Position = playerPosition;

        if (needsRepath || path.empty()) {
            sf::Vector2i start;

            if (last_Path_Node != sf::Vector2i(0, 0)) {
                start = last_Path_Node;
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
    }
    else {
        if (needsRepath || path.empty()) {
            if (last_Position != sf::Vector2f(-1.f, -1.f)) { 
                sf::Vector2i start;

                if (last_Path_Node != sf::Vector2i(0, 0)) {
                    start = last_Path_Node;
                }
                else {
                    start = sf::Vector2i(static_cast<int>(shape.getPosition().x / CELL_SIZE),
                        static_cast<int>(shape.getPosition().y / CELL_SIZE));
                }

                sf::Vector2i end(static_cast<int>(last_Position.x / CELL_SIZE),
                    static_cast<int>(last_Position.y / CELL_SIZE));

                path = Pathfinding::findPath(grid, start, end);
                pathIndex = 1;
                needsRepath = false;
            }
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
            last_Path_Node = currentTargetNode;
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

void Hunter::check_collision(const Entity& player)
{
    if (shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
        shape.setFillColor(sf::Color::Green);
    }
    else {
        shape.setFillColor(sf::Color::Red);
    }
}
