#include <iostream>

#include "Game.h"

int main(int argv, char** argc)
{
    Game g("../src/config.txt");
    g.run();
    return 0;
}