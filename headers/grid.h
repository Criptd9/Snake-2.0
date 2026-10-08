#pragma once

#include <iostream>
#include <vector>

namespace GRID{
    const int WIDTH = 20;
    const int HEIGHT = 10;
    enum CELLS {EMPTY_CELL = 0, WALL_CELL = 1, SNAKE_HEAD = 2, APPLE = 3, TAIL = 4};
}

class Grid{
    private:
        std::vector<std::vector<int>>grid;
    public:
        Grid();

        //Get methods
        std::vector<std::vector<int>> getGrid()const{return grid;}
        int getGridCell(const int &row, const int &col)const{return grid[row][col];}

        //Set methods
        void setGrid(const std::vector<std::vector<int>>& grid){this->grid = grid;}
        void setGridCell(const int &value, const int &row, const int &col){grid[row][col] = value;}

        //Grid methods
        void clear_grid();

        ~Grid() = default;
};