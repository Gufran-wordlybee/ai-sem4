#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;
int board[9][9] = {
    {0, 0, 3, 0, 2, 0, 6, 0, 0},
    {9, 0, 0, 3, 0, 5, 0, 0, 1},
    {0, 0, 1, 8, 0, 6, 4, 0, 0},
    {0, 0, 8, 1, 0, 2, 9, 0, 0},
    {7, 0, 0, 0, 0, 0, 0, 0, 8},
    {0, 0, 6, 7, 0, 8, 2, 0, 0},
    {0, 0, 2, 6, 0, 9, 5, 0, 0},
    {8, 0, 0, 2, 0, 3, 0, 0, 9},
    {0, 0, 5, 0, 1, 0, 3, 0, 0}
};
set<int> domain[9][9];
void printBoard(const string& label) {
    cout << "\n" << label << "\n";
    cout << "    1 2 3   4 5 6   7 8 9\n";
    cout << "  +-------+-------+-------+\n";
    for (int r = 0; r < 9; r++) {
        cout << (char)('A'+r) << " |";
        for (int c = 0; c < 9; c++) {
            if (board[r][c] == 0) cout << " .";
            else                  cout << " " << board[r][c];
            if (c==2||c==5) cout << " |";
        }
        cout << " |\n";
        if (r==2||r==5||r==8)
            cout << "  +-------+-------+-------+\n";
    }
}
vector<pair<int,int>> getPeers(int r, int c) {
    set<pair<int,int>> peers;
    for (int col=0; col<9; col++) if (col!=c) peers.insert({r,col});
    for (int row=0; row<9; row++) if (row!=r) peers.insert({row,c});
    int br=(r/3)*3, bc=(c/3)*3;
    for (int row=br; row<br+3; row++)
        for (int col=bc; col<bc+3; col++)
            if (row!=r||col!=c) peers.insert({row,col});
    return vector<pair<int,int>>(peers.begin(), peers.end());
}

void initDomains() {
    for (int r=0; r<9; r++)
        for (int c=0; c<9; c++) {
            if (board[r][c] != 0)
                domain[r][c] = {board[r][c]}; // fixed clue
            else
                domain[r][c] = {1,2,3,4,5,6,7,8,9};
        }
    for (int r=0; r<9; r++)
        for (int c=0; c<9; c++)
            if (board[r][c] != 0)
                for (auto [pr,pc] : getPeers(r,c))
                    domain[pr][pc].erase(board[r][c]);
}
bool forwardCheck(int r, int c, int val,
                  vector<pair<pair<int,int>,int>>& pruned) {
    for (auto [pr,pc] : getPeers(r,c)) {
        if (board[pr][pc] != 0) continue; // already assigned
        if (domain[pr][pc].count(val)) {
            domain[pr][pc].erase(val);
            pruned.push_back({{pr,pc}, val});
            if (domain[pr][pc].empty()) return false; // wipe-out!
        }
    }
    return true;
}
void undoPruning(const vector<pair<pair<int,int>,int>>& pruned) {
    for (auto [cell, val] : pruned)
        domain[cell.first][cell.second].insert(val);
}
pair<int,int> selectMRV() {
    int minSize = INT_MAX;
    pair<int,int> best = {-1,-1};
    for (int r=0; r<9; r++)
        for (int c=0; c<9; c++) {
            if (board[r][c] != 0) continue;
            int sz = (int)domain[r][c].size();
            if (sz < minSize) { minSize=sz; best={r,c}; }
        }
    return best;
}

vector<int> orderLCV(int r, int c) {
    vector<pair<int,int>> scored; 
    for (int val : domain[r][c]) {
        int elim = 0;
        for (auto [pr,pc] : getPeers(r,c))
            if (board[pr][pc]==0 && domain[pr][pc].count(val))
                elim++;
        scored.push_back({elim, val});
    }
    sort(scored.begin(), scored.end()); // ascending: fewest eliminations first
    vector<int> result;
    for (auto [e,v] : scored) result.push_back(v);
    return result;
}

int assignments = 0;
int backtracks  = 0;

bool solve() {
    auto [r,c] = selectMRV();
    if (r == -1) return true; 
    vector<int> values = orderLCV(r, c);
    for (int val : values) {
        assignments++;
        board[r][c] = val;
        set<int> savedDomain = domain[r][c];
        domain[r][c] = {val};
        vector<pair<pair<int,int>,int>> pruned;
        if (forwardCheck(r, c, val, pruned)) {
            if (solve()) return true;
        }
        backtracks++;
        board[r][c] = 0;
        domain[r][c] = savedDomain;
        undoPruning(pruned);
    }
    return false; 
}
int main() {
    printBoard("Puzzle (unsolved):");
    initDomains();
    if (solve()) {
        printBoard("Solution:");
        cout << "\n--- Stats ---\n";
        cout << "Assignments made : " << assignments << "\n";
        cout << "Backtracks needed: " << backtracks  << "\n";
    } else {
        cout << "\nNo solution exists for this puzzle.\n";
    }
    return 0;
}