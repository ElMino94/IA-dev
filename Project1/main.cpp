#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "boost_pad.hpp"  
#include "Hunter.hpp"
#include "Patrol.hpp"
#include "Grid.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400); // Initialiser la position du joueur

    std::vector<Patrol> enemies; // Liste des patrouilleurs
    std::vector<Hunter> hunters;
    std::vector<BoostPad> boostPads;

    Grid grid;
    grid.loadFromFile("map.txt"); // Charger la grille depuis le fichier

    // Création des Patrols avec leurs positions de départ
    for (const auto& pos : grid.patrolPositions) {
        Patrol patrol(pos.x, pos.y, 100.0f); // Rayon de détection à 100.0f

        // Définition des waypoints en utilisant des indices de grille (Vector2i)
        std::vector<sf::Vector2i> patrolPattern = {
            {static_cast<int>(pos.x / CELL_SIZE), static_cast<int>((pos.y + 100) / CELL_SIZE)},
            {static_cast<int>((pos.x + 100) / CELL_SIZE), static_cast<int>((pos.y + 100) / CELL_SIZE)},
            {static_cast<int>((pos.x + 100) / CELL_SIZE), static_cast<int>(pos.y / CELL_SIZE)}
        };

        // Passer le vecteur de waypoints avec des indices de grille (Vector2i) à setWaypoints
        patrol.setWaypoints(patrolPattern);

        enemies.push_back(patrol);
    }

    // Initialisation des Hunters et BoostPads
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
                    grid.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        player.update(deltaTime, grid, player.shape.getPosition()); // Passer la position en pixels du joueur

        // Mise à jour des Patrols
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid, player.shape.getPosition()); // Passer la position en pixels du joueur
        }

        for (auto& hunter : hunters) {
            hunter.update(deltaTime, grid, player.shape.getPosition());
        }

        // Vérification des collisions avec les BoostPads
        for (auto it = boostPads.begin(); it != boostPads.end(); ) {
            if (it->checkCollision(player.shape)) {
                player.activateBoost(2.f);
                it = boostPads.erase(it);
            }
            else {
                ++it;
            }
        }

        // Affichage
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
