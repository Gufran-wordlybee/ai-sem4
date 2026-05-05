#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;
const char EMPTY = '.';
const char HUMAN = 'X';
const char AI    = 'O';
const int WIN_LINES[8][3] = {
    {0,1,2}, {3,4,5}, {6,7,8},
    {0,3,6}, {1,4,7}, {2,5,8},
    {0,4,8}, {2,4,6}
};
struct Board {
    char cells[9];
    Board() { for (int i = 0; i < 9; i++) cells[i] = EMPTY; }
    void print() const {
        cout << "\n  Board:\n";
        cout << "     0   1   2\n";
        cout << "   +---+---+---+\n";
        for (int r = 0; r < 3; r++) {
            cout << " " << r << " | ";
            for (int c = 0; c < 3; c++)
                cout << cells[r*3+c] << " | ";
            cout << "\n   +---+---+---+\n";
        }
        cout << "\n";
    }
};
bool constraintCellEmpty(const Board& b, int pos) {
    return b.cells[pos] == EMPTY;
}
char whoseTurn(const Board& b) {
    int x = 0, o = 0;
    for (int i = 0; i < 9; i++) {
        if (b.cells[i] == HUMAN) x++;
        if (b.cells[i] == AI)    o++;
    }
    return (x == o) ? HUMAN : AI;
}
char checkWinner(const Board& b) {
    for (auto& line : WIN_LINES) {
        char a = b.cells[line[0]], bv = b.cells[line[1]], cv = b.cells[line[2]];
        if (a != EMPTY && a == bv && bv == cv) return a;
    }
    return EMPTY;
}
bool isBoardFull(const Board& b) {
    for (int i = 0; i < 9; i++)
        if (b.cells[i] == EMPTY) return false;
    return true;
}
bool isTerminal(const Board& b) {
    return checkWinner(b) != EMPTY || isBoardFull(b);
}
vector<int> getLegalMoves(const Board& b) {
    vector<int> moves;
    for (int i = 0; i < 9; i++)
        if (b.cells[i] == EMPTY) moves.push_back(i);
    return moves;
}
int minimax(Board& b, int depth, int alpha, int beta, bool isMaximizing, int& nodes) {
    nodes++;
    char winner = checkWinner(b);
    if (winner == AI)    return +10 - depth;
    if (winner == HUMAN) return -10 + depth;
    if (isBoardFull(b))  return 0;
    vector<int> moves = getLegalMoves(b);
    if (isMaximizing) {
        int best = INT_MIN;
        for (int m : moves) {
            b.cells[m] = AI;
            best = max(best, minimax(b, depth+1, alpha, beta, false, nodes));
            b.cells[m] = EMPTY;
            alpha = max(alpha, best);
            if (beta <= alpha) break;
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int m : moves) {
            b.cells[m] = HUMAN;
            best = min(best, minimax(b, depth+1, alpha, beta, true, nodes));
            b.cells[m] = EMPTY;
            beta = min(beta, best);
            if (beta <= alpha) break;
        }
        return best;
    }
}
int getBestMove(Board& b) {
    int bestScore = INT_MIN, bestMove = -1, nodes = 0;
    cout << "  [Minimax] Move evaluations:\n";
    cout << "  Cell | Score | Nodes\n";
    cout << "  -----+-------+-------\n";
    for (int m : getLegalMoves(b)) {
        int n = 0;
        b.cells[m] = AI;
        int score = minimax(b, 0, INT_MIN, INT_MAX, false, n);
        b.cells[m] = EMPTY;
        nodes += n;
        cout << "    " << m << "  |  " << setw(3) << score << "  |  " << n << "\n";
        if (score > bestScore) { bestScore = score; bestMove = m; }
    }
    cout << "  => Best: cell " << bestMove << " (score=" << bestScore << ", total nodes=" << nodes << ")\n";
    return bestMove;
}

void printResult(const Board& b) {
    char w = checkWinner(b);
    b.print();
    cout << "  ======= GAME OVER =======\n";
    if      (w == HUMAN) cout << "  YOU WIN! (X)\n";
    else if (w == AI)    cout << "  AI WINS! (O)\n";
    else                 cout << "  DRAW!\n";
    cout << "  =========================\n\n";
}

void playGame() {
    Board b;
    cout << "\n  You = X | AI = O | X goes first\n";
    cout << "  Cells: 0-8  (row*3 + col)\n";

    while (!isTerminal(b)) {
        b.print();
        if (whoseTurn(b) == HUMAN) {
            int pos;
            while (true) {
                cout << "  Your move (0-8): ";
                cin >> pos;
                if (pos < 0 || pos > 8)
                    cout << "  Invalid. Choose 0-8.\n";
                else if (!constraintCellEmpty(b, pos))
                    cout << "  Cell " << pos << " is occupied!\n";
                else break;
            }
            b.cells[pos] = HUMAN;
        } else {
            cout << "\n  AI thinking...\n";
            int m = getBestMove(b);
            b.cells[m] = AI;
            cout << "  AI plays cell " << m << "\n";
        }
    }
    printResult(b);
}

void autoDemo() {
    Board b;
    int move = 1;
    cout << "\n  [AI vs AI — both play optimally]\n";
    while (!isTerminal(b)) {
        char turn = whoseTurn(b);
        cout << "\n--- Move " << move++ << " (" << turn << ") ---\n";
        b.print();

        int bestScore = (turn == AI) ? INT_MIN : INT_MAX;
        int bestMove = -1, nodes = 0;

        for (int m : getLegalMoves(b)) {
            b.cells[m] = turn;
            int s = minimax(b, 0, INT_MIN, INT_MAX, turn == HUMAN, nodes);
            b.cells[m] = EMPTY;
            if ((turn == AI && s > bestScore) || (turn == HUMAN && s < bestScore)) {
                bestScore = s; bestMove = m;
            }
        }

        b.cells[bestMove] = turn;
        cout << "  " << turn << " -> cell " << bestMove
             << "  (score=" << bestScore << ", nodes=" << nodes << ")\n";
    }
    printResult(b);
}

int main() {
    cout << "\n  1. Play against AI\n";
    cout << "  2. Watch AI vs AI\n";
    cout << "  Enter choice: ";
    int c; 
    cin >> c;
    if (c == 1) playGame();
    else autoDemo();

    return 0;
}
