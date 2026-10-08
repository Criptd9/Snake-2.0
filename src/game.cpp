#include "game.h"

void Game::loop(Game &self){
    system("cls");

    Menu_tab menu;

    Game_tab game_tab;

    game_tab.setPause(false);

    game_tab.setCurrentOption(GAME_TAB::YES);

    while(run){
        switch(current_tab){
            case GAME::MENU_TAB:
                menu.menu_tab(self, game_tab);
                break;
            case GAME::EXIT_TAB:
                menu.exit_tab(self);
                break;
            case GAME::GAME_TAB:
                game_tab.update(self);
                break;
            case GAME::BEST_SCORE_TAB:
                menu.best_score_tab(self, game_tab);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP));
    }

    system("cls");

    SetConsoleTextAttribute(consoleOutput, WHITE_COLOR);
}

void Menu_tab::menu_tab(Game &game, Game_tab &_game_tab){
    game.text("Snake", RED_COLOR);
    game.add_lines(2);

    show_options(MENU_TAB_OPTIONS, current_option, game);

    game.show_info();

    char key = getch();

    change_option(MENU_TAB_OPTIONS.size(), current_option, key);

    if(key == ENTER_KEY){
        switch(current_option){
            case MENU::PLAY:
                system("cls");
                _game_tab.init_game();
                game.setCurrentTab(GAME::GAME_TAB);
                break;
            case MENU::BEST_SCORE:
                system("cls");
                game.setCurrentTab(GAME::BEST_SCORE_TAB);
                break;
            case MENU::EXIT:
                system("cls");
                current_option = MENU::YES;
                game.setCurrentTab(GAME::EXIT_TAB);
                break;
        }
    }

    game.clear_lines();
}

void Menu_tab::best_score_tab(Game &game, Game_tab &_game_tab){
    std::ifstream file_score("Score.txt");

    if(file_score.is_open()){
        std::string line;

        while(!file_score.eof()){
            std::getline(file_score, line);
        }

        if(!line.empty()){
            _game_tab.setBestScore(std::stoi(line));
        }
        else{
            _game_tab.setBestScore(0);
        }

        file_score.close();
    }
    else{
        _game_tab.setBestScore(0);

        std::ofstream file_score{"Score.txt"};
    }

    game.text("Your best score: ", BLUE_COLOR);game.text(std::to_string(_game_tab.getBestScore()), WHITE_COLOR);
    game.add_lines(2);
    game.text("Press any ", WHITE_COLOR);game.text("key ", BLUE_COLOR);game.text("to return back.", WHITE_COLOR);

    char key = getch();

    system("cls");
    game.setCurrentTab(GAME::MENU_TAB);
}

void Menu_tab::exit_tab(Game &game){
    game.text("Are you sure to quit?", RED_COLOR);
    game.add_lines(2);

    show_options(EXIT_TAB_OPTIONS, current_option, game);

    game.show_info();

    char key = getch();

    change_option(EXIT_TAB_OPTIONS.size(), current_option, key);

    if(key == ENTER_KEY){
        switch(current_option){
            case MENU::YES:
                game.setRun(false);
                break;
            case MENU::NO:
                system("cls");
                current_option = MENU::EXIT;
                game.setCurrentTab(GAME::MENU_TAB);
                break;
        }
    }

    game.clear_lines();
}