#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

using namespace sf;
using namespace std;

class Player : public Entity {
public:
    static constexpr float n_speed = 200.0f;
    static constexpr float b_speed = 350.0f;
    Player(float x, float y);
    void update(float deltaTime, Grid& grid) override;
    void activateBoost(float duration); 
    void resetBoost();  

private:
    float speed;
    float boostDuration;
    bool isBoosted;
};

#endif // PLAYER_HPP
