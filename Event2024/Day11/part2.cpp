#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

#define NUM_ROUNDS 10

int main() {
    int total = 0;
    ifstream infile("../input2.txt");
    map<char, vector<char>> termiteMap;
    vector termites(1, 'Z');
    
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        char parent;
        vector<char> children;
        
        getline(ss, token, ':');
        parent = token[0];
        
        while (getline(ss, token, ',')) {
            children.push_back(token[0]);
        }
        termiteMap[parent] = children;
    }
    infile.close();
    
    for (int n = 0; n < NUM_ROUNDS; n++) {
        int i = 0;
        while (i < termites.size()) {
            char termite = termites[i];
            termites.erase(termites.begin() + i);
            for (char c : termiteMap[termite]) {
                termites.insert(termites.begin() + i, c);
            }
            i += termiteMap[termite].size();
        }
        cout << termites.size() << endl;
    }
    
    total = termites.size();

    cout << "Total: " << total << endl;

    return 0;
}
