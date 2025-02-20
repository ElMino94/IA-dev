#ifndef NODE_H
#define NODE_H

#include <SFML/System/Vector2.hpp>

using namespace std;
using namespace sf;

struct Node {
    Vector2i position;
    int gCost, hCost, fCost;
    Node* parent;

    Node(Vector2i pos);
    void calculateCosts(Node* end, int newG);
};

#endif