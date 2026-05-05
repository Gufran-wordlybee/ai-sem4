#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 8;
const int MAX_STEPS = 10000;
const int RANDOM_WALK_PROB = 20;

vector<int> generateRandomBoard() {
    vector<int> board(N);
    for (int i = 0; i < N; i++)
        board[i] = rand() % N;
    return board;
}

int heuristic_NoOfConflicts(vector<int> &board) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (board[i] == board[j] ||
                abs(board[i] - board[j]) == abs(i - j))
                h++;
        }
    }
    return h;
}


vector<int> getBestNeighbor(vector<int> &board) {
    vector<int> best = board;
    int bestH = heuristic_NoOfConflicts(board);

    for (int col = 0; col < N; col++) {
        int originalRow = board[col];

        for (int row = 0; row < N; row++) {
            if (row == originalRow) continue;

            board[col] = row;
            int h = heuristic_NoOfConflicts(board);

            if (h < bestH) {
                bestH = h;
                best = board;
            }
        }

        board[col] = originalRow; 
    }

    return best;
}

vector<int> randomWalkMove(vector<int> &board) {
    vector<int> temp = board;
    int col = rand() % N;
    int row = rand() % N;
    temp[col] = row;
    return temp;
}

void printBoard(vector<int> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[j] == i) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}


vector<int> solve() {
    vector<int> current = generateRandomBoard();

    for (int step = 0; step < MAX_STEPS; step++) {
        int currH = heuristic_NoOfConflicts(current);

        if (currH == 0)
            return current;

        vector<int> neighbor = getBestNeighbor(current);
        int neighH = heuristic_NoOfConflicts(neighbor);

        // If better, move
        if (neighH < currH) {
            current = neighbor;
        }
        else {

            if ((rand() % 100) < RANDOM_WALK_PROB) {
                current = randomWalkMove(current);
            }
        }
    }

    return current;
}

int main() {
    srand(time(0));

    vector<int> solution = solve();

    cout << "Final Board:\n";
    printBoard(solution);
    cout << "heuristic_NoOfConflicts: " << heuristic_NoOfConflicts(solution) << endl;

    return 0;
}