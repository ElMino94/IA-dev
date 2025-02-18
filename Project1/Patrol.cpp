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

void Patrol::update(float deltaTime, Grid& grid, Vector2f playerPos) {
    playerPosition = playerPos;

    Vector2f diff = playerPosition - getPosition();
    float distanceToPlayer = sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distanceToPlayer < detectionRadius && canSeePlayer(grid)) {
        state = PatrolState::CHASING;
    }
    else if (state == PatrolState::CHASING && distanceToPlayer > detectionRadius * 1.2f) {
        state = PatrolState::PATROLLING;
    }

    if (state == PatrolState::CHASING) {
        chasePlayer(deltaTime);
    }
    else {
        patrol(deltaTime);
    }
}

void Patrol::chasePlayer(float deltaTime) {
    Vector2f direction = playerPosition - getPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 5.0f) {
        direction /= distance;
        Vector2f newPosition = getPosition() + direction * SPEED * deltaTime;
        setPosition(newPosition);
    }
}

void Patrol::patrol(float deltaTime) {
    if (waypoints.empty()) return;

    Vector2f currentPos = getPosition();
    Vector2f target = waypoints[currentWaypointIndex];
    Vector2f direction = target - currentPos;
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
