#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>	// Key
#include <thread> // sleep
#include "render.h"
#include "utility.h"
#include "check.h"
#include "game.h"

using namespace std;

void createGame(tile** table, int x, int y, int numOfChar)
{
	srand(time(0));
	int size = x * y;
	char* Pokemon = new char[size];
	//khoi tao
	for (int i = 0; i < size; i += 2)
	{
		Pokemon[i] = Pokemon[i + 1] = rand() % numOfChar + 'A';
	}
	//random
	for (int i = 0; i < size; i++)
	{
		swapPoke(Pokemon[i], Pokemon[rand() % size]);
	}
	int index = 0;
	for (int i = 0; i < y + 2; i++)
	{
		for (int j = 0; j < x + 2; j++)
		{
			if (i == 0 || j == 0 || i == y + 1 || j == x + 1)
				table[i][j].empty = true;
			else
			{
				table[i][j].pokemon = Pokemon[index];
				index++;
			}
		}
	}
	delete[] Pokemon;
}

void shuffleGame(tile** table, int x, int y)
{
	int count = 0;
	for (int i = 1; i <= y; i++) {
		for (int j = 1; j <= x; j++)
		{
			if (table[i][j].empty == false)
			{
				count++;
			}
		}
	}
	char* Pokemon = new char[count];
	count = 0;
	for (int i = 1; i <= y; i++) {
		for (int j = 1; j <= x; j++)
		{
			if (table[i][j].empty == false)
			{
				Pokemon[count] = table[i][j].pokemon;
				count++;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		swapPoke(Pokemon[i], Pokemon[rand() % count]);
	}
	count = 0;
	for (int i = 1; i <= y; i++) {
		for (int j = 1; j <= x; j++)
		{
			if (table[i][j].empty == false)
			{
				table[i][j].pokemon = Pokemon[count];
				count++;
			}
		}
	}
	delete[] Pokemon;
}

void game(int x, int y, int *secondsptr, player p, bool hard, string background)
{
	tile** table = new tile * [y + 2];
	for (int i = 0; i < y + 2; i++)
		table[i] = new tile[x + 2];
	createGame(table, x, y, 15);
	readBackground(table, x, y, background);
	cout << "\x1b[?25l"; // an con tro
	system("cls");
	bool haveChosen = false;
	bool hintPressed = false;
	string sound;
	pointer chosen, current;
	printTable(table, current, x, y);
	printInfoBoard(secondsptr, p);

	int pokeLeft = x * y;
	int tempx1, tempy1, tempx2, tempy2;

	while (true)
	{
		char arrow;
		switch (arrow = _getch())
		{
		case KEY_UP:
			box(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			if (current.y == 1)
				current.y = y;
			else
				current.y--;
			pointedBox(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			break;
		case KEY_DOWN:
			box(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			if (current.y == y)
				current.y = 1;
			else
				current.y++;
			pointedBox(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			break;
		case KEY_RIGHT:
			box(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			if (current.x == x)
				current.x = 1;
			else
				current.x++;
			pointedBox(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			break;
		case KEY_LEFT:
			box(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			if (current.x == 1)
				current.x = x;
			else
				current.x--;
			pointedBox(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
			break;
		case 'h': //hint, can spam this for extremely low score
			if (checkAvailablePair(table, x, y, tempx1, tempy1, tempx2, tempy2))
			{
				hintPressed = true;
				table[tempy1][tempx1].hinted = true;
				table[tempy2][tempx2].hinted = true;
				box(table[tempy1][tempx1].xCursor, table[tempy1][tempx1].yCursor, table[tempy1][tempx1]);
				box(table[tempy2][tempx2].xCursor, table[tempy2][tempx2].yCursor, table[tempy2][tempx2]);
			}
			*secondsptr = *secondsptr - 10;
			break;
		case ' ':
		case '\r':
		case '\n':
			if (!table[current.y][current.x].empty)
			{
				table[current.y][current.x].chosen = !table[current.y][current.x].chosen;
				if (haveChosen == false)
				{
					haveChosen = true;
					chosen.x = current.x;
					chosen.y = current.y;
				}
				else
				{
					if (hintPressed && ((chosen.x == tempx1 && chosen.y == tempy1) || (chosen.x == tempx2 && chosen.y == tempy2) || (current.x == tempx1 && current.y == tempy1) || (current.x == tempx2 && current.y == tempy2)))	//dung
					{
						table[tempy1][tempx1].hinted = false;
						table[tempy2][tempx2].hinted = false;
						box(table[tempy1][tempx1].xCursor, table[tempy1][tempx1].yCursor, table[tempy1][tempx1]);
						box(table[tempy2][tempx2].xCursor, table[tempy2][tempx2].yCursor, table[tempy2][tempx2]);
						hintPressed = false;
					}
					int xtemp, ytemp, xtemp2, ytemp2;
					int check = checkAll(table, chosen.x, chosen.y, current.x, current.y, xtemp, ytemp, xtemp2, ytemp2, x, y);
					if (table[chosen.y][chosen.x].pokemon == table[current.y][current.x].pokemon && check && (chosen.x != current.x || chosen.y != current.y)) // dung
					{
						sound = "an.wav";
						makeSound(sound);
						pokeLeft -= 2;
						if (!hard)
						{
							table[chosen.y][chosen.x].empty = true;
							table[current.y][current.x].empty = true;
							if (check == 1)
								drawI(table, chosen, current);
							else if (check == 2)
								drawL(table, chosen, current, xtemp, ytemp);
							else if (check == 3)
								drawUZ(table, chosen, current, xtemp, ytemp, xtemp2, ytemp2);
							for (int i = 1; i <= y; i++)
							{
								for (int j = 1; j <= x; j++)
								{
									if (table[i][j].empty)
									{
										box(table[i][j].xCursor, table[i][j].yCursor, table[i][j]);
									}
								}
							}
							//box(table[chosen.y][chosen.x].xCursor, table[chosen.y][chosen.x].yCursor, table[chosen.y][chosen.x]);		//delete 2 hop
							//box(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
						}
						else
						{
							table[chosen.y][chosen.x].chosen = false;
							table[current.y][current.x].chosen = false;
							if (check == 1)
								drawI(table, chosen, current);
							else if (check == 2)
								drawL(table, chosen, current, xtemp, ytemp);
							else if (check == 3)
								drawUZ(table, chosen, current, xtemp, ytemp, xtemp2, ytemp2);
							if (current.x < chosen.x)
							{
								pushBox(table[chosen.y], x, chosen.x);
								pushBox(table[current.y], x, current.x);
								printBoxRow(table[chosen.y], x);
								printBoxRow(table[current.y], x);
							}
							else
							{
								pushBox(table[current.y], x, current.x);
								pushBox(table[chosen.y], x, chosen.x);
								printBoxRow(table[current.y], x);
								printBoxRow(table[chosen.y], x);
							}
						}
						if (!checkAvailablePair(table, x, y, tempx1, tempy1, tempx2, tempy2) && pokeLeft > 0)
							do
							{
								printMoveAnnouncement();
								shuffleGame(table, x, y);
								printTable(table, current, x, y);
							} while (!checkAvailablePair(table, x, y, tempx1, tempy1, tempx2, tempy2) && pokeLeft > 0);
					}
					else  //sai
					{
						table[current.y][current.x].chosen = false;
						table[chosen.y][chosen.x].chosen = false;
						box(table[chosen.y][chosen.x].xCursor, table[chosen.y][chosen.x].yCursor, table[chosen.y][chosen.x]);
						pointedBox(table[current.y][current.x].xCursor, table[current.y][current.x].yCursor, table[current.y][current.x]);
					}
					haveChosen = false;
				}
			}
			break;
		}
		printScore(*secondsptr);
		if (pokeLeft == 0)
		{
			break;
		}
	}
	//giai phong
	for (int i = 0; i < y; i++) {
		delete[] table[i];
	}
	delete[] table;
}

void level(int* secondsptr, player p, bool hard)
{
	string sound = "win_level.wav";
	game(4, 4, secondsptr, p, hard, "lvl1.txt");
	cout << "\x1b[33m"; printScore(*secondsptr); cout << "\x1b[0m";
	makeSound(sound);
	stop(1500);
	game(6, 5, secondsptr, p, hard, "lvl2.txt");
	cout << "\x1b[33m"; printScore(*secondsptr); cout << "\x1b[0m";
	makeSound(sound);
	stop(1500);
	game(8, 6, secondsptr, p, hard, "lvl3.txt");
	cout << "\x1b[33m"; printScore(*secondsptr); cout << "\x1b[0m";
	makeSound(sound);
	p.score = *secondsptr;
	(*secondsptr) = -200;
	sound = "win_game.wav";
	makeSound(sound);
	printWin();
	savePlayer(p);
	sortFile();
	printWinBoard(p, hard);
}