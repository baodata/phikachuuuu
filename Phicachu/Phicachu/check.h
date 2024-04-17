#pragma once
#include "utility.h"

bool checkChuI(tile** table, int x1, int y1, int x2, int y2);
bool checkChuL(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp);
bool checkChuUZ(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp, int& xtemp2, int& ytemp2, int xmax, int ymax);
int checkAll(tile** table, int x1, int y1, int x2, int y2, int& xtemp, int& ytemp, int& xtemp2, int& ytemp2, int xmax, int ymax);
bool checkAvailablePair(tile** table, int xmax, int ymax, int& x1, int& y1, int& x2, int& y2);