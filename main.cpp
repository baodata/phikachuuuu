#include <iostream>
#include <cstdlib>
#include <ctime>

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

void emptyBox(int x, int y)
{
	moveCursorTo(x, y);
	cout << "       "; moveCursorTo(x, y + 1);
	cout << "       "; moveCursorTo(x, y + 2);
	cout << "       "; moveCursorTo(x + 7, y);
}

struct title {
	char pokemon;
	bool empty = false;
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

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			cout << table[i][j].pokemon << " ";
		cout << endl;
	}

	int xloc = 1;
	int yloc = 10;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (table[i][j].empty == true)
				emptyBox(xloc, yloc);
			else
				box(xloc, yloc,table[i][j].pokemon);
			moveCursorTo(xloc, yloc);
			xloc += 7;
		}
		xloc = 1;
		yloc += 3;
	}

	cout << endl << endl << endl;

	//giai phong
	for (int i = 0; i < y; i++) {
		delete[] table[i];
	}
	delete[] table;
	delete[] Pokemon;
	return 0;
}