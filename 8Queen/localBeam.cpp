#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 8;
const int BEAM_WIDTH = 4;
const int MAX_STEPS = 1000;


vector<int> randomBoard() {
    vector<int> board(N);
    for (int i = 0; i < N; i++)
        board[i] = rand() % N;
    return board;
}

int heuristic(vector<int> &board) {
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

vector<vector<int>> getNeighbors(vector<int> &board) {
    vector<vector<int>> neighbors;

    for (int col = 0; col < N; col++) {
        int original = board[col];

        for (int row = 0; row < N; row++) {
            if (row == original) continue;

            vector<int> temp = board;
            temp[col] = row;
            neighbors.push_back(temp);
        }
    }

    return neighbors;
}

void sortByHeuristic(vector<vector<int>> &states) {
    for (int i = 0; i < states.size(); i++) {
        for (int j = i + 1; j < states.size(); j++) {
            if (heuristic(states[j]) < heuristic(states[i])) {
                swap(states[i], states[j]);
            }
        }
    }
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

int main() {
    srand(time(0));

    vector<vector<int>> beam;
    for (int i = 0; i < BEAM_WIDTH; i++)
        beam.push_back(randomBoard());

    for (int step = 0; step < MAX_STEPS; step++) {

        for (auto &b : beam) {
            if (heuristic(b) == 0) {
                cout << "Solution Found:\n";
                printBoard(b);
                return 0;
            }
        }

        vector<vector<int>> allNeighbors;
        for (auto &b : beam) {
            vector<vector<int>> nbrs = getNeighbors(b);
            for (auto &n : nbrs)
                allNeighbors.push_back(n);
        }

        sortByHeuristic(allNeighbors);

        vector<vector<int>> nextBeam;
        for (int i = 0; i < BEAM_WIDTH && i < allNeighbors.size(); i++)
            nextBeam.push_back(allNeighbors[i]);

        beam = nextBeam;
    }

    cout << "No perfect solution found. Final states:\n";
    for (auto &b : beam) {
        printBoard(b);
        cout << "Heuristic: " << heuristic(b) << "\n\n";
    }

    return 0;
}