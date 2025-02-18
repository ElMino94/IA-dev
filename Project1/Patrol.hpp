#pragma once

#include "Enemy.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Patrol : public Enemy {
protected:
	vector<Vector2f> waypoints;

	int currentWaypointIndex = 0;
public:
	Patrol(float x, float y);

	void update(float deltaTime, Grid& grid);
	void setWaypoints(const vector<Vector2f>& newWaypoints);
};