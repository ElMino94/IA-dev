#ifndef BOOSTPAD_HPP
#define BOOSTPAD_HPP

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class BoostPad {
public:
    BoostPad(float x, float y);
    void draw(sf::RenderWindow& window) const;
    bool checkCollision(const sf::RectangleShape& playerShape) const;

    sf::RectangleShape shape;
};

#endif // BOOSTPAD_HPP
