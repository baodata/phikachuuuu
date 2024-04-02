#pragma once
#include "game.h"
#include "utility.h"
#include <cstdlib>
#include <ctime>

void createGame(tile** table, int x, int y, int numOfChar);
void game(int x, int y, int *secondsptr, player p);
void easy(int *secondsptr, player p);