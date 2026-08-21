#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int total = 0;
    ifstream infile("../input1.txt");
    vector<int> brightnesses;
    int stamps[] = {10, 5, 3, 1};
    
    string line;
    while (getline(infile, line)) {
        brightnesses.push_back(stoi(line));
    }
    infile.close();

    for (int i = 0; i < brightnesses.size(); i++) {
        int brightness = brightnesses[i];
        int count = 0;
        cout << "Brightness level: " << brightness << endl;
        for (int stamp : stamps) {
            count = brightness / stamp;
            brightness -= stamp * count;
            cout << "Adding " << count << " " << stamp << "-dot stamps" << endl;
            total += count;
        }
        cout << endl;
        //total += count;
    }

    cout << "Total: " << total << endl;

    return 0;
}
