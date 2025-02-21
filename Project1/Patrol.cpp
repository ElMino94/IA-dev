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

    std::cout << "Distance en cases: " << distanceInCells << std::endl;
    std::cout << "Joueur d�tect�: " << playerDetected << std::endl;

    // V�rifier l'�tat actuel du Patrol
    switch (currentState) {
    case PATROLLING:
        shape.setFillColor(Color::Blue); // Bleu = mode patrouille
        patrol(deltaTime);

        if (distanceInCells <= 2.0f && playerDetected) {
            currentState = CHASING;  // Si le joueur est d�tect�, passer en mode CHASING
            lastPlayerPosition = playerPosition;
            cooldownTimer = 1.0f;  // Ajout d'un cooldown avant de passer � SEARCHING ou CHASING
        }
        break;

    case CHASING:
        shape.setFillColor(Color::Red); // Rouge = poursuite
        chase(playerPosition, deltaTime);

        if (distanceInCells > 2.0f || !playerDetected) {  // Si on perd le joueur, passer en mode SEARCHING
            currentState = SEARCHING;
            searchTime = 0.0f;
            cooldownTimer = 1.0f;  // Ajout d'un cooldown pour �viter le basculement trop rapide entre �tats
        }
        break;

    case SEARCHING:
        shape.setFillColor(Color::Yellow); // Jaune = recherche
        searchTime += deltaTime;
        search(deltaTime);

        if (playerDetected) {
            currentState = CHASING; // Si le joueur est retrouv�, passer � CHASING
            lastPlayerPosition = playerPosition;
            cooldownTimer = 1.0f;  // Ajout d'un cooldown avant de changer d'�tat
        }
        else if (searchTime >= maxSearchTime) {
            currentState = PATROLLING; // Apr�s un certain temps sans trouver, revenir � la patrouille
            cooldownTimer = 1.0f;  // Ajout d'un cooldown avant de revenir en PATROLLING
        }
        break;
    }
}




void Patrol::patrol(float deltaTime) {
    if (waypoints.empty()) return;

    // R�cup�rer le waypoint actuel (en coordonn�es en pixels)
    Vector2f target = waypoints[currentWaypointIndex];

    // Calculer la direction et la distance pour se d�placer vers le waypoint
    Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Si la distance est sup�rieure � un seuil, on se d�place vers le waypoint
    if (distance > 1.0f) {
        direction /= distance;
        position += direction * SPEED * deltaTime;
    }
    else {
        // Si on atteint le waypoint, passer au suivant
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

    // V�rifier si le joueur est dans le rayon de d�tection
    if (distance <= detectionRadius) {
        // V�rification de la ligne de vue avec la grille
        int patrolX = static_cast<int>(position.x / CELL_SIZE);
        int patrolY = static_cast<int>(position.y / CELL_SIZE);
        int playerX = static_cast<int>(playerPos.x / CELL_SIZE);
        int playerY = static_cast<int>(playerPos.y / CELL_SIZE);

        // Algorithme de parcours de ligne (similaire � Bresenham)
        int deltaX = abs(playerX - patrolX);
        int deltaY = abs(playerY - patrolY);
        int stepX = (patrolX < playerX) ? 1 : -1;
        int stepY = (patrolY < playerY) ? 1 : -1;
        int error = deltaX - deltaY;

        int x = patrolX;
        int y = patrolY;

        while (x != playerX || y != playerY) {
            if (!grid.getCell(x, y).walkable) {
                // Si un obstacle est d�tect� entre le patrol et le joueur
                std::cout << "Obstacle d�tect� entre (" << patrolX << ", " << patrolY << ") et (" << playerX << ", " << playerY << ")" << std::endl;
                return false;
            }

            int e2 = 2 * error;
            if (e2 > -deltaY) { error -= deltaY; x += stepX; }
            if (e2 < deltaX) { error += deltaX; y += stepY; }
        }

        // Si la distance est suffisante et que la ligne de vue est d�gag�e
        std::cout << "Joueur d�tect� dans le rayon et en ligne de vue (" << patrolX << ", " << patrolY << ") -> (" << playerX << ", " << playerY << ")" << std::endl;
        return true;
    }

    // Si la distance est trop grande, ne pas d�tecter le joueur
    return false;
}


void Patrol::setWaypoints(const std::vector<sf::Vector2i>& points) {
    waypoints.clear(); // Vide le vecteur des waypoints

    // Conversion des indices de grille en positions en pixels (Vector2f)
    for (const auto& point : points) {
        waypoints.push_back(sf::Vector2f(point.x * CELL_SIZE, point.y * CELL_SIZE));
    }

    if (!waypoints.empty()) {
        position = waypoints[0]; // Initialisation de la position � la premi�re case
    }
}
