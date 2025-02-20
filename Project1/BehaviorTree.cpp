#include "BehaviorTree.hpp"

void BlackBoard::setValue(const string& key, int value) {
    data[key] = value;
}

int BlackBoard::getValue(const string& key) {
    return data[key];
}

void SequenceNode::AddChild(unique_ptr<BTNode> child) {
	children.push_back(move(child));
}

NodeState SequenceNode::execute() {
    for (auto& child : children) {
        if (child->execute() == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}

void SelectorNode::AddChild(unique_ptr<BTNode> child) {
	children.push_back(move(child));
}

NodeState SelectorNode::execute() {
    for (auto& child : children) {
        if (child->execute() == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}

ConditionNode::ConditionNode(BlackBoard& bb, const string& key, int value) : blackboard(bb), key(key), thresthold(value) {}

NodeState ConditionNode::execute() {
	int value = blackboard.getValue(key);
    if (value > thresthold) {
		return NodeState::SUCCESS;
    }
    return NodeState::FAILURE;
}

ActionNode::ActionNode(string name, function<void()> action) : actionName(name), action(action) {}

NodeState ActionNode::execute() {
    cout << "Action: " << this->actionName << endl;
    this->action();
    return NodeState::SUCCESS;
}
