#pragma once
#include "utility.h"

void box(int x, int y, tile a);
void pointedBox(int x, int y, tile a);
void connectDrawing(tile** table, int x1, int y1, int x2, int y2);
void deleteConnect(tile** table, int x1, int y1, int x2, int y2);
void printTable(tile** table, pointer a, int x, int y);
void drawI(tile** table, pointer chosen, pointer a);
void drawL(tile** table, pointer chosen, pointer current, int xtemp, int ytemp);
void drawUZ(tile** table, pointer chosen, pointer current, int xtemp, int ytemp, int xtemp2, int ytemp2);
void menuBox(menuButton button);
void printOuterLine();
void printTutorial();
void printTimer(int s);
void printInfoBoard();