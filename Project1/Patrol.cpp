#include "Patrol.hpp"
#include <cmath>
#include <iostream>

const float Patrol::SPEED = 100.0f;
const float Patrol::DETECTION_RADIUS = 150.0f;

Patrol::Patrol(float x, float y) : Enemy(x, y) {
    shape.setFillColor(Color::Green);
    setPosition(Vector2f(x, y));
}

void Patrol::setWaypoints(const vector<Vector2f>& newWaypoints) {
    waypoints = newWaypoints;
    currentWaypointIndex = 0;
}

void Patrol::update(float deltaTime, Grid& grid, Vector2f playerPos) {
    playerPosition = playerPos;

    Vector2f diff = playerPos - getPosition();
    float playerDistance = sqrt(diff.x * diff.x + diff.y * diff.y); // Nom modifié

    if (waypoints.empty()) return;

    Vector2f currentPos = getPosition();
    Vector2f target = waypoints[currentWaypointIndex];
    Vector2f direction = target - shape.getPosition();
    float waypointDistance = sqrt(direction.x * direction.x + direction.y * direction.y); // Nom modifié

    if (waypointDistance > 5.0f) {
        direction /= waypointDistance;
        Vector2f newPosition = currentPos + direction * SPEED * deltaTime;
        setPosition(newPosition);
    }
    else {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
    }
}

