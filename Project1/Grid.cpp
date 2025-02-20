#include "grid.hpp"
#include <fstream>
#include <iostream>
 
Grid::Grid() {
    cells.resize(GRID_HEIGHT, vector<Cell>(GRID_WIDTH, { true, {0, 0}, RectangleShape(Vector2f(CELL_SIZE, CELL_SIZE)) }));
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cells[y][x].position = Vector2f(x * CELL_SIZE, y * CELL_SIZE);
            cells[y][x].shape.setPosition(cells[y][x].position);
            cells[y][x].shape.setFillColor(Color::Transparent);
            cells[y][x].shape.setOutlineThickness(1);
            cells[y][x].shape.setOutlineColor(Color(50, 50, 50));
        }
    }
}

void Grid::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

	patrolPositions.clear();

    for (int y = 0; y < GRID_HEIGHT; ++y) {
        string line;
        if (!getline(file, line)) break;
        for (int x = 0; x < GRID_WIDTH && x < line.size(); ++x) {
            if (line[x] == '0') {
                cells[y][x].walkable = true;
            }
            else if (line[x] == '1')
            {
                cells[y][x].walkable = false;
                cells[y][x].shape.setFillColor(Color::White);
            }
            else if (line[x] == 'P') {
                patrolPositions.push_back(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            }
            else if (line[x] == 'h') {
                hunter_Positions.push_back(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            }
            else if (line[x] == 'b') {
                boost_Positions.push_back(Vector2f(x * CELL_SIZE, y * CELL_SIZE));
            }
        }
    }
}

void Grid::draw(RenderWindow& window) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            window.draw(cells[y][x].shape);
        }
    }
}

Cell& Grid::getCell(int x, int y) {
    return cells[y][x];
}

const Cell& Grid::getCell(int x, int y) const
{
    return cells[y][x];
}

void Grid::handleClick(int mouseX, int mouseY) {
    int x = mouseX / CELL_SIZE;
    int y = mouseY / CELL_SIZE;

    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        if (cells[y][x].walkable) {
            cells[y][x].walkable = !cells[y][x].walkable;
            cells[y][x].shape.setFillColor(cells[y][x].walkable ? Color::Transparent : Color::White);
        }     
        else if (!cells[y][x].walkable) {
            cells[y][x].walkable = !cells[y][x].walkable;
            cells[y][x].shape.setFillColor(cells[y][x].walkable ? Color::Transparent : Color::White);
        }
    }
}


