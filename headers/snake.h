#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "grid.h"

namespace SNAKE{
    enum DIR {STOP = 0, UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4};

    struct Tail{
        int pos_x;
        int pos_y;

        Tail(const int &pos_x, const int &pos_y) : pos_x(pos_x), pos_y(pos_y) {}

        Tail() = default;
    };
}

class Snake{
    private:
        std::string head;

        int pos_x;
        int pos_y;

        float step_timer;
        float step_interval;

        int color;

        std::vector<int>dir;

        bool hit;
        bool tail_hit;

        bool game_over;

        std::vector<SNAKE::Tail>tail;
        int color_body;
        std::string body;
    public:
        Snake() = default;

        //Get methods
        std::string getHead()const{return head;}

        int getPosX()const{return pos_x;}
        int getPosY()const{return pos_y;}

        float getStepTimer()const{return step_timer;}
        float getStepInterval()const{return step_interval;}

        int getColor()const{return color;}

        std::vector<int> getDir()const{return dir;}
        int getDirElement(const int &id){return dir[id];}

        bool getHit()const{return hit;}
        bool getTailHit()const{return tail_hit;}

        bool getGameOver()const{return game_over;}

        std::vector<SNAKE::Tail> getTail()const{return tail;}
        SNAKE::Tail getTailElement(const int &id)const{return tail[id];}
        int getColorBody()const{return color_body;}
        std::string getBody()const{return body;}

        //Set methods
        void setHead(const std::string &head){this->head = head;}

        void setPosX(const int &pos_x){this->pos_x = pos_x;}
        void setPosY(const int &pos_y){this->pos_y = pos_y;}

        void setStepTimer(const float &step_timer){this->step_timer = step_timer;}
        void setStepInterval(const float &step_interval){this->step_interval = step_interval;}

        void setColor(const int &color){this->color = color;}

        void setDir(const std::vector<int> &dir){this->dir = dir;}
        void setDirElement(const int &element){if(dir.size() < 3){dir.push_back(element);}}

        void setHit(const bool &hit){this->hit = hit;}
        void setTailHit(const bool &tail_hit){this->tail_hit = tail_hit;}

        void setGameOver(const bool &game_over){this->game_over = game_over;}
        
        void setTail(const std::vector<SNAKE::Tail> &tail){this->tail = tail;}
        void setTailElement(const SNAKE::Tail &element){tail.emplace_back(element);}
        void setColorBody(const int &color_body){this->color_body = color_body;}
        void setBody(const std::string &body){this->body = body;}

        //Snake methods
        void snake_logic(Grid &grid, const float &delta_time);
        void clear_snake_arrays();

        ~Snake() = default;
};