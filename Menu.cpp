#include "Menu.h"
#include <iostream>

void Menu::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Menu::mainMenu() {
    cout << "[1] Generate keys\n[2] Encrypt/Decrypt message\n[3] Exit\n> ";
}