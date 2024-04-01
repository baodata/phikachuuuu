#pragma once
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

struct tile
{
	char pokemon;
	bool empty = false;
	bool chosen = false;
	int xCursor;
	int yCursor;
	bool hinted = false;
};

struct pointer
{
	int x = 1;
	int y = 1;
};

struct menuButton
{
	char data[15];
	bool chosen = false;
	int xCursor;
	int yCursor;
	char description[55];
};

struct player
{
	char name[10];
	int score;
};

void stop(int i);
void moveCursorTo(int x, int y);
void swapPoke(char& a, char& b);