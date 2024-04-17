#pragma once
#include "utility.h"
#include <conio.h>

void box(tile a);
void pointedBox(tile a);
void connectDrawing(tile** table, int x1, int y1, int x2, int y2);
void deleteConnect(tile** table, int x1, int y1, int x2, int y2);
void getLocation(tile** table, pointer a, int x, int y);
void printTable(tile** table, pointer a, int x, int y);
void drawI(tile** table, pointer chosen, pointer a);
void drawL(tile** table, pointer chosen, pointer current, int xtemp, int ytemp);
void drawUZ(tile** table, pointer chosen, pointer current, int xtemp, int ytemp, int xtemp2, int ytemp2);
void menuBox(menuButton button);
void printOuterLine();
void printTutorial();
void printScore(int s);
void printPlayer(player p);
void printMoveAnnouncement();
void printWin();
void printInfoBoard(int *secondsptr, player p);
void printLeaderBoard();
void printWinBoard(player p, bool hard, bool& hardMode, bool& replay);

void printBoxRow(tile* a, int length);
void pushBox(tile* a, int length, int removedBox);