#include "render.h"

using namespace std;

void box(tile a)	//https://stackoverflow.com/questions/3753055/how-can-i-display-extended-ascii-codes-characters-in-perl
{
	moveCursorTo(a.xCursor, a.yCursor);
	if (a.empty)
	{
		cout << "\x1b[36m" << a.picture[0]; moveCursorTo(a.xCursor, a.yCursor + 1);
		cout << a.picture[1]; moveCursorTo(a.xCursor, a.yCursor + 2);
		cout << a.picture[2] << "\x1b[0m";
	}
	else if (a.chosen)
	{
		cout << char(218) << "-----" << char(191); moveCursorTo(a.xCursor, a.yCursor + 1);
		cout << "|\x1b[42m  \x1b[30m" << a.pokemon << "  \x1b[0m|"; moveCursorTo(a.xCursor, a.yCursor + 2);
		cout << char(192) << "-----" << char(217);
	}
	else if (a.hinted)
	{
		cout << "\x1b[5m" << char(218) << "-----" << char(191); moveCursorTo(a.xCursor, a.yCursor + 1);
		cout << "|  \x1b[" << (int)a.pokemon % (6) + 31 << "m" << a.pokemon << "\x1b[0m\x1b[5m  |"; moveCursorTo(a.xCursor, a.yCursor + 2);
		cout << char(192) << "-----" << char(217) << "\x1b[0m";
	}
	else
	{
		cout << char(218) << "-----" << char(191); moveCursorTo(a.xCursor, a.yCursor + 1);
		cout << "|  \x1b[" << (int)a.pokemon % (6) + 31 << "m" << a.pokemon << "\x1b[0m  |"; moveCursorTo(a.xCursor, a.yCursor + 2);	//https://gist.github.com/raghav4/48716264a0f426cf95e4342c21ada8e7
		cout << char(192) << "-----" << char(217);
	}
}

void pointedBox(tile a)
{
	moveCursorTo(a.xCursor, a.yCursor);
	cout << " --*-- "; moveCursorTo(a.xCursor, a.yCursor + 1);
	cout << "*\x1b[47m  \x1b[30m";
	if (!a.empty)
		cout << a.pokemon;
	else
		cout << " ";
	cout << "  \x1b[0m*"; moveCursorTo(a.xCursor, a.yCursor + 2);
	cout << " --*-- ";
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

void getLocation(tile** table, pointer a, int x, int y)
{
	int xloc = 1;
	int yloc = 1;
	for (int i = 0; i <= y + 1; i++)
	{
		for (int j = 0; j <= x + 1; j++)
		{
			table[i][j].xCursor = xloc;
			table[i][j].yCursor = yloc;
			xloc += 7;
		}
		xloc = 1;
		yloc += 3;
	}
}

void printTable(tile** table, pointer a, int x, int y)
{
	getLocation(table, a, x, y);
	for (int i = 0; i <= y + 1; i++)
	{
		for (int j = 0; j <= x + 1; j++)
		{
			stop(1);
			if (j == a.x && i == a.y)
				pointedBox(table[i][j]);
			else
				box(table[i][j]);
			moveCursorTo(table[i][j].xCursor, table[i][j].yCursor);
		}
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
		cout << " " << "\x1b[90m" << button.data << "                                                                \x1b[0m";
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
	moveCursorTo(81, 11);
	cout << "Press h for hint (-10 points).";
	moveCursorTo(81, 13);
	cout << "Press Esc to exit.";
	moveCursorTo(81, 15);
	cout << "You lose 1 point per second.";
	moveCursorTo(81, 16);
	cout << "(The maximum score is 200)";
}

void printScore(int s)
{
	moveCursorTo(81, 20);
	cout << "Score remaining: " << s << "  "; 
}

void printPlayer(player p)
{
	moveCursorTo(81, 18);
	cout << "Player: " << p.name;
}

void printMoveAnnouncement()
{
	moveCursorTo(81, 18);
	cout << "\x1b[91mNO AVAILABLE MOVE: SHUFLING";
	stop(500);
	cout << ".";
	stop(500);
	cout << ".";
	stop(500);
	moveCursorTo(81, 18);
	cout << "                              \x1b[0m";
}

void printWin()
{
	moveCursorTo(92, 26);
	cout << "CONGRATULATION";
	stop(1000);
	moveCursorTo(95, 27);
	cout << "YOU WIN!";
	stop(2000);
}

void printInfoBoard(int *secondsptr, player p)
{
	printOuterLine();
	printTutorial();
	printScore(*secondsptr);
	printPlayer(p);
}

void printLeaderBoard()
{
	system("cls");
	moveCursorTo(40, 2);
	cout << "LEADERBBOARD";
	moveCursorTo(8, 7);
	cout << "-----------------------------------------------------------------------------";
	fstream fs;
	fs.open("leaderboard.txt");
	for (int i = 0; i < 10; i++)
	{
		moveCursorTo(10, (i+4)*2);
		string name;
		int score;
		getline(fs, name, ';');
		if (i == 0)
			cout << "\x1b[33m";
		fs >> score;
		fs.ignore();
		cout << i + 1 << "> " << name; moveCursorTo(80, (i + 4) * 2); cout << score;
		if (i == 0)
			cout << "\x1b[0m";
	}
	moveCursorTo(90, 28);
	cout << "press any keys to exit";
	fs.close();
}

void printWinBoard(player p, bool hard, bool & hardMode, bool & replay)
{
	system("cls");
	string sound = "appear.wav";
	stop(200);
	moveCursorTo(40, 10);
	makeSound(sound);
	cout << "PLAYER: " << p.name;
	stop(1000);
	moveCursorTo(40, 12);
	makeSound(sound);
	cout << "FINAL SCORE: " << p.score;
	stop(1000);
	makeSound(sound);
	if (!hard)
	{
		moveCursorTo(40, 18);
		cout << "press r to play again";
		moveCursorTo(40, 19);
		cout << "press h to play hard mode";
	}
	moveCursorTo(40, 20);
	cout << "press ";  if (!hard) cout << "other "; else cout << "any "; cout << "keys to exit";
	makeSound(sound);
	char option;
	switch (option = _getch())
	{
	case 'r':
		break;
	case 'h':
		hardMode = true;
	default:
		replay = false;
		break;
	}
}

//for hard mode
void printBoxRow(tile* a, int length)
{
	for (int i = 0; i <= length; i++)
	{
		box(*(a + i));
	}
}

void pushBox(tile* a, int length, int removedBox)
{
	for (int i = removedBox; i < length; i++)
	{
		(a + i)->pokemon = (a + i + 1)->pokemon;
		(a + i)->empty = (a + i + 1)->empty;
	}
	(a + length)->empty = true;
}