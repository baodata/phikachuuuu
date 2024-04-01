#include "render.h"
#include <iostream>
#include "utility.h"
#include <string>

using namespace std;

void box(int x, int y, tile a)	//https://stackoverflow.com/questions/3753055/how-can-i-display-extended-ascii-codes-characters-in-perl
{
	moveCursorTo(x, y);
	if (a.empty)
	{
		cout << "       "; moveCursorTo(x, y + 1);
		cout << "       "; moveCursorTo(x, y + 2);
		cout << "       "; moveCursorTo(x + 7, y);
	}
	else if (a.chosen)
	{
		cout << char(218) << "-----" << char(191); moveCursorTo(x, y + 1);
		cout << "|\x1b[42m  \x1b[30m" << a.pokemon << "  \x1b[0m|"; moveCursorTo(x, y + 2);
		cout << char(192) << "-----" << char(217); moveCursorTo(x + 7, y);
	}
	else if (a.hinted)
	{
		cout << "\x1b[5m" << char(218) << "-----" << char(191); moveCursorTo(x, y + 1);
		cout << "|  \x1b[" << (int)a.pokemon % (6) + 31 << "m" << a.pokemon << "\x1b[0m\x1b[5m  |"; moveCursorTo(x, y + 2);
		cout << char(192) << "-----" << char(217) << "\x1b[0m";
	}
	else
	{
		cout << char(218) << "-----" << char(191); moveCursorTo(x, y + 1);
		cout << "|  \x1b[" << (int)a.pokemon % (6) + 31 << "m" << a.pokemon << "\x1b[0m  |"; moveCursorTo(x, y + 2);	//https://gist.github.com/raghav4/48716264a0f426cf95e4342c21ada8e7
		cout << char(192) << "-----" << char(217);
	}
}

void pointedBox(int x, int y, tile a)
{
	moveCursorTo(x, y);
	cout << " --*-- "; moveCursorTo(x, y + 1);
	cout << "*\x1b[47m  \x1b[30m";
	if (!a.empty)
		cout << a.pokemon;
	else
		cout << " ";
	cout << "  \x1b[0m*"; moveCursorTo(x, y + 2);
	cout << " --*-- "; moveCursorTo(x + 7, y);
}

void connectDrawing(tile** table, int x1, int y1, int x2, int y2)
{
	if (y1 == y2)
	{
		if (x1 < x2)
		{
			moveCursorTo(table[y1][x1].xCursor + 3, table[y1][x1].yCursor + 1);
			for (int i = table[y1][x1].xCursor; i <= table[y2][x2].xCursor; i++)
				cout << "-";
		}
		else
		{
			moveCursorTo(table[y2][x2].xCursor + 3, table[y2][x2].yCursor + 1);
			for (int i = table[y2][x2].xCursor; i <= table[y1][x1].xCursor; i++)
				cout << "-";
		}
	}
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			moveCursorTo(table[y1][x1].xCursor + 3, table[y1][x1].yCursor + 1);
			for (int i = table[y1][x1].yCursor; i <= table[y2][x2].yCursor; i++)
			{
				cout << "|";
				moveCursorTo(table[y1][x1].xCursor + 3, i + 1);
			}
		}
		else
		{
			moveCursorTo(table[y2][x2].xCursor + 3, table[y2][x2].yCursor + 1);
			for (int i = table[y2][x2].yCursor; i <= table[y1][x1].yCursor; i++)
			{
				cout << "|";
				moveCursorTo(table[y2][x2].xCursor + 3, i + 1);
			}
		}
	}
}

void deleteConnect(tile** table, int x1, int y1, int x2, int y2)
{
	if (y1 == y2)
	{
		if (x1 < x2)
		{
			moveCursorTo(table[y1][x1].xCursor + 3, table[y1][x1].yCursor + 1);
			for (int i = table[y1][x1].xCursor; i <= table[y2][x2].xCursor; i++)
				cout << " ";
		}
		else
		{
			moveCursorTo(table[y2][x2].xCursor + 3, table[y2][x2].yCursor + 1);
			for (int i = table[y2][x2].xCursor; i <= table[y1][x1].xCursor; i++)
				cout << " ";
		}
	}
	if (x1 == x2)
	{
		if (y1 < y2)
		{
			moveCursorTo(table[y1][x1].xCursor + 3, table[y1][x1].yCursor + 1);
			for (int i = table[y1][x1].yCursor; i <= table[y2][x2].yCursor; i++)
			{
				cout << " ";
				moveCursorTo(table[y1][x1].xCursor + 3, i + 1);
			}
		}
		else
		{
			moveCursorTo(table[y2][x2].xCursor + 3, table[y2][x2].yCursor + 1);
			for (int i = table[y2][x2].yCursor; i <= table[y1][x1].yCursor; i++)
			{
				cout << " ";
				moveCursorTo(table[y2][x2].xCursor + 3, i + 1);
			}
		}
	}
}

void printTable(tile** table, pointer a, int x, int y)
{
	int xloc = 1;
	int yloc = 1;
	for (int i = 0; i <= y + 1; i++)
	{
		for (int j = 0; j <= x + 1; j++)
		{
			table[i][j].xCursor = xloc;
			table[i][j].yCursor = yloc;
			stop(1);
			if (j == a.x && i == a.y)
				pointedBox(xloc, yloc, table[i][j]);
			else
				box(xloc, yloc, table[i][j]);
			moveCursorTo(xloc, yloc);
			xloc += 7;
		}
		xloc = 1;
		yloc += 3;
	}
}

void drawI(tile** table, pointer chosen, pointer current)
{
	connectDrawing(table, chosen.x, chosen.y, current.x, current.y);
	stop(200);
	deleteConnect(table, chosen.x, chosen.y, current.x, current.y);
}

void drawL(tile** table, pointer chosen, pointer current, int xtemp, int ytemp)
{
	connectDrawing(table, chosen.x, chosen.y, xtemp, ytemp);
	connectDrawing(table, xtemp, ytemp, current.x, current.y);
	stop(200);
	deleteConnect(table, chosen.x, chosen.y, xtemp, ytemp);
	deleteConnect(table, xtemp, ytemp, current.x, current.y);
}

void drawUZ(tile** table, pointer chosen, pointer current, int xtemp, int ytemp, int xtemp2, int ytemp2)
{
	connectDrawing(table, chosen.x, chosen.y, xtemp2, ytemp2);
	connectDrawing(table, xtemp2, ytemp2, xtemp, ytemp);
	connectDrawing(table, xtemp, ytemp, current.x, current.y);
	stop(200);
	deleteConnect(table, chosen.x, chosen.y, xtemp2, ytemp2);
	deleteConnect(table, xtemp2, ytemp2, xtemp, ytemp);
	deleteConnect(table, xtemp, ytemp, current.x, current.y);
}

void menuBox(menuButton button)
{
	moveCursorTo(button.xCursor, button.yCursor);
	if (!button.chosen)
		cout << " " << "\x1b[90m" << button.data << "                                                     \x1b[0m";
	else if (button.chosen)
		cout << "\x1b[1m>" << button.data << "<\x1b[33m\x1b[1m " << button.description << "\x1b[0m";
}

void printOuterLine()
{
	moveCursorTo(80, 1);
	cout << char(218) << "---------------------------------------" << char(191);
	for (int i = 0; i < 28; i++)
	{
		moveCursorTo(80, 2 + i);
		cout << "|";
		moveCursorTo(120, 2 + i);
		cout << "|";
	}
	moveCursorTo(80, 30);
	cout << char(192) << "---------------------------------------" << char(217);
}

void printTutorial()
{
	moveCursorTo(81, 2);
	cout << "Use arrow keys to move.";
	moveCursorTo(81, 4);
	cout << "Enter/Space to choose.";
	moveCursorTo(81, 6);
	cout << "Connect 2 boxes with less than 2";
	moveCursorTo(81, 7);
	cout << "direction changes.";
	moveCursorTo(81, 8);
	cout << "(has similar pattern to the letters";
	moveCursorTo(81, 9);
	cout << "I, L, U, Z)";
}

void printTimer(int s)
{
	for (int i = s; i >= 0; --i) 
	{
		moveCursorTo(81, 11);
		cout << i;
		stop(1000);
	}
}//?

void printInfoBoard()
{
	printOuterLine();
	printTutorial();
}