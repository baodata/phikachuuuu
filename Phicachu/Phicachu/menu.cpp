#include "menu.h"

using namespace std;

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
    strcpy_s(button[4].description, " ");

    string background;
    string sound;
    thread runGame;
    thread timer;
    while (true)
    {
        int seconds;
        int* secondsptr = &seconds;
        bool returnToMenu = false;
        bool hardMode = false;
        bool replay = true;
        bool exit = false;
        bool quit = false;
        bool hard = false;
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
                sound = "bloop.wav";
                makeSound(sound);
                button[pointed].chosen = false;
                if (pointed < 4)
                    pointed++;
                button[pointed].chosen = true;
                break;
            case KEY_UP:
                sound = "bloop.wav";
                makeSound(sound);
                button[pointed].chosen = false;
                if (pointed > 0)
                    pointed--;
                button[pointed].chosen = true;
                break;
            case ' ':
            case '\r':
            case '\n':
                sound = "bloop(high).wav";
                makeSound(sound);
                player p;
                p.name.clear();
                returnToMenu = true;
                switch (pointed)
                {
                case 0:
                    hard = false;
                    hardMode = false;
                    replay = true;
                    while (replay)
                    {
                        getPlayer(p);
                        *secondsptr = 200;
                        timer = thread(countDown, secondsptr);
                        runGame = thread(level, secondsptr, p, hard, ref(hardMode), ref(replay));
                        runGame.join();
                        timer.join();
                    }
                    if (!hardMode)
                        break;
                case 1:
                    hard = true;
                    getPlayer(p);
                    *secondsptr = 250;
                    timer = thread(countDown, secondsptr);
                    runGame = thread(level, secondsptr, p, hard, ref(hardMode), ref(replay));
                    runGame.join();
                    timer.join();
                    _getch();
                    break;
                case 2:
                    *secondsptr = NULL;
                    background = "blank.txt";
                    system("cls");
                    int x, y, pokeNum; 
                    moveCursorTo(40, 8);
                    cout << "note: at least one of the two sizes must be even.";
                    moveCursorTo(40, 10);
                    cout << "Enter width (max: 8): ";
                    cin >> x;
                    moveCursorTo(40, 12);
                    cout << "Enter height (max: 8): ";
                    cin >> y;
                    moveCursorTo(40, 14);
                    cout << "Enter number of diferent Pokemons (max: 26): ";
                    cin >> pokeNum;
                    moveCursorTo(40, 16);
                    cout << "Current difficulty: ";
                    moveCursorTo(40, 17);
                    cout << "Press c to change, enter/space to confirm";
                    while (true)
                    {
                        moveCursorTo(70, 16);
                        if (hard)
                            cout << "hard";
                        else
                            cout << "easy";
                        char option;
                        bool done = false;
                        switch (option = _getch())
                        {
                        case 'c':
                            hard = !hard;
                            break;
                        case ' ':
                        case '\r':
                        case '\n':
                            done = true;
                            break;
                        }
                        if (done)
                            break;
                    }
                    game(x, y, secondsptr, p, hard, background, pokeNum, exit);
                    if (!exit)
                    {
                        sound = "win_level.wav";
                        makeSound(sound);
                        printWin();
                    }
                    break;
                case 3:
                    printLeaderBoard();
                    while (_getch())
                    {
                        break;
                    }
                    break;
                case 4:
                    quit = true;
                    break;
                default:
                    returnToMenu = false;
                    break;
                }
            }
            if (returnToMenu)
              break;
        }
        if (quit)
            break;
    }
}