#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;	

enum class NodeState {
	SUCCESS,
	FAILURE,
	RUNNING
};

class BTNode {
public:
	virtual ~BTNode() = default;	
	virtual NodeState execute() = 0;
};

class BlackBoard {
private:
	unordered_map<string, int> data;
public:
	void setValue(const string& key, int value);
	int getValue(const string& key);
};

class SequenceNode : public BTNode {
private:
	vector<unique_ptr<BTNode>> children;
public:
	void AddChild(unique_ptr<BTNode> child);
	NodeState execute() override;
};

class SelectorNode : public BTNode {
private:
	vector<unique_ptr<BTNode>> children;
public:
	void AddChild(unique_ptr<BTNode> child);
	NodeState execute() override;
};

class ConditionNode : public BTNode {
private:
	BlackBoard& blackboard;
	string key;
	/*int expectedValue;*/
	int thresthold;
public:
	ConditionNode(BlackBoard& bb, const string& key, int value);
	NodeState execute() override;
};

class ActionNode : public BTNode {
private:
	string actionName;
	function<void()> action;
public:
	ActionNode(string name, function<void()> act);

	NodeState execute() override;
};