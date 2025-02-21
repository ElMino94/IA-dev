#include "Patrol.hpp"
#include <cmath>

Patrol::Patrol(float x, float y, float radius) : Enemy(x, y), detectionRadius(radius), currentWaypointIndex(0), currentState(PATROLLING), searchTime(0.0f) {
    detectionCircle.setRadius(radius);
    detectionCircle.setOrigin(radius, radius);
    detectionCircle.setPosition(position);
    detectionCircle.setFillColor(Color(255, 0, 0, 100));
}

void Patrol::update(float deltaTime, Grid& grid, Vector2f playerPosition) {

    if (cooldownTimer > 0) {
        cooldownTimer -= deltaTime;
        return;
    }

    int dx = static_cast<int>(playerPosition.x / CELL_SIZE) - static_cast<int>(position.x / CELL_SIZE);
    int dy = static_cast<int>(playerPosition.y / CELL_SIZE) - static_cast<int>(position.y / CELL_SIZE);
    float distanceInCells = sqrt(dx * dx + dy * dy);

    bool playerDetected = detectPlayer(grid, playerPosition);

    switch (currentState) {
    case PATROLLING:
        shape.setFillColor(Color::Blue); 
        patrol(deltaTime);

        if (distanceInCells <= 2.0f && playerDetected) {
            currentState = CHASING;  
            lastPlayerPosition = playerPosition;
            cooldownTimer = 1.0f;  
        }
        break;

    case CHASING:
        shape.setFillColor(Color::Red); 
        chase(playerPosition, deltaTime);

        if (distanceInCells > 2.0f || !playerDetected) {  
            currentState = SEARCHING;
            searchTime = 0.0f;
            cooldownTimer = 1.0f;  
        }
        break;

    case SEARCHING:
        shape.setFillColor(Color::Yellow);
        searchTime += deltaTime;
        search(deltaTime);

        if (playerDetected) {
            currentState = CHASING; 
            lastPlayerPosition = playerPosition;
            cooldownTimer = 1.0f;  
        }
        else if (searchTime >= maxSearchTime) {
            currentState = PATROLLING; 
            cooldownTimer = 1.0f;  
        }
        break;
    }
}




void Patrol::patrol(float deltaTime) {
    if (waypoints.empty()) return;

    Vector2f target = waypoints[currentWaypointIndex];

    Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 1.0f) {
        direction /= distance;
        position += direction * SPEED * deltaTime;
    }
    else {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
    }

    shape.setPosition(position);
}


void Patrol::chase(Vector2f playerPos, float deltaTime) {
    Vector2f direction = playerPos - position;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > 1.0f) {
        direction /= length;
        position += direction * SPEED * deltaTime;
    }
    else {
        currentState = SEARCHING;
        searchTime = 0.0f;
    }

	shape.setPosition(position);
}

void Patrol::search(float deltaTime) {
    searchTime += deltaTime;
    if (searchTime >= maxSearchTime) {
        currentWaypointIndex = 0;
    }
}

bool Patrol::detectPlayer(const Grid& grid, Vector2f playerPos) {
    // Calcul de la distance entre le patrol et le joueur en pixels
    float dx = playerPos.x - position.x;
    float dy = playerPos.y - position.y;
    float distance = sqrt(dx * dx + dy * dy); // Distance en pixels

    // Vérifier si le joueur est dans le rayon de détection
    if (distance <= detectionRadius) {
        // Vérification de la ligne de vue avec la grille
        int patrolX = static_cast<int>(position.x / CELL_SIZE);
        int patrolY = static_cast<int>(position.y / CELL_SIZE);
        int playerX = static_cast<int>(playerPos.x / CELL_SIZE);
        int playerY = static_cast<int>(playerPos.y / CELL_SIZE);

        // Algorithme de parcours de ligne (similaire à Bresenham)
        int deltaX = abs(playerX - patrolX);
        int deltaY = abs(playerY - patrolY);
        int stepX = (patrolX < playerX) ? 1 : -1;
        int stepY = (patrolY < playerY) ? 1 : -1;
        int error = deltaX - deltaY;

        int x = patrolX;
        int y = patrolY;

        while (x != playerX || y != playerY) {
            if (!grid.getCell(x, y).walkable) {
                // Si un obstacle est détecté entre le patrol et le joueur
                std::cout << "Obstacle détecté entre (" << patrolX << ", " << patrolY << ") et (" << playerX << ", " << playerY << ")" << std::endl;
                return false;
            }

            int e2 = 2 * error;
            if (e2 > -deltaY) { error -= deltaY; x += stepX; }
            if (e2 < deltaX) { error += deltaX; y += stepY; }
        }

        // Si la distance est suffisante et que la ligne de vue est dégagée
        std::cout << "Joueur détecté dans le rayon et en ligne de vue (" << patrolX << ", " << patrolY << ") -> (" << playerX << ", " << playerY << ")" << std::endl;
        return true;
    }

    // Si la distance est trop grande, ne pas détecter le joueur
    return false;
}


void Patrol::setWaypoints(const std::vector<sf::Vector2i>& points) {
    waypoints.clear(); // Vide le vecteur des waypoints

    // Conversion des indices de grille en positions en pixels (Vector2f)
    for (const auto& point : points) {
        waypoints.push_back(sf::Vector2f(point.x * CELL_SIZE, point.y * CELL_SIZE));
    }

    if (!waypoints.empty()) {
        position = waypoints[0]; // Initialisation de la position à la première case
    }
}
