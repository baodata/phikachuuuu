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
    strcpy_s(button[0].description, "The standard mode, you have 200 seconds to complete 3 levels.");
    strcpy_s(button[1].data, "HARD");
    strcpy_s(button[1].description, "A slightly harder mode, 250 seconds to complete 3 levels.");
    strcpy_s(button[2].data, "CUSTOM");
    strcpy_s(button[2].description, "Custom your way into the game.");
    strcpy_s(button[3].data, "LEADERBOARD");
    strcpy_s(button[3].description, "Hall of fame.");
    strcpy_s(button[4].data, "EXIT");
    strcpy_s(button[4].description, "Embrace cowardice?");
    bool exit = false;
    bool hard = false;
    string background;
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
            stop(100);
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
                player p;
                p.name.clear();
                returnToMenu = true;
                switch (pointed)
                {
                case 0:
                    hard = false;
                    getPlayer(p);
                    *secondsptr = 200;
                    timer = thread(countDown, secondsptr);
                    runGame = thread(level, secondsptr, p, hard);
                    runGame.join();
                    timer.join();
                    break;
                case 1:
                    hard = true;
                    getPlayer(p);
                    *secondsptr = 250;
                    timer = thread(countDown, secondsptr);
                    runGame = thread(level, secondsptr, p, hard);
                    runGame.join();
                    timer.join();
                    break;
                case 2:
                    *secondsptr = NULL;
                    background = "blank.txt";
                    system("cls");
                    cout << "dai, cao?";
                    int x, y;
                    cin >> x >> y;
                    game(x, y, secondsptr, p, hard, background);
                    printWin();
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