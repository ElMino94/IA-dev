#pragma once

#include "Enemy.hpp"
#include "Grid.hpp"
#include "BehaviorTree.hpp"
#include <vector>
#include <memory>

using namespace sf;
using namespace std;



class Patrol : public Enemy {
private:
	
	vector<Vector2f> waypoints;
	int currentWaypointIndex = 0;
	float detectionRadius = 100.0f;
	Vector2f playerPosition;

public:
	Patrol(float x, float y);

	void update(float deltaTime, Grid& grid, Vector2f playerPos);
	void setWaypoints(const vector<Vector2f>& newWaypoints);
	
};