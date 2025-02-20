#pragma once

#include "Enemy.hpp"
#include "BehaviorTree.hpp"
#include <vector>
#include <memory>

class Patrol : public Enemy {
private:
	vector<Vector2f> waypoints;
	int currentWaypointIndex = 0;
	Vector2f playerPosition;
	BlackBoard blackboard;
	unique_ptr<BTNode> behaviorTree;
	
public:
	static const float SPEED;
	static const float DETECTION_RADIUS;

	Patrol(float x, float y);

	void setWaypoints(const vector<Vector2f>& newWaypoints);
	void update(float deltaTime, Grid& grid, Vector2f playerPos);
	void chasePlayer(float deltaTime);
	void patrol(float deltaTime);

	void buildBehaviorTree();
};