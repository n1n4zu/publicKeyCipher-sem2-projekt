#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "KeyGenerator.h"
#include "Menu.h"
#include "PublicKeyCipher.h"

using namespace std;

int main() {
    while (true) {
        system("pwd");
        Menu::clear();
        Menu::mainMenu();
        string option;
        cin >> option;

        if (option == "1") {
            string name;
            cout << "Input key name:\n> ";
            cin >> name;
            cout << "Generating keys...\n";
            KeyGenerator::makeKeyFiles(name, 4096);
            cout << "Keys generated.\n";
        } else if (option == "2") {
            string filename;
            cout << "Input file name:\n> ";
            cin >> filename;

            ifstream file(filename, ios::binary);
            if (!file) {
                cerr << "ERROR: File does not exist!\n";
                continue;
            }

            string mode;
            cout << "Choose mode (encrypt/decrypt):\n> ";
            cin >> mode;

            if (mode == "encrypt") {
                string pubKeyFilename;
                cout << "Input public key filename:\n> ";
                cin >> pubKeyFilename;

                ifstream pubKeyFile(pubKeyFilename);
                if (!pubKeyFile) {
                    cerr << "ERROR: File does not exist!\n";
                    continue;
                }

                vector<char> message((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                cout << "Encrypting and saving to encrypted.bin...\n";
                // Implement encryption logic here
            } else if (mode == "decrypt") {
                string privKeyFilename;
                cout << "Input private key filename:\n> ";
                cin >> privKeyFilename;

                ifstream privKeyFile(privKeyFilename);
                if (!privKeyFile) {
                    cerr << "ERROR: File does not exist!\n";
                    continue;
                }

                cout << "Reading " << filename << " and decrypting...\n";
                // Implement decryption logic here
            } else {
                cerr << "ERROR: Unknown mode. Choose 'encrypt' or 'decrypt'.\n";
            }
        } else if (option == "3") {
            break;
        }
    }

    return 0;
}