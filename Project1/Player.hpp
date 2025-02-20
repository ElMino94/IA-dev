#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    static constexpr float n_speed = 200.0f;
    static constexpr float b_speed = 350.0f;
    Player(float x, float y);
    void update(float deltaTime, Grid& grid, sf::Vector2f playerPosition) override;
    void activateBoost(float duration); 
    void resetBoost();  

private:
    float speed;
    float boostDuration;
    bool isBoosted;
};

#endif 
