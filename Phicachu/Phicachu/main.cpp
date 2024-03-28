#include "game.h"
#include "menu.h"

using namespace std;

int main()
{
	char pika[] = "pikachu.txt";
	readAndWriteFile(pika);
	customMode();
	return 0;
}