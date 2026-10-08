#include "game.h"

//C++ 17

int main(){
    system("title Snake");
    
    Game game;

    game.hide_cursor();

    game.setConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE));

    game.loop(game);

    game.show_curosr();
    
    return 0;
}