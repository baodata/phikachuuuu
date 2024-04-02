#include "menu.h"
#include "utility.h"
#include "game.h"
#include "render.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <thread>

using namespace std;

void readAndWriteFile(char filename[]) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line))
            cout << "\x1b[33m" << line << "\x1b[0m" << endl;
        inputFile.close();
    }
    else {
        cout << "Game PIKACHU" << endl;
    }
}

void menu()
{
    int pointed = 0;
    menuButton* button = new menuButton[5];
    for (int i = 0; i < 5; i++)
    {
        button[i].xCursor = 10;
        button[i].yCursor = 14 + 3 * i;
    }
    button[pointed].chosen = true;
    strcpy_s(button[0].data, "EASY");
    strcpy_s(button[0].description, "A standard mode for new players.");
    strcpy_s(button[1].data, "\x1b[9mHARD\x1b[0m");
    strcpy_s(button[1].description, "We are currently not good enough to code this.");
    strcpy_s(button[2].data, "CUSTOM");
    strcpy_s(button[2].description, "Custom your way into the game.");
    strcpy_s(button[3].data, "LEADERBOARD");
    strcpy_s(button[3].description, "Hall of fame.");
    strcpy_s(button[4].data, "EXIT");
    strcpy_s(button[4].description, "Embrace cowardice?");
    bool exit = false;
    player p;
    thread runGame;
    thread timer;
    while (true)
    {
        int seconds;
        int* secondsptr = &seconds;
        bool returnToMenu = false;
        cout << "\x1b[?25l";
        system("cls");
        char pika[] = "pikachu.txt";
        readAndWriteFile(pika);
        for (int i = 0; i < 5; i++)
        {
            stop(150);
            menuBox(button[i]);
        }
        while (true)
        {
            for (int i = 0; i < 5; i++)
            {
                menuBox(button[i]);
            }
            char arrow;
            switch (arrow = _getch())
            {
            case KEY_DOWN:
                button[pointed].chosen = false;
                if (pointed < 4)
                    pointed++;
                button[pointed].chosen = true;
                break;
            case KEY_UP:
                button[pointed].chosen = false;
                if (pointed > 0)
                    pointed--;
                button[pointed].chosen = true;
                break;
            case ' ':
            case '\r':
            case '\n':
                returnToMenu = true;
                switch (pointed)
                {
                case 0:
                    getPlayer(p);
                    *secondsptr = 200;
                    timer = thread(countDown, secondsptr);
                    runGame = thread(easy, secondsptr, p);
                    runGame.join();
                    timer.join();
                    break;
                case 2:
                    *secondsptr = NULL;
                    system("cls");
                    cout << "dai, cao?";
                    int x, y;
                    cin >> x >> y;
                    game(x, y, secondsptr, p);
                    break;
                case 3:
                    printLeaderBoard();
                    while (_getch())
                    {
                        break;
                    }
                    break;
                case 4:
                    exit = true;
                    break;
                default:
                    returnToMenu = false;
                    break;
                }
            }
            if (returnToMenu)
              break;
        }
        if (exit)
            break;
    }
}