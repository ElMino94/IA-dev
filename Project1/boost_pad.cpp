#include "boost_pad.hpp"

BoostPad::BoostPad(float x, float y) {
    shape.setSize({ 30, 30 });  
    shape.setPosition(x, y);  
    shape.setFillColor(sf::Color::Yellow); 
}

void BoostPad::draw(sf::RenderWindow& window) const {
    window.draw(shape);  
}

bool BoostPad::checkCollision(const sf::RectangleShape& playerShape) const {
    return shape.getGlobalBounds().intersects(playerShape.getGlobalBounds());  
}
