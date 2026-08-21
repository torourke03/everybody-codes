#include <fstream>
#include <iostream>
#include <string>
using namespace std;


int main(int argc, char** argv) {
    ifstream inFile("notes.txt");
    string text;
    int numPotions = 0;
    
    getline(inFile, text);
    inFile.close();
    cout << text << '\n';
    
    for (char c : text) {
        switch (c) {
            case 'A':
                break;
            case 'B':
                numPotions += 1;
                break;
            case 'C':
                numPotions += 3;
                break;
        }
    }
    
    cout << "Total: " << numPotions << "\n";
    
    return 0;
}
