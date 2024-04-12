#include "menu.h"
#include "game.h"
#include "linkedList.h"
#include "utility.h"
#include "render.h"
#include <iostream>
using namespace std;
int main()
{
	tile** table = new tile * [6 + 2];
	for (int i = 0; i < 6 + 2; i++)
		table[i] = new tile[6 + 2];
	createGame(table, 6, 6, 15);
	pointer p;
	printTable(table, p, 6, 6);
	Ref* linked = convert2LinkedList(table, 6, 6);
	system("cls");
	for (int i = 1; i <= 6; i++)
		displayList(linked[i]);
	int a;
	cin >> a;
	menu();
	return 0;
}