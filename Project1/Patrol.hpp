#ifndef PATROL_HPP
#define PATROL_HPP

#include "Enemy.hpp"
#include <vector>
#include <iostream>


class Patrol : public Enemy {
public:
    enum State { PATROLLING, CHASING, SEARCHING };

protected:
    State currentState;
    vector<Vector2f> waypoints;
    int currentWaypointIndex = 0;
	float speed = 100.0f;
    float detectionRadius;
    CircleShape detectionCircle;
    Vector2f lastPlayerPosition;
    float searchTime;
    const float maxSearchTime = 3.0f; // Temps de recherche max avant de reprendre la patrouille
    bool isPlayerDetected = false;
    float stateCooldown = 0.3f;  // Temps avant de pouvoir changer d'état à nouveau
    float cooldownTimer;
    
public:
    Patrol(float x, float y, float radius);
    void update(float deltaTime, Grid& grid, Vector2f playerPosition) override;
    void patrol(float deltaTime);
    void chase(Vector2f playerPos, float deltaTime);
    void search(float deltaTime);
    bool detectPlayer(const Grid& grid, Vector2f playerPos);
	void setWaypoints(const vector<Vector2i>& points);

	
};

#endif
