#include "BehaviorTree.hpp"

void BlackBoard::setValue(const std::string& key, int value) {
    data[key] = value;
}

int BlackBoard::getValue(const std::string& key) {
    return data[key];
}

NodeState SequenceNode::execute() {
    for (auto& child : children) {
        if (child->execute() == NodeState::FAILURE) {
            return NodeState::FAILURE;
        }
    }
    return NodeState::SUCCESS;
}

NodeState SelectorNode::execute() {
    for (auto& child : children) {
        if (child->execute() == NodeState::SUCCESS) {
            return NodeState::SUCCESS;
        }
    }
    return NodeState::FAILURE;
}

NodeState ConditionNode::execute() {
    return (blackboard.getValue(key) == expectedValue) ? NodeState::SUCCESS : NodeState::FAILURE;
}

NodeState ActionNode::execute() {
    std::cout << "Action: " << this->actionName << std::endl;
    this->action();
    return NodeState::SUCCESS;
}
