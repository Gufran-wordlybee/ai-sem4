#include <iostream>
#include <vector>
using namespace std;

const int N = 9;

bool isValid(vector<vector<int>> &board, int row, int col, int num) {
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;

    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}


bool backtracking(vector<vector<int>> &board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {

            if (board[row][col] == 0) { // empty cell

                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {

                        board[row][col] = num;

                        if (backtracking(board))
                            return true;

                        board[row][col] = 0; 
                    }
                }

                return false; 
            }
        }
    }
    return true;
}


void printBoard(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {

    vector<vector<int>> board = {
        {0,0,3,0,2,0,6,0,0},
        {9,0,0,3,0,5,0,0,1},
        {0,0,1,8,0,6,4,0,0},
        {0,0,8,1,0,2,9,0,0},
        {7,0,0,0,0,0,0,0,8},
        {0,0,6,7,0,8,2,0,0},
        {0,0,2,6,0,9,5,0,0},
        {8,0,0,2,0,3,0,0,9},
        {0,0,5,0,1,0,3,0,0}
    };

    if (backtracking(board)) {
        cout << "Solved Sudoku:\n";
        printBoard(board);
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}