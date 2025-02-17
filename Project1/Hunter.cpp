#include "Hunter.hpp"

Hunter::Hunter(float x, float y, sf::Color color) : Entity(x, y, color) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(color);
}

void Hunter::update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) {
    // Calculer le vecteur directionnel vers le joueur
    sf::Vector2f direction = playerPosition - shape.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    // Normaliser le vecteur directionnel
    if (length != 0) {
        direction /= length;
    }

    // Mettre a jour la position du hunter
    shape.move(direction * speed * deltaTime);
}