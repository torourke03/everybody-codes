#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
    std::string filename = "input.txt";
    if (argc == 2) filename = argv[1];
    std::ifstream inFile(filename);
    int total = 0;
    std::string line;

    std::getline(inFile, line);
    std::stringstream ss(line);
    while (std::getline(ss, line, ',')) {
        int count = stoi(line);
        int i = 1;
        while (i < 100) {
            if (count <= i * i) {
                total += (i * i) - count;
                break;
            }
            i++;
        }
    }
    inFile.close();

    std::cout << "Total: " << total << std::endl;
    return 0;
}
