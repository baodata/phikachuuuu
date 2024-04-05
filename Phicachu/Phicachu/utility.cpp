#include "utility.h"
#include <iostream>
#include <thread>
#include <string>
#include <fstream>

using namespace std;

void getPlayer(player& p)
{
    system("cls");
    moveCursorTo(50, 12);
    cout << "Enter your name: ";
    cin >> ws;
    getline(cin, p.name);
    p.score = 0;
}
void savePlayer(player p)
{
    fstream file;
    file.open("leaderboard.txt", ios::app);
    file << p.name << ";" << p.score << endl;
    file.close();
}

void sortFile()
{
    fstream file;
    file.open("leaderboard.txt", ios::in);
    player* p = new player[11];
    int i = 0;
    while (!file.eof() && i < 11)
    {
        getline(file, p[i].name, ';');
        file >> p[i].score;
        file.ignore();
        i++;
    }
    file.close();
    player temp;
    for (int j = 0; j < i - 1; j++) {
        for (int k = j + 1; k < i; k++) {
            if (p[j].score < p[k].score) {
                temp = p[j];
                p[j] = p[k];
                p[k] = temp;
            }
        }
    }
    file.open("leaderboard.txt", ios::out);
    if (i > 10)
        i = 10;
    for (int j = 0; j < i; j++) 
    {
        file << p[j].name << ";" << p[j].score << endl;
    }
    file.close();
    delete[] p;
}

void readBackground(tile** table, int x, int y, string filename)
{
    fstream file(filename);
    string line;
    for (int i = 1; i <= y; i++)    // table y
    {
        for (int k = 0; k < 3; k++)     // 3 dong picture
        {
            getline(file, line);
            for (int j = 1; j <= x; j++)    //table x
            {
                table[i][j].picture[k] = line.substr(7 * (j - 1), 7 );
            }
        }
    }
}


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