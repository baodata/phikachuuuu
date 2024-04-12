#pragma once
#include "game.h"
#include "utility.h"
#include <cstdlib>
#include <ctime>

void createGame(tile** table, int x, int y, int numOfChar);
void shuffleGame(tile** table, int x, int y);	//shuffling
void game(int x, int y, int* secondsptr, player p, bool hard, string background, int pokeNum, bool & exit);
void level(int* secondsptr, player p, bool hard, bool& hardMode, bool& replay);