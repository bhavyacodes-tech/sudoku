#include <iostream>
using namespace std;

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    cout << "Solved Sudoku Grid:" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if it's safe to place num at grid[row][col]
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;
    bool emptyCellFound = false;

    // Find an empty cell
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyCellFound = true;
                break;
            }
        }
        if (emptyCellFound)
            break;
    }

    // If no empty cell is found, puzzle solved
    if (!emptyCellFound)
        return true;

    // Try digits 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively try to fill the rest of the grid
            if (solveSudoku(grid))
                return true;

            // Backtrack if placing num doesn’t lead to a solution
            grid[row][col] = 0;
        }
    }

    // If no valid number can be placed, trigger backtracking
    return false;
}

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku grid (use 0 for empty cells):" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            while (true) {
                cout << "Enter value for cell [" << row + 1 << "][" << col + 1 << "] (0-9): ";
                cin >> grid[row][col];

                if (grid[row][col] >= 0 && grid[row][col] <= 9)
                    break;
                else
                    cout << "Invalid input! Please enter a number between 0 and 9." << endl;
            }
        }
    }

    cout << "\nSolving Sudoku..." << endl;

    if (solveSudoku(grid))
        printGrid(grid);
    else
        cout << "No solution exists for the given Sudoku puzzle." << endl;

    return 0;
}
