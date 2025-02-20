#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

const int GRID_WIDTH = 21;
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

public:
    Grid();
    void loadFromFile(const string& filename);
    void draw(RenderWindow& window);
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;
    void Place_wall(int mouseX, int mouseY);

	vector<Vector2f> patrolPositions;
    vector<Vector2f> hunter_Positions;
    vector<Vector2f> boost_Positions;
};

#endif      
