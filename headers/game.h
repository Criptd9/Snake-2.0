#pragma once

#include "game_utility.h"
#include "grid.h"
#include "snake.h"
#include "apple.h"

using Clock = std::chrono::high_resolution_clock;
using TimePoint = Clock::time_point;

namespace GAME{
    enum TAB {MENU_TAB = 0, GAME_TAB = 1, BEST_SCORE_TAB = 2, EXIT_TAB = 3};
}

class Game{
    private:
        bool run;

        int current_tab;

        HANDLE consoleOutput;

        int n_lines;
    public:
        Game() {run = true, current_tab = GAME::MENU_TAB, n_lines = 0;}

        //Get methods
        bool getRun()const{return run;}
        int getCurrentTab()const{return current_tab;}
        int getLines()const{return n_lines;}
        HANDLE getConsoleOutput()const{return consoleOutput;}

        //Set methods
        void setRun(const bool &run){this->run = run;}
        void setCurrentTab(const int &current_tab){this->current_tab = current_tab;}
        void setLines(const int &n_lines){this->n_lines = n_lines;}
        void setConsoleOutput(const HANDLE &consoleOutput){this->consoleOutput = consoleOutput;}

        //Game methods
        void loop(Game &self);
        void game_tab();

        //Utility methods
        void hide_cursor();
        void show_curosr();
        void add_lines(const int &amount);
        void clear_lines();
        void text(const std::string &_text, int color);
        void show_info();

        ~Game() = default;
};

namespace GAME_TAB{
    const int MAX_SCORE = (GRID::WIDTH - 2) * (GRID::HEIGHT - 2) - 1;
    /*The highest score possibile is equal to the total area inside the grid (so we need to subtract the 4 angles) minus 1 because
    we need to toggle the position of the snake's head.*/
    enum PAUSE_SCREEN_OPTIONS_ID {YES = 0, NO = 1};
}

class Game_tab{
    private:
        const std::vector<std::string> PAUSE_SCREEN_OPTIONS = {"Yes", "No"};
        int current_option;

        Grid grid;
        Snake snake;
        Apple apple;

        int score;
        int best_score;

        float delta_time;
        Clock::time_point last_time;

        bool pause;
    public:
        Game_tab(){}

        //Get methods
        int getCurrentOption()const{return current_option;}
        int getScore()const{return score;}
        int getBestScore()const{return best_score;}
        float getDeltaTime()const{return delta_time;}
        Clock::time_point getLastTime()const{return last_time;}
        bool getPause()const{return pause;}

        //Set methods
        void setCurrentOption(const int &current_option){this->current_option = current_option;}
        void setScore(const int &score){this->score = score;}
        void setBestScore(const int &best_score){this->best_score = best_score;}
        void setDeltaTime(const float &delta_time){this->delta_time = delta_time;}
        void setLastTime(const Clock::time_point &last_time){this->last_time = last_time;}
        void setPause(const bool &pause){this->pause = pause;}

        //Game_tab methods
        void init_game();
        void draw(Game &game);
        void input(Game &game);
        void update(Game &game);
        void game_over_screen(Game &game);
        void win_screen(Game &game);
        void pause_screen(Game &game);

        //Utility methods
        void info(Game &game);
        float calculate_delta_time();

        ~Game_tab() = default;
};

namespace MENU{
    enum OPTIONS_ID {PLAY = 0, BEST_SCORE = 1, EXIT = 2};
    enum EXIT_TAB_OPTIONS_ID {YES = 0, NO = 1};
}

class Menu_tab{
    private:
        const std::vector<std::string> MENU_TAB_OPTIONS = {"Play", "Show best score", "Exit"};
        const std::vector<std::string> EXIT_TAB_OPTIONS = {"Yes", "No"};

        int current_option;
    public:
        Menu_tab() {current_option = MENU::PLAY;}

        //Get methods
        int getCurrentOption()const{return current_option;}
        //Set methods
        void setCurrentOption(const int &current_option){this->current_option = current_option;}

        //Menu methods
        void menu_tab(Game &game, Game_tab &_game_tab);
        void best_score_tab(Game &game, Game_tab &_game_tab);
        void exit_tab(Game &game);

        ~Menu_tab() = default;
};

//Utility functions
void show_options(const std::vector<std::string> &OPTIONS, const int &current_option, Game &game);
void change_option(size_t n_options, int &current_option, char key);