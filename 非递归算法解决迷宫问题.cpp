#include <iostream>
#include <algorithm>
using namespace std;
struct Coordinate {
    int i;
    int j;
    int direction;
};

bool isValid(int i, int j, int rows, int cols) {
    return i >= 0 && i < rows&& j >= 0 && j < cols;
}

void solveMaze(int** maze, int rows, int cols, Coordinate* path, int& pathLength,Coordinate&x) {
    int stackSize = rows * cols;
    Coordinate* stack = new Coordinate[stackSize];

    Coordinate start = x;
    int top = 0;
    stack[top] = start;

    while (top >= 0) {
        Coordinate current = stack[top];
        top--;

        int i = current.i;
        int j = current.j;
        int direction = current.direction;

        if (!isValid(i, j, rows, cols) || maze[i][j] == 1) {
            continue;
        }

        maze[i][j] = 1;

        if (i == rows - 1 && j == cols - 1) {
            path[pathLength++] = current;
            break;
        }

        path[pathLength++] = current;

        Coordinate up = { i - 1, j, 0 };
        Coordinate right = { i, j + 1, 1 };
        Coordinate down = { i + 1, j, 2 };
        Coordinate left = { i, j - 1, 3 };

        top++;
        stack[top] = left;
        top++;
        stack[top] = down;
        top++;
        stack[top] = right;
        top++;
        stack[top] = up;
    }

    delete[] stack;
}

int main() {
    int rows;
    int cols;
    Coordinate x;
    cout << "please enter the size of rows and cols"<<endl;
    cin >> rows >> cols;
    cout << "please enter the maze"<<endl;
    int** maze = new int* [rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> maze[i][j];
        }
    }
    cout << "please enter where to start" << endl;
    cin >> x.i >> x.j>>x.direction;
    
    Coordinate* path = new Coordinate[rows * cols];
    int pathLength = 0;

    solveMaze(maze, rows, cols, path, pathLength,x);

    for (int i = pathLength-1; i >=0; i--) {
        std::cout << "(" << path[i].i << ", " << path[i].j << ", " << path[i].direction << ")" << std::endl;
    }

    for (int i = 0; i < rows; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    delete[] path;

    return 0;
}
