#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main() {
    const std::vector<std::pair<int, int>> adj = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int total = 0;
    std::ifstream infile("everybody_codes_e4_q02_p2.txt");
    std::pair<int, int> pos;
    std::vector<std::pair<int, int>> beacons;
    std::string moves;
    std::set<std::pair<int, int>> visited;
    std::set<std::pair<int, int>> fireflies;
    
    std::string line;
    // Start
    getline(infile, line);
    std::stringstream ss(line);
    getline(ss, line, '[');
    getline(ss, line, ',');
    pos.first = std::stoi(line);
    getline(ss, line, ']');
    pos.second = std::stoi(line);
    
    // Beacons
    for (int i = 0; i < 3; i++) {
        std::pair<int, int> beacon;
        getline(infile, line);
        ss.str(line);
        getline(ss, line, '[');
        getline(ss, line, ',');
        beacon.first = std::stoi(line);
        getline(ss, line, ']');
        beacon.second = std::stoi(line);
        beacons.push_back(beacon);
    }
    
    // Moves
    getline(infile, line);
    ss.str(line);
    getline(ss, line, '=');
    getline(ss, moves);
    infile.close();
    
    visited.insert(pos);
    for (char c : moves) {
        int i = c - 'A';
        pos = {(pos.first + beacons[i].first) / 2, (pos.second + beacons[i].second) / 2};
        visited.insert(pos);
    }
    
    for (auto ball : visited) {
        for (auto a : adj) {
            std::pair<int, int> firefly = {ball.first + a.first, ball.second + a.second};
            if (visited.find(firefly) == visited.end()) {
                fireflies.insert(firefly);
            }
        }
    }
    total = fireflies.size();
    
    std::cout << "Total: " << total << std::endl;

    return 0;
}
