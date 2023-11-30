#include <iostream>
#include <vector>
using namespace std;

struct PathNode {
    int x;
    int y;
    vector<int> path;  
};

bool isValid(int x, int y, const vector<vector<int>>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();
    return x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] == 0;
}


void solveMazeRecursive(int x, int y, int targetX, int targetY, vector<int>& currentPath, vector<PathNode>& allPaths, const vector<vector<int>>& maze) {
    if (x == targetX && y == targetY) {  
        PathNode node;
        node.x = x;
        node.y = y;
        node.path = currentPath;
        allPaths.push_back(node);
        return;
    }

    int directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    for (int i = 0; i < 4; i++) {
        int nextX = x + directions[i][0];
        int nextY = y + directions[i][1];

        if (isValid(nextX, nextY, maze)) {
            vector<vector<int>> updatedMaze = maze;
            updatedMaze[x][y] = 2;
            currentPath.push_back(i);
            solveMazeRecursive(nextX, nextY, targetX, targetY, currentPath, allPaths, updatedMaze);
            currentPath.pop_back();
            updatedMaze[x][y] = 0;
        }
    }
}

void printMazeWithPaths(const vector<PathNode>& allPaths, int startX, int startY, int targetX, int targetY, const vector<vector<int>>& maze) {
    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<int>> mazeOutput(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mazeOutput[i][j] = maze[i][j] == 0 ? 0 : 1;
        }
    }

    for (const auto& path : allPaths) {
        int x = startX;
        int y = startY;

        for (int dir : path.path) {
            switch (dir) {
            case 0:
                x -= 1;
                mazeOutput[x][y] = 2;
                break;
            case 1:
                y += 1;
                mazeOutput[x][y] = 3;
                break;
            case 2:
                x += 1;
                mazeOutput[x][y] = 4;
                break;
            case 3:
                y -= 1;
                mazeOutput[x][y] = 5;
                break;
            default:
                break;
            }
        }
    }

   
    mazeOutput[startX][startY] = 6;
    mazeOutput[targetX][targetY] = 7;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            switch (mazeOutput[i][j]) {
            case 0:
                cout << 0 << " ";
                break;
            case 1:
                cout << 1 << " ";
                break;
            case 2:
                cout << "↑" << " ";
                break;
            case 3:
                cout << "→" << " ";
                break;
            case 4:
                cout << "↓" << " ";
                break;
            case 5:
                cout << "←" << " ";
                break;
            case 6:
                cout << "S" << " ";  
                break;
            case 7:
                cout << "T" << " ";  
                break;
            default:
                break;
            }
        }
        cout << endl;
    }
}

int main() {
    int rows, cols;
    cout << "please enter the size of rows and cols" << endl;
    cin >> rows >> cols;

    vector<vector<int>> maze(rows, vector<int>(cols, 0));

    cout << "please enter the maze" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> maze[i][j];
        }
    }

    int startX, startY, targetX, targetY;
    cout << "Enter the starting position (x y): ";
    cin >> startX >> startY;
    cout << "Enter the target position (x y): ";
    cin >> targetX >> targetY;

    vector<int> currentPath;
    vector<PathNode> allPaths;

    solveMazeRecursive(startX, startY, targetX, targetY, currentPath, allPaths, maze);

    cout << "Number of paths found: " << allPaths.size() << endl;
    printMazeWithPaths(allPaths, startX, startY, targetX, targetY, maze);

    return 0;
}