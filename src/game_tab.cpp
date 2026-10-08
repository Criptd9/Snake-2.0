#include "game.h"

void Game_tab::init_game(){
    //Init arrays
    grid.clear_grid();
    snake.clear_snake_arrays();

    snake.setGameOver(false);

    //Init snake head
    snake.setPosX(GRID::WIDTH / 2);
    snake.setPosY(GRID::HEIGHT / 2);
    snake.setStepTimer(0.0f);
    snake.setStepInterval(0.15f);
    snake.setHead("O");
    snake.setColor(GREEN_COLOR);
    snake.setDirElement(SNAKE::STOP);
    snake.setHit(false);
    snake.setTailHit(false);
    grid.setGridCell(GRID::SNAKE_HEAD, snake.getPosY(), snake.getPosX());

    //Init apple
    apple.setAppleCharacter("@");
    apple.setColor(RED_COLOR);
    apple.spawn_apple(grid);

    //Init snake body
    snake.setBody("o");
    snake.setColorBody(LIGHT_YELLOW_COLOR);

    //Init scores
    score = 0;
    
    std::ifstream file_score("Score.txt");

    if(file_score.is_open()){
        std::string line;

        while(!file_score.eof()){
            std::getline(file_score, line);
        }

        if(!line.empty()){
            best_score = std::stoi(line);
        }
        else{
            best_score = 0;
        }
        file_score.close();
    }
    else{
        best_score = 0;

        std::ofstream file_score {"Score.txt"};
    }

    //Init clock
    last_time = Clock::now();
}

void Game_tab::draw(Game &game){
    for(const auto &row : grid.getGrid()){
        for(const auto &col : row){
            switch(col){
                case GRID::WALL_CELL:
                    game.text("#", BLUE_COLOR);
                    break;
                case GRID::EMPTY_CELL:
                    game.text(".", WHITE_COLOR);
                    break;
                case GRID::SNAKE_HEAD:
                    game.text(snake.getHead(), snake.getColor());
                    break;
                case GRID::APPLE:
                    game.text(apple.getAppleCharacter(), apple.getColor());
                    break;
                case GRID::TAIL:
                    game.text(snake.getBody(), snake.getColorBody());
                    break;
            }
        }
        game.add_lines(1);
    }

    info(game);
}

void Game_tab::input(Game &game){
    const int last_element_of_snake_dir = snake.getDir().size() - 1;

    if(_kbhit()){
        char key = getch();

        switch(key){
            case ESC_KEY:
                pause = true;
                break;
            case UP_ARROW_KEY:
                if(snake.getDirElement(last_element_of_snake_dir) != SNAKE::DOWN){
                    snake.setDirElement(SNAKE::UP);
                }
                break;
            case DOWN_ARROW_KEY:
                if(snake.getDirElement(last_element_of_snake_dir) != SNAKE::UP){
                    snake.setDirElement(SNAKE::DOWN);
                }
                break;
            case LEFT_ARROW_KEY:
                if(snake.getDirElement(last_element_of_snake_dir) != SNAKE::RIGHT){
                    snake.setDirElement(SNAKE::LEFT);
                }
                break;
            case RIGHT_ARROW_KEY:
                if(snake.getDirElement(last_element_of_snake_dir) != SNAKE::LEFT){
                    snake.setDirElement(SNAKE::RIGHT);
                }
                break;
        }
    }
}

void Game_tab::update(Game &game){
    if(!pause){
        delta_time = calculate_delta_time();

        draw(game);

        input(game);

        if(snake.getPosX() == apple.getPosX() && snake.getPosY() == apple.getPosY()){
            score++;
            if(score != GAME_TAB::MAX_SCORE){
                apple.spawn_apple(grid);
            }
            snake.setTailElement({snake.getPosX(), snake.getPosY()});
        }

        if(score == GAME_TAB::MAX_SCORE){
            win_screen(game);
        }

        snake.snake_logic(grid, delta_time);

        if(snake.getGameOver()){
            game_over_screen(game);
        }
    }
    else{
        system("cls");
        pause_screen(game);
        last_time = Clock::now();
    }

    game.clear_lines();
}

void Game_tab::game_over_screen(Game &game){
    system("cls");

    if(score > best_score){
        best_score = score;

        std::ofstream file_score("Score.txt");

        if(file_score.is_open()){
            file_score << std::to_string(best_score);
            file_score.close();
        }
        else{
            std::ofstream file_score{"Score.txt"};
        }
    }

    game.text("Game over", RED_COLOR);
    game.add_lines(2);
    game.text("Your score: ", BLUE_COLOR);game.text(std::to_string(score), WHITE_COLOR);
    game.add_lines(1);
    game.text("Your best score: ", BLUE_COLOR);game.text(std::to_string(best_score), WHITE_COLOR);
    game.add_lines(2);
    game.text("Press ", WHITE_COLOR);game.text("any key ", BLUE_COLOR);game.text("to return at the menu.", WHITE_COLOR);

    char key = getch();

    system("cls");

    game.setCurrentTab(GAME::MENU_TAB);
}

void Game_tab::win_screen(Game &game){
    system("cls");
    game.text("You win!", BLUE_COLOR);
    game.add_lines(2);
    game.text("You reached the highest score possible! ", WHITE_COLOR);
    game.add_lines(1);
    game.text("Your score: ", BLUE_COLOR);game.text(std::to_string(score), WHITE_COLOR);
    game.add_lines(1);
    game.text("Your best score: ", BLUE_COLOR);game.text(std::to_string(best_score), WHITE_COLOR);
    game.add_lines(2);
    game.text("Press ", WHITE_COLOR);game.text("any key ", BLUE_COLOR);game.text("to return at the menu.", WHITE_COLOR);

    char key = getch();

    system("cls");

    game.setCurrentTab(GAME::MENU_TAB);

}

void Game_tab::pause_screen(Game &game){
    game.text("Pause", RED_COLOR);
    game.add_lines(2);
    game.text("Are you sure to quit?", WHITE_COLOR);
    game.add_lines(2);

    show_options(PAUSE_SCREEN_OPTIONS, current_option, game);

    game.show_info();

    char key = getch();

    change_option(PAUSE_SCREEN_OPTIONS.size(), current_option, key);

    if(key == ENTER_KEY){
        switch(current_option){
            case MENU::YES:
                system("cls");
                pause = false;
                current_option = GAME_TAB::YES;
                game.setCurrentTab(GAME::MENU_TAB);
                break;
            case MENU::NO:
                system("cls");
                pause = false;
                current_option = GAME_TAB::YES;
                game.setCurrentTab(GAME::GAME_TAB);
                break;
        }
    }

    game.clear_lines();
}