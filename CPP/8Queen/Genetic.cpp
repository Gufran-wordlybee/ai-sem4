#include<iostream>
#include<vector>
using namespace std;

const int N = 8;
const int POP_SIZE = 26;

vector<int> randomBoard() {
    vector<int> board(N);
    for (int i = 0; i < N; i++)
        board[i] = rand() % N;
    return board;
}
// conflicts
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


double fitness(vector<int> &board) {
    return 1.0 / (1 + heuristic(board));
}

// Select 2 parents (roulette style simplified)
pair<vector<int>, vector<int>> selection(vector<vector<int>> &pop) {
    int a = rand() % POP_SIZE;
    int b = rand() % POP_SIZE;
    return {pop[a], pop[b]};
}


vector<int> crossover(vector<int> &p1, vector<int> &p2) {
    int point = rand() % (N - 1) + 1;
    vector<int> child;

    for (int i = 0; i < point; i++)
        child.push_back(p1[i]);
    for (int i = point; i < N; i++)
        child.push_back(p2[i]);

    return child;
}


void mutate(vector<int> &board) {
    if ((rand() % 100) < 10) { // 10% mutation
        int col = rand() % N;
        board[col] = rand() % N;
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


    vector<vector<int>> population;
    for (int i = 0; i < POP_SIZE; i++)
        population.push_back(randomBoard());


    vector<vector<int>> newPopulation;

    while (newPopulation.size() < POP_SIZE) {

        auto [p1, p2] = selection(population);


        vector<int> child = crossover(p1, p2);


        mutate(child);


        newPopulation.push_back(child);
    }


    cout << "New Population:\n";
    for (auto &board : newPopulation) {
        printBoard(board);
        cout << "Heuristic: " << heuristic(board) << "\n\n";
    }

    return 0;
}