#include "utility.h"
#include <iostream>
#include <thread>

using namespace std;

void stop(int i)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(i));
}

void moveCursorTo(int x, int y) //poe
{
	cout << "\x1b[" << y << ";" << x << "f";
}

void swapPoke(char& a, char& b)
{
    char temp = a;
    a = b;
    b = temp;
}

void countDown(int *s)
{
    while (*s > -200)
    {
        stop(1000);
        (*s)--;
    }
}