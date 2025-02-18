#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 40;

struct Cell {
    bool walkable;
    Vector2f position;
    RectangleShape shape;
};

class Grid {
private:
    vector<vector<Cell>> cells;
    int wall_limit;
public:
    Grid();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    void handleClick(int mouseX, int mouseY);

	vector<Vector2f> patrolPositions;
};

#endif      
