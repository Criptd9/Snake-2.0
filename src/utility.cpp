#include "game.h"

void Game::hide_cursor(){
    std::cout<<"\033[?25l";
}

void Game::show_curosr(){
    std::cout<<"\033[?25h";
}

void Game::add_lines(const int &amount){
    for(int i=0;i<amount;i++){
        std::cout<<"\n";
        n_lines++;
    }
}

void Game::clear_lines(){
    for(int i=0;i<n_lines;i++){
        std::cout<<"\033[A\r";
    }

    n_lines = 0;
}

void Game::text(const std::string &_text, int color){
    SetConsoleTextAttribute(consoleOutput, color);
    std::cout<<_text;
}

void Game::show_info(){
    add_lines(1);
    text("Press the ", WHITE_COLOR); text("up ", BLUE_COLOR); text("or ", WHITE_COLOR); text("down keys ", BLUE_COLOR); text("to select an option.", WHITE_COLOR);
    add_lines(1);
    text("Press ", WHITE_COLOR); text("enter ", BLUE_COLOR); text("to confirm an option.", WHITE_COLOR);
}

void show_options(const std::vector<std::string> &OPTIONS, const int &current_option, Game &game){
    for(int i=0;i<OPTIONS.size();i++){
        if(i == current_option){
            game.text("     " + OPTIONS[i] + " <--", BLUE_COLOR);
        }
        else{
            game.text("     " + OPTIONS[i] + "    ", WHITE_COLOR);
        }
        game.add_lines(1);
    }
}

void change_option(size_t n_options, int &current_option, char key){
    n_options -= 1;

    switch(key){
        case UP_ARROW_KEY:
            current_option--;
            if(current_option < 0){
                current_option = n_options;
            }
            break;
        case DOWN_ARROW_KEY:
            current_option++;
            if(current_option > n_options){
                current_option = 0;
            }
            break;
    }
}