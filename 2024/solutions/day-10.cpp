#include "utilities.h"

struct Point{
    int x, y;
    Point(int x = 0, int y = 0)
        : x(x), y(y) {}    
};

vector<pair<int, int>> directions = {
    { 0,  1}, // right
    { 1,  0}, // down
    { 0, -1}, // left
    {-1,  0} // up
};

bool is_valid_point(const matrix<char>& map, Point pt) {
    return(pt.x >= 0 && pt.x < map.size() && pt.y >= 0 && pt.y < map[0].size());
}

vector<Point> find_trailheads(const matrix<char>& map) {
    vector<Point> trailheads;

    for(int x = 0; x < map.size(); ++x)
        for(int y = 0; y < map[0].size(); ++y)
            if(map[x][y] == '0')
                trailheads.push_back({x, y});

    return trailheads;
}

int trailhead_score(const matrix<char>& map, Point trailhead, matrix<bool>& visited) {
    if (!is_valid_point(map, trailhead) || visited[trailhead.x][trailhead.y]) {
        return 0;
    }

    char current_value = map[trailhead.x][trailhead.y];

    visited[trailhead.x][trailhead.y] = true;
    int count = (current_value == '9');

    for (auto d : directions) {
        Point next = { trailhead.x + d.first, trailhead.y + d.second };
        if (is_valid_point(map, next) && map[next.x][next.y] - current_value == 1) {
            count += trailhead_score(map, next, visited);
        }
    }

    // Comment if we want pt. 1
    visited[trailhead.x][trailhead.y] = false;
    return count;
}

int sum_scores(const matrix<char>& map) {
    vector<Point> trailheads = find_trailheads(map);
    int sum = 0;

    for(auto th : trailheads) {
        matrix<bool> visited(map.size(), vector<bool>(map[0].size(), 0));
        sum += trailhead_score(map, th, visited);
    }

    return sum;    
}

int main() {
    std::ifstream in = open_file("10");
    if(!in) return 1;

    matrix<char> map;
    input_matrix(in, map, split_to_chars);
    //print_matrix(map);

    std::cout << sum_scores(map) << std::endl;
    
    in.close();
    return 0;
}