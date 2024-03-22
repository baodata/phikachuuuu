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

void box(int x ,int y,char poke)
{
	moveCursorTo(x, y);
	cout << " ----- "; moveCursorTo(x,y+1);
	cout << "|  " << poke << "  |"; moveCursorTo(x, y+2);
	cout << " ----- "; moveCursorTo(x + 7, y);
}

void poinedBox(int x, int y, char poke)
{
	moveCursorTo(x, y);
	cout << " ----- "; moveCursorTo(x, y + 1);
	cout << "|\x1b[47m  \x1b[30m" << poke << "  \x1b[0m|"; moveCursorTo(x, y + 2);
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
		Pokemon[i] = Pokemon[i+1] = rand() % 5 + 'A';
		//cout << Pokemon[i] << " " << Pokemon[i+1] << " ";
	}
	//random
	for (int i = 0; i < size; i++)
	{
		swap(Pokemon[i], Pokemon[rand() % size]);
	}

	//for (int i = 0; i < size; i ++)
		//cout << Pokemon[i] << " ";
	//cout << endl << endl;
	//////////////////////////////////////////////////////
	title** table  = new title* [y];

	for (int i = 0; i < y; i++)
		table[i] = new title[x];
	for (int i = 0; i < size; i++)
		table[i / x][i % x].pokemon = Pokemon[i];

	delete[] Pokemon;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			cout << table[i][j].pokemon << " ";
		cout << endl;
	}

	pointer a;
	cout << "\x1b[?25l"; // an con tro
	while (true)
	{
		int xloc = 10;
		int yloc = 10;
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				if (j == a.x && i == a.y)
					poinedBox(xloc, yloc, table[i][j].pokemon);
				else
					box(xloc, yloc, table[i][j].pokemon);
				moveCursorTo(xloc, yloc);
				xloc += 7;
			}
			xloc = 10;
			yloc += 3;
		}

		cout << endl << endl << endl;

		
		char arrow;
		switch (arrow = _getch())
		{
		case KEY_UP:
			if (a.y == 0)
				a.y = y-1;
			else
				a.y--;
			break;
		case KEY_DOWN:
			if (a.y == y - 1)
				a.y = 0;
			else
			a.y++;
			break;
		case KEY_RIGHT:
			if (a.x == x - 1)
				a.x = 0;
			else
				a.x++;
			break;
		case KEY_LEFT:
			if (a.x == 0)
				a.x = x - 1;
			else
				a.x--;
			break;
		}
		cout << "x: " << a.x << " y: " << a.y;
	}
	//giai phong
	for (int i = 0; i < y; i++) {
		delete[] table[i];
	}
	delete[] table;
	delete[] Pokemon;
	return 0;
}