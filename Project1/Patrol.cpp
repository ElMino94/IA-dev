#include "Patrol.hpp"
#include <iostream>

Patrol::Patrol(float x, float y) : Enemy(x, y) {
    shape.setFillColor(Color::Green);
    setPosition(Vector2f(x, y));
}

void Patrol::setWaypoints(const vector<Vector2f>& newWaypoints) {
    waypoints = newWaypoints;
    currentWaypointIndex = 0;
}

void Patrol::update(float deltaTime, Grid& grid) {
    if (waypoints.empty()) return;

    Vector2f currentPos = getPosition();
    Vector2f target = waypoints[currentWaypointIndex];
    Vector2f direction = target - shape.getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 5.0f) {
        direction /= distance;
        Vector2f newPosition = currentPos + direction * SPEED * deltaTime;
        setPosition(newPosition);

    }
    else {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size();
    }
}