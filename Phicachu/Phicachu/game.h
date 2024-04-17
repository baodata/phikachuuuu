#pragma once
#include <cstdlib>
#include <ctime>
#include "render.h"
#include "check.h"

void createGame(tile** table, int x, int y, int numOfChar);
void shuffleGame(tile** table, int x, int y);	//shuffling
void game(int x, int y, int* secondsptr, player p, bool hard, string background, int pokeNum, bool & exit);
void level(int* secondsptr, player p, bool hard, bool& hardMode, bool& replay);