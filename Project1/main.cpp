#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "boost_pad.hpp"  
#include "Hunter.hpp"
#include "Patrol.hpp"
#include "Grid.hpp"

const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400); 

    std::vector<Patrol> enemies; 
    std::vector<Hunter> hunters;
    std::vector<BoostPad> boostPads;

    Grid grid;
    grid.loadFromFile("map.txt"); 

    for (const auto& pos : grid.patrolPositions) {
        Patrol patrol(pos.x, pos.y, 100.0f); 

        std::vector<sf::Vector2i> patrolPattern = {
            {static_cast<int>(pos.x / CELL_SIZE), static_cast<int>((pos.y + 100) / CELL_SIZE)},
            {static_cast<int>((pos.x + 100) / CELL_SIZE), static_cast<int>((pos.y + 100) / CELL_SIZE)},
            {static_cast<int>((pos.x + 100) / CELL_SIZE), static_cast<int>(pos.y / CELL_SIZE)}
        };

        patrol.setWaypoints(patrolPattern);

        enemies.push_back(patrol);
    }

    for (const auto& pos : grid.hunter_Positions) {
        hunters.emplace_back(pos.x, pos.y);
    }
    for (const auto& pos : grid.boost_Positions) {
        boostPads.emplace_back(pos.x, pos.y);
    }

    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    grid.Place_wall(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        player.update(deltaTime, grid, player.shape.getPosition()); 

        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid, player.shape.getPosition()); 
        }

        for (auto& hunter : hunters) {
            hunter.update(deltaTime, grid, player.shape.getPosition());
        }

        for (auto it = boostPads.begin(); it != boostPads.end(); ) {
            if (it->checkCollision(player.shape)) {
                player.activateBoost(2.f);
                it = boostPads.erase(it);
            }
            else {
                ++it;
            }
        }

        window.clear();
        grid.draw(window);

        for (const auto& boostPad : boostPads) {
            boostPad.draw(window);
        }

        window.draw(player.shape);
        for (auto& enemy : enemies) {
            window.draw(enemy.shape);
        }

        for (auto& hunter : hunters) {
            window.draw(hunter.shape);
            hunter.check_collision(player);
        }

        window.display();
    }

    return 0;
}
