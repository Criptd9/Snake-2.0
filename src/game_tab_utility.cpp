#include "game.h"

void Game_tab::info(Game &game){
    game.add_lines(1);
    game.text("Press ", WHITE_COLOR);game.text("esc ", BLUE_COLOR);game.text("to pause.", WHITE_COLOR);
    game.add_lines(1);
    game.text("Press the ", WHITE_COLOR);game.text("arrow keys ", BLUE_COLOR);game.text("to move the snake.", WHITE_COLOR);
    game.add_lines(1);
    game.text("Your score: ", BLUE_COLOR);game.text(std::to_string(score), WHITE_COLOR);
    game.add_lines(1);
    game.text("Your best score: ", BLUE_COLOR);game.text(std::to_string(best_score), WHITE_COLOR);
}

float Game_tab::calculate_delta_time(){
    auto current_time = Clock::now();

    float dt = std::chrono::duration<float>(current_time - last_time).count();

    last_time = current_time;

    return dt;
}