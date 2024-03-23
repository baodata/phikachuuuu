#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

void moveCursorTo(int x, int y) //poe
{
	cout << "\033[" << y << ";" << x << "H";
}

void box(int x ,int y,char poke)	//https://stackoverflow.com/questions/3753055/how-can-i-display-extended-ascii-codes-characters-in-perl
{
	moveCursorTo(x, y);
	cout << char(218) <<"-----" << char(191); moveCursorTo(x,y+1);
	cout << "|  " << poke << "  |"; moveCursorTo(x, y+2);
	cout << char(192) << "-----" << char(217);
}

void pointedBox(int x, int y, char poke)
{
	moveCursorTo(x, y);
	cout << " --*-- "; moveCursorTo(x, y + 1);
	cout << "*\x1b[47m  \x1b[30m" << poke << "  \x1b[0m*"; moveCursorTo(x, y + 2);
	cout << " --*-- "; moveCursorTo(x + 7, y);
}

void chosenBox(int x, int y, char poke)
{
	moveCursorTo(x, y);
	cout << " ----- "; moveCursorTo(x, y + 1);
	cout << "|\x1b[42m  \x1b[30m" << poke << "  \x1b[0m|"; moveCursorTo(x, y + 2);
	cout << " ----- "; moveCursorTo(x + 7, y);
}

void emptyBox(int x, int y)
{
	moveCursorTo(x, y);
	cout << "       "; moveCursorTo(x, y + 1);
	cout << "       "; moveCursorTo(x, y + 2);
	cout << "       "; moveCursorTo(x + 7, y);
}

void movePointer(int xmax, int ymax, int& x, int& y)
{

}

struct title {
	char pokemon;
	bool empty = false;
	int xCursor;
	int yCursor;
	bool chosen = false;
};

struct pointer
{
	int x = 0;
	int y = 0;
};



int main()
{
	srand(time(0));
	int x,y;
	cout << "nhap chieu dai, chieu cao";
	cin >> x >> y;
	int size = x * y;
	char* Pokemon = new char[size];
	//khoi tao
	for (int i = 0; i < size; i +=2)
	{
		Pokemon[i] = Pokemon[i+1] = rand() % 10 + 'A';
	}
	//random
	for (int i = 0; i < size; i++)
	{
		swap(Pokemon[i], Pokemon[rand() % size]);
	}
	title** table  = new title* [y];

	for (int i = 0; i < y; i++)
		table[i] = new title[x];
	for (int i = 0; i < size; i++)
		table[i / x][i % x].pokemon = Pokemon[i];

	delete[] Pokemon;

	pointer a;
	cout << "\x1b[?25l"; // an con tro
	system("cls");
	int xloc = 1;
	int yloc = 1;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			table[i][j].xCursor = xloc;
			table[i][j].yCursor = yloc;
			if (j == a.x && i == a.y)
			pointedBox(xloc, yloc, table[i][j].pokemon);
			else
			box(xloc, yloc, table[i][j].pokemon);
			moveCursorTo(xloc, yloc);
			xloc += 7;
		}
		xloc = 1;
		yloc += 3;
	}
	cout << endl << endl << endl;

	//for (int i = 0; i < y; i++)
	//{
	//	for (int j = 0; j < x; j++)
	//	{
	//		cout << table[i][j].xCursor;
	//		cout << table[i][j].yCursor << " ";
	//	}
	//	cout << endl;
	//	xloc = 10;
	//	yloc += 3;
	//}

	bool haveChosen = false;
	pointer chosen;

	while(true)
	{	
		char arrow;
		switch (arrow = _getch())
		{
		case KEY_UP:
			if (table[a.y][a.x].empty == true)
				emptyBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor);
			else if (table[a.y][a.x].chosen == false)
				box(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			else
				chosenBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			if (a.y == 0)
				a.y = y-1;
			else
				a.y--;
			pointedBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			break;
		case KEY_DOWN:
			if (table[a.y][a.x].empty == true)
				emptyBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor);
			else if (table[a.y][a.x].chosen == false)
				box(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			else
				chosenBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			if (a.y == y - 1)
				a.y = 0;
			else
			a.y++;
			pointedBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			break;
		case KEY_RIGHT:
			if (table[a.y][a.x].empty == true)
				emptyBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor);
			else if (table[a.y][a.x].chosen == false)
				box(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			else
				chosenBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			if (a.x == x - 1)
				a.x = 0;
			else
				a.x++;
			pointedBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			break;
		case KEY_LEFT:
			if (table[a.y][a.x].empty == true)
				emptyBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor);
			else if (table[a.y][a.x].chosen == false)
				box(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			else
				chosenBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			if (a.x == 0)
				a.x = x - 1;
			else
				a.x--;
			pointedBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			break;
		case ' ':
		case '\r':
		case '\n':
			chosenBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
			table[a.y][a.x].chosen = !table[a.y][a.x].chosen;
			if (haveChosen == false)
			{
				haveChosen = true;
				chosen.x = a.x;
				chosen.y = a.y;
			}
			else
			{
				if (table[chosen.y][chosen.x].pokemon == table[a.y][a.x].pokemon && (chosen.x != a.x || chosen.y != a.y))
				{
					table[chosen.y][chosen.x].empty = true;
					table[a.y][a.x].empty = true;
					emptyBox(table[chosen.y][chosen.x].xCursor, table[chosen.y][chosen.x].yCursor);
					emptyBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor);
				}
				else
				{
					pointedBox(table[a.y][a.x].xCursor, table[a.y][a.x].yCursor, table[a.y][a.x].pokemon);
					table[a.y][a.x].chosen = false;
					box(table[chosen.y][chosen.x].xCursor, table[chosen.y][chosen.x].yCursor, table[chosen.y][chosen.x].pokemon);
					table[chosen.y][chosen.x].chosen = false;
				}
				haveChosen = false;
			}
			break;
		}
	}
	//giai phong
	for (int i = 0; i < y; i++) {
		delete[] table[i];
	}
	delete[] table;
	delete[] Pokemon;
	return 0;
}