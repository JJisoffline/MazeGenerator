#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

const int width = 31;   // Must be odd
const int height = 21;  // Must be odd

// Directions
int directions[4][2] = {
    {0, -2},  // North
    {0, 2},   // South
    {2, 0},   // East
    {-2, 0}   // West
};

// Checks if it's not the edge of the map and is a wall that you can tunnel through
bool is_valid_move(vector<vector<char>>& maze, int x, int y) {
    return x > 0 && x < width - 1 && y > 0 && y < height - 1 && maze[y][x] == '#';
}

void carve_maze(vector<vector<char>>& maze, int x, int y, mt19937& rng) {
    maze[y][x] = ' ';

    // Shuffle directions
    shuffle(begin(directions), end(directions), rng);

    for (int i = 0; i < 4; ++i) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (is_valid_move(maze, nx, ny)) {
            // Remove the wall between the current and the next cell
            maze[y + directions[i][1] / 2][x + directions[i][0] / 2] = ' ';
            carve_maze(maze, nx, ny, rng);
        }
    }
}

vector<vector<char>> generate_maze() {
    vector<vector<char>> maze(height, vector<char>(width, '#'));

    // Random starting point
    random_device rd;
    mt19937 rng(rd());

    int start_x = rng() % (width / 2) * 2 + 1;
    int start_y = rng() % (height / 2) * 2 + 1;

    carve_maze(maze, start_x, start_y, rng);

    return maze;
}

void print_maze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> maze = generate_maze();
    print_maze(maze);
    return 0;
}