#include "snake.h"

void Snake::snake_logic(Grid &grid, const float &delta_time){
    step_timer += delta_time;

    if(step_timer >= step_interval){
        if(tail.empty()){
            grid.setGridCell(GRID::EMPTY_CELL, pos_y, pos_x);   
        }
        else{
            const int tail_size = tail.size() - 1;
            for(int i = tail_size; i >= 0; i--){
                if(i == tail_size){
                    grid.setGridCell(GRID::EMPTY_CELL, tail[i].pos_y, tail[i].pos_x);  
                }

                if(i > 0){
                    tail[i].pos_x = tail[i - 1].pos_x;
                    tail[i].pos_y = tail[i - 1].pos_y;
                    grid.setGridCell(GRID::TAIL, tail[i].pos_y, tail[i].pos_x);  
                }
                else{
                    tail[i].pos_x = pos_x;
                    tail[i].pos_y = pos_y;
                    grid.setGridCell(GRID::TAIL, tail[i].pos_y, tail[i].pos_x);  
                }
            }
        }

        const int MAX_POS_X = GRID::WIDTH - 2;
        const int MAX_POS_Y = GRID::HEIGHT - 2;
        const int MIN_POS_X = 1;
        const int MIN_POS_Y = 1;

        switch(dir[0]){
            case SNAKE::UP:
                pos_y--;

                if(pos_y < MIN_POS_Y && hit || grid.getGridCell(pos_y, pos_x) == GRID::TAIL && tail_hit){
                    pos_y++;
                    game_over = true;
                }

                if(pos_y < MIN_POS_Y && !hit){
                    hit = true;
                    pos_y++;
                }
                else if(pos_y >= MIN_POS_Y){
                    hit = false;
                }

                if(grid.getGridCell(pos_y, pos_x) == GRID::TAIL && !tail_hit && !hit){
                    tail_hit = true;
                    pos_y++;
                }
                else if(grid.getGridCell(pos_y, pos_x) != GRID::TAIL){
                    tail_hit = false;
                }

                break;
            case SNAKE::DOWN:
                pos_y++;

                if(pos_y > MAX_POS_Y && hit || grid.getGridCell(pos_y, pos_x) == GRID::TAIL && tail_hit){
                    game_over = true;
                    pos_y--;
                }

                if(pos_y > MAX_POS_Y  && !hit){
                    hit = true;
                    pos_y--;
                }
                else if(pos_y <= MAX_POS_Y){
                    hit = false;
                }

                if(grid.getGridCell(pos_y, pos_x) == GRID::TAIL && !tail_hit && !hit){
                    tail_hit = true;
                    pos_y--;
                }
                else if(grid.getGridCell(pos_y, pos_x) != GRID::TAIL){
                    tail_hit = false;
                }
                
                break;
            case SNAKE::LEFT:
                pos_x--;

                if(pos_x < MIN_POS_X && hit || grid.getGridCell(pos_y, pos_x) == GRID::TAIL && tail_hit){
                    game_over = true;
                    pos_x++;
                }

                if(pos_x < MIN_POS_X && !hit){
                    hit = true;
                    pos_x++;
                }
                else if(pos_x >= MIN_POS_X){
                    hit = false;
                }

                if(grid.getGridCell(pos_y, pos_x) == GRID::TAIL && !tail_hit && !hit){
                    tail_hit = true;
                    pos_x++;
                }
                else if(grid.getGridCell(pos_y, pos_x) != GRID::TAIL){
                    tail_hit = false;
                }

                break;
            case SNAKE::RIGHT:
                pos_x++;

                if(pos_x > MAX_POS_X && hit || grid.getGridCell(pos_y, pos_x) == GRID::TAIL && tail_hit){
                    game_over = true;
                    pos_x--; 
                }

                if(pos_x > MAX_POS_X && !hit){
                    hit = true;
                    pos_x--; 
                }
                else if(pos_x <= MAX_POS_X){
                    hit = false;
                }

                if(grid.getGridCell(pos_y, pos_x) == GRID::TAIL && !tail_hit && !hit){
                    tail_hit = true;
                    pos_x--;
                }
                else if(grid.getGridCell(pos_y, pos_x) != GRID::TAIL){
                    tail_hit = false;
                }

                break;
        }

        if(dir.size() > 1){
            dir.erase(dir.begin());
        }

        grid.setGridCell(GRID::SNAKE_HEAD, pos_y, pos_x);

        step_timer -= step_interval;
    }
}

void Snake::clear_snake_arrays(){
    dir.clear();
    tail.clear();
}