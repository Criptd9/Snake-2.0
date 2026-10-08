#pragma once

#include <iostream>
#include "grid.h"
#include <random>

class Apple{
    private:
        std::string apple_c;
        int pos_x;
        int pos_y;
        int color;
    public:

        //Get methods
        int getPosX()const{return pos_x;}
        int getPosY()const{return pos_y;}
        std::string getAppleCharacter()const{return apple_c;}
        int getColor()const{return color;}

        //Set methods
        void setPosX(const int &pos_x){this->pos_x = pos_x;}
        void setPosY(const int &pos_y){this->pos_y = pos_y;}
        void setAppleCharacter(const std::string &apple_c){this->apple_c = apple_c;}
        void setColor(const int &color){this->color = color;}

        //Apple methods
        void spawn_apple(Grid &grid);
};