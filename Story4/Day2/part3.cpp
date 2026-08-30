#include <deque>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::set<std::pair<int, int>> findAllLocations(std::pair<int, int>& start, std::vector<std::pair<int, int>>& beacons);

int main() {
    const std::vector<std::pair<int, int>> adj = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int total = 0;
    std::ifstream infile("everybody_codes_e4_q02_p3.txt");
    std::pair<int, int> start;
    std::vector<std::pair<int, int>> beacons;
    
    std::string line;
    // Start
    getline(infile, line);
    std::stringstream ss(line);
    getline(ss, line, '[');
    getline(ss, line, ',');
    start.first = std::stoi(line);
    getline(ss, line, ']');
    start.second = std::stoi(line);
    
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
    infile.close();
    
    std::set<std::pair<int, int>> locations = findAllLocations(start, beacons);
    std::set<std::pair<int, int>> fireflies;
    for (std::pair<int, int> location : locations) {
        for (std::pair<int, int> a : adj) {
            std::pair<int, int> checkPos = {location.first + a.first, location.second + a.second};
            if (locations.find(checkPos) == locations.end()) {
                fireflies.insert(checkPos);
            }
        }
    }
    total = fireflies.size();
    
    std::cout << "Total: " << total << std::endl;

    return 0;
}

std::set<std::pair<int, int>> findAllLocations(std::pair<int, int>& start, std::vector<std::pair<int, int>>& beacons) {
    std::set<std::pair<int, int>> visited;
    std::deque<std::pair<int, int>> q;
    visited.insert(start);
    q.push_back(start);
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto pos = q.front();
            q.pop_front();
            for (auto beacon : beacons) {
                std::pair<int, int> checkPos = {(pos.first + beacon.first) / 2, (pos.second + beacon.second) / 2};
                if (visited.find(checkPos) == visited.end()) {
                    visited.insert(checkPos);
                    q.push_back(checkPos);
                }
            }
        }
    }
    
    return visited;
}