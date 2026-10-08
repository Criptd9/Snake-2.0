#include "grid.h"

Grid::Grid(){
    grid.resize(GRID::HEIGHT);

    for(int i=0;i<GRID::HEIGHT;i++){
        grid[i].resize(GRID::WIDTH);
        for(int j=0;j<GRID::WIDTH;j++){
            if(i == 0 || i == GRID::HEIGHT - 1 || j == 0 || j == GRID::WIDTH - 1){
                grid[i][j] = GRID::WALL_CELL;
            }
            else{
                grid[i][j] = GRID::EMPTY_CELL;
            }
        }
    }
}

void Grid::clear_grid(){
    for(auto &row : grid){
        for(auto &col : row){
            if(col != GRID::EMPTY_CELL && col != GRID::WALL_CELL){
                col = GRID::EMPTY_CELL;
            }
        }
    }
}