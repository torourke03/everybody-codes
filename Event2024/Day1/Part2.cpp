#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char** argv) {
    ifstream inFile("notes2.txt");
    string text;
    int numPotions = 0;
    
    getline(inFile, text);
    inFile.close();
    cout << text << '\n';
    
    for (int i = 0; i < text.length(); i += 2) {
        char firstEnemy = text.at(i);
        char secondEnemy = text.at(i + 1);
        cout << "Pairing: " << firstEnemy << secondEnemy << "\n";
                
        switch (firstEnemy) {
            case 'A':
                break;
            case 'B':
                numPotions += 1;
                cout << "Adding " << 1 << "\n";
                break;
            case 'C':
                numPotions += 3;
                cout << "Adding " << 3 << "\n";
                break;
            case 'D':
                numPotions += 5;
                cout << "Adding " << 5 << "\n";
                break;
            case 'x':
                break;
            default:
                cout << "Error: " << firstEnemy << " is not a valid first enemy\n";
        }
        switch (secondEnemy) {
            case 'A':
                break;
            case 'B':
                numPotions += 1;
                cout << "Adding " << 1 << "\n";
                break;
            case 'C':
                numPotions += 3;
                cout << "Adding " << 3 << "\n";
                break;
            case 'D':
                numPotions += 5;
                cout << "Adding " << 5 << "\n";
                break;
            case 'x':
                break;
            default:
                cout << "Error: " << secondEnemy << " is not a valid second enemy\n";
        }
        
        if (firstEnemy != 'x' && secondEnemy != 'x') {
            numPotions += 2;
        }
    }
    
    cout << "Total: " << numPotions << "\n";
    
    return 0;
}
