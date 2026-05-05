#include <iostream>
#include<vector>
using namespace std;

vector<string> vars = {"WA","NT","SA","Q","NSW","V","T"};
vector<string> colors = {"R","G","B"};

vector<vector<int>> neighbors = {
    {1,2},        // WA
    {0,2,3},      // NT
    {0,1,3,4,5},  // SA
    {1,2,4},      // Q
    {2,3,5},      // NSW
    {2,4},        // V
    {}            // T
};

vector<string> assignment(7, "");

bool isValid(int var, string color) {
    for (int n : neighbors[var]) {
        if (assignment[n] != "" && assignment[n] == color)
            return false;
    }
    return true;
}

// MRV + Degree
int selectVariable() {
    int bestVar = -1;
    int minDomain = INT_MAX;
    int maxDegree = -1;

    for (int i = 0; i < 7; i++) {
        if (assignment[i] != "") continue;

        int count = 0;
        for (auto c : colors)
            if (isValid(i, c)) count++;

        if (count < minDomain) {
            minDomain = count;
            bestVar = i;
            maxDegree = neighbors[i].size();
        }
        else if (count == minDomain) {
            if (neighbors[i].size() > maxDegree) {
                bestVar = i;
                maxDegree = neighbors[i].size();
            }
        }
    }
    return bestVar;
}

vector<string> LCV(int var) {
    vector<pair<int,string>> temp;

    for (auto c : colors) {
        int conflicts = 0;

        for (int n : neighbors[var]) {
            if (assignment[n] == "") {
                for (auto nc : colors) {
                    if (nc == c) conflicts++;
                }
            }
        }

        temp.push_back({conflicts, c});
    }

    sort(temp.begin(), temp.end());

    vector<string> ordered;
    for (auto &p : temp)
        ordered.push_back(p.second);

    return ordered;
}


bool backtrack() {
    bool done = true;
    for (auto &v : assignment)
        if (v == "") done = false;

    if (done) return true;

    int var = selectVariable();

    for (auto val : LCV(var)) {
        if (isValid(var, val)) {
            assignment[var] = val;

            if (backtrack()) return true;

            assignment[var] = "";
        }
    }
    return false;
}


int main() {
    if (backtrack()) {
        cout << "Solution:\n";
        for (int i = 0; i < 7; i++) {
            cout << vars[i] << " -> " << assignment[i] << endl;
        }
    } else {
        cout << "No solution\n";
    }
    return 0;
}