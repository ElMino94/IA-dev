#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Entity {
protected:
	Vector2f position;

public:
    RectangleShape shape;
    Vector2f velocity;

    Entity(float x, float y);
    virtual void update(float deltaTime, Grid& grid, Vector2f playerPosition) = 0;
	Vector2f getPosition() const;
	void setPosition(const Vector2f& pos); 
};

#endif 