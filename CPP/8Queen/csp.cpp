#include <iostream>
#include <vector>
using namespace std;

const int N = 8;


bool checkConflicts(vector<int> &board, int col, int row) {
    for (int i = 0; i < col; i++) {
        if (board[i] == row || abs(board[i] - row) == abs(i - col))
            return false;
    }
    return true;
}

bool backtracking(vector<int> &board, int col) {
    if (col == N)
        return true; 

    for (int row = 0; row < N; row++) {
        if (checkConflicts(board, col, row)) {
            board[col] = row;

            if (backtracking(board, col + 1))
                return true;

            board[col] = -1;
        }
    }
    return false;
}

void printBoard(vector<int> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[j] == i) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
}

int main() {
    vector<int> board(N, -1);

    if (backtracking(board, 0)) {
        cout << "Solution Found:\n";
        printBoard(board);
    } else {
        cout << "No Solution Exists\n";
    }

    return 0;
}