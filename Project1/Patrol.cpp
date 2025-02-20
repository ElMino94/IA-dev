#include "Patrol.hpp"
#include <cmath>
#include <iostream>

const float Patrol::SPEED = 100.0f;
const float Patrol::DETECTION_RADIUS = 150.0f;

Patrol::Patrol(float x, float y) : Enemy(x, y) {
    shape.setFillColor(Color::Green);
    setPosition(Vector2f(x, y));
	buildBehaviorTree();
}

void Patrol::setWaypoints(const vector<Vector2f>& newWaypoints) {
    waypoints = newWaypoints;
    currentWaypointIndex = 0;
}

void Patrol::update(float deltaTime, Grid& grid, Vector2f playerPos) {
    playerPosition = playerPos;

    Vector2f diff = playerPos - getPosition();
    float playerDistance = sqrt(diff.x * diff.x + diff.y * diff.y); // Nom modifié
    blackboard.setValue("distanceToPlayer", static_cast<int>(playerDistance));

	if (behaviorTree) {
		behaviorTree->execute();
	}    

	if (playerDistance > DETECTION_RADIUS) {
		blackboard.setValue("isChasing", 0);
		patrol(deltaTime);
	}
}

void Patrol::chasePlayer(float deltaTime) {
	Vector2f direction = playerPosition - getPosition();
	float playerDistance = sqrt(direction.x * direction.x + direction.y * direction.y); // Nom modifié
	
    if (playerDistance > 5.0f) {
        direction /= playerDistance;
		Vector2f newPosition = getPosition() + direction * SPEED * deltaTime;
		setPosition(newPosition);
    }
}

void Patrol::patrol(float deltaTime) {
	if (waypoints.empty()) return;

	Vector2f currentPos = getPosition();
	Vector2f target = waypoints[currentWaypointIndex];
	Vector2f direction = target - getPosition();
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

void Patrol::buildBehaviorTree() {
	auto root = make_unique<SelectorNode>();

	auto detectPlayer = make_unique<ConditionNode>(blackboard, "distanceToPlayer", DETECTION_RADIUS);
	auto chaseAction = make_unique<ActionNode>("Chase Player", [this]() {
		blackboard.setValue("isChasing", 1);
		chasePlayer(0.016f);
	});

	auto patrolAction = make_unique<ActionNode>("Patrol", [this]() {
		blackboard.setValue("isChasing", 0);
		patrol(0.016f);
		});

	auto chaseSequence = make_unique<SequenceNode>();
	chaseSequence->AddChild(move(detectPlayer));
	chaseSequence->AddChild(move(chaseAction));

	root->AddChild(move(chaseSequence));
	root->AddChild(move(patrolAction));

	behaviorTree = move(root);
}

