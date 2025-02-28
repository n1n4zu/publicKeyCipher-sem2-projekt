#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "KeyGenerator.h"
#include "Menu.h"
#include "PublicKeyCipher.h"

using namespace std;

pair<string, vector<long long>> readEncryptedFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Could not open encrypted file.");
    }

    // Odczytaj oryginalną nazwę pliku
    string originalFilename;
    getline(file, originalFilename);

    // Odczytaj zaszyfrowane bloki
    vector<long long> encryptedBlocks;
    long long block;
    while (file.read(reinterpret_cast<char*>(&block), sizeof(block))) {
        encryptedBlocks.push_back(block);
    }

    return {originalFilename, encryptedBlocks};
}

void writeEncryptedFile(const string& filename, const vector<long long>& encryptedBlocks, const string& originalFilename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Could not open file for writing encrypted data.");
    }

    // Zapisz oryginalną nazwę pliku
    file << originalFilename << "\n";

    // Zapisz zaszyfrowane bloki
    for (long long block : encryptedBlocks) {
        file.write(reinterpret_cast<const char*>(&block), sizeof(block));
    }
}

int main() {
    while (true) {
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

                long long keySize, n, e;
                char comma;
                pubKeyFile >> keySize >> comma >> n >> comma >> e;
                pubKeyFile.close();

                vector<char> message((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                cout << "Encrypting and saving to encrypted.bin...\n";
                auto encryptedBlocks = PublicKeyCipher::encryptMessage(message, {n, e}, keySize / 8 - 1);
                writeEncryptedFile("encrypted.bin", encryptedBlocks, filename);
                cout << "Encryption complete. Saved to encrypted.bin.\n";
            } else if (mode == "decrypt") {
                string privKeyFilename;
                cout << "Input private key filename:\n> ";
                cin >> privKeyFilename;

                ifstream privKeyFile(privKeyFilename);
                if (!privKeyFile) {
                    cerr << "ERROR: File does not exist!\n";
                    continue;
                }

                long long keySize, n, d;
                char comma;
                privKeyFile >> keySize >> comma >> n >> comma >> d;
                privKeyFile.close();

                cout << "Reading " << filename << " and decrypting...\n";
                auto [originalFilename, encryptedBlocks] = readEncryptedFile(filename);
                auto decryptedMessage = PublicKeyCipher::decryptMessage(encryptedBlocks, encryptedBlocks.size() * (keySize / 8 - 1), {n, d}, keySize / 8 - 1);

                // Użyj oryginalnej nazwy pliku do zapisania deszyfrowanych danych
                ofstream outputFile(originalFilename, ios::binary);
                if (!outputFile) {
                    cerr << "ERROR: Could not create output file.\n";
                    continue;
                }

                outputFile.write(decryptedMessage.data(), decryptedMessage.size());
                cout << "Decryption complete. Saved to " << originalFilename << ".\n";
            } else {
                cerr << "ERROR: Unknown mode. Choose 'encrypt' or 'decrypt'.\n";
            }
        } else if (option == "3") {
            break;
        }
    }

    return 0;
}