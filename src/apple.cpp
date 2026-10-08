#include "apple.h"

void Apple::spawn_apple(Grid &grid){
    struct Available_position{
        int pos_x;
        int pos_y;

        Available_position(const int &pos_x, const int &pos_y) : pos_x(pos_x), pos_y(pos_y) {}
    };

    std::vector<Available_position>available_positions;

    for(int i=0;i<GRID::HEIGHT;i++){
        for(int j=0;j<GRID::WIDTH;j++){
            if(grid.getGridCell(i, j) == GRID::EMPTY_CELL){
                available_positions.emplace_back(j, i);
            }
        }
    }

    if(!available_positions.empty()){
        const int MIN_ELEMENT = 0;
        const int MAX_ELEMENT = available_positions.size() - 1;

        std::random_device rd;
        std::uniform_int_distribution<int> random_pos(MIN_ELEMENT, MAX_ELEMENT);

        int random_element = random_pos(rd);

        pos_x = available_positions[random_element].pos_x;
        pos_y = available_positions[random_element].pos_y;

        grid.setGridCell(GRID::APPLE, pos_y, pos_x);
    }
}