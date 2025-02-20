#include "boost_pad.hpp"

BoostPad::BoostPad(float x, float y) {
    shape.setSize({ 30, 30 });  
    shape.setPosition(x, y);  
    shape.setFillColor(Color::Yellow); 
}

void BoostPad::draw(RenderWindow& window) const {
    window.draw(shape);  
}

bool BoostPad::checkCollision(const RectangleShape& playerShape) const {
    return shape.getGlobalBounds().intersects(playerShape.getGlobalBounds());  
}
