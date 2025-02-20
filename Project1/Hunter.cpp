#include "Hunter.hpp"

Hunter::Hunter(float x, float y) : Entity(x, y), last_Path_Node(0, 0), last_Position(-1.f, -1.f) {}

bool Hunter::has_Line_Of_Sight(const Vector2f& start, const Vector2f& end, const Grid& grid) {

    Vector2f direction = end - start;

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length == 0) return true; 
    direction /= length;

    for (float distance = 10.0f; distance < length; distance += CELL_SIZE) {
        Vector2f check_Position = start + direction * distance;
        int x = static_cast<int>(check_Position.x / CELL_SIZE);
        int y = static_cast<int>(check_Position.y / CELL_SIZE);

        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
            if (!grid.getCell(x, y).walkable) {
                return false; 
            }
        }
    }

    return true; 
}

void Hunter::update(float deltaTime, Grid& grid, Vector2f player_Position) {

    if (has_Line_Of_Sight(shape.getPosition(), player_Position, grid)) {
        last_Position = player_Position;

        if (needs_Repath || path.empty()) {
            Vector2i start;

            if (last_Path_Node != Vector2i(0, 0)) {
                start = last_Path_Node;
            }
            else {
                start = Vector2i(static_cast<int>(shape.getPosition().x / CELL_SIZE),
                    static_cast<int>(shape.getPosition().y / CELL_SIZE));
            }
            Vector2i end(static_cast<int>(player_Position.x / CELL_SIZE), static_cast<int>(player_Position.y / CELL_SIZE));
            path = Pathfinding::findPath(grid, start, end);
            path_Index = 1;
            !needs_Repath;
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
        path_Index = 1;
        !needs_Repath;
    }

    if (!path.empty() && path_Index < path.size()) {
        Vector2i current_Target_Node = path[path_Index];
        Vector2f target_Position(current_Target_Node.x * CELL_SIZE, current_Target_Node.y * CELL_SIZE);
        Vector2f direction = target_Position - shape.getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }
        Vector2f next_Position = shape.getPosition() + direction * speed * deltaTime;
        setPosition(next_Position);

        if (length < 5.f) {
            last_Path_Node = current_Target_Node;
            needs_Repath;
        }
    }

    if (path_Index >= path.size()) needs_Repath;
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
