#pragma once

#include "Enemy.hpp"
#include <vector>

using namespace sf;
using namespace std;

enum class PatrolState {
	PATROLLING,
	CHASING
};

class Patrol : public Enemy {
private:
	/*PatrolState state = PatrolState::PATROLLING;*/
	vector<Vector2f> waypoints;
	int currentWaypointIndex = 0;
	float detectionRadius = 100.0f;
	Vector2f playerPosition;

public:
	Patrol(float x, float y);

	void update(float deltaTime, Grid& grid, Vector2f playerPos);
	void setWaypoints(const vector<Vector2f>& newWaypoints);
	/*void chasePlayer(float deltaTime);
	void patrol(float deltaTime);
	bool canSeePlayer(Grid& grid);*/
};