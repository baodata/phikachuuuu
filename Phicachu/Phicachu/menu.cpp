#include "menu.h"
#include <fstream>
#include <iostream>
#include <string>

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
        cout << "L?i khi m? file." << endl;
    }
}