#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;
const vector<string> REGIONS = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};
const vector<string> COLORS = {"Red", "Green", "Blue"};
const unordered_map<string, vector<string>> NEIGHBORS = {
    {"WA",  {"NT", "SA"}},
    {"NT",  {"WA", "SA", "Q"}},
    {"SA",  {"WA", "NT", "Q", "NSW", "V"}},
    {"Q",   {"NT", "SA", "NSW"}},
    {"NSW", {"SA", "Q", "V"}},
    {"V",   {"SA", "NSW"}},
    {"T",   {}} 
};
unordered_map<string, string> assignment;
bool isConsistent(const string& region, const string& color) {
    for (const string& neighbor : NEIGHBORS.at(region)) {
        if (assignment.count(neighbor) && assignment.at(neighbor) == color)
            return false;
    }
    return true;
}

int countConstrainedValues(const string& region, const string& color) {
    int count = 0;
    for (const string& neighbor : NEIGHBORS.at(region)) {
        if (assignment.count(neighbor)) continue; // already assigned
        for (const string& c : COLORS) {
            if (c == color) {
                bool alreadyBlocked = false;
                for (const string& nn : NEIGHBORS.at(neighbor)) {
                    if (assignment.count(nn) && assignment.at(nn) == c) {
                        alreadyBlocked = true;
                        break;
                    }
                }
                if (!alreadyBlocked) count++;
            }
        }
    }
    return count;
}
string selectUnassignedVariable() {
    string best = "";
    int minRemainingValues = INT_MAX;
    for (const string& region : REGIONS) {
        if (assignment.count(region)) continue; 
        int count = 0;
        for (const string& color : COLORS) {
            if (isConsistent(region, color))
                count++;
        }
        if (count < minRemainingValues) {
            minRemainingValues = count;
            best = region;
        }
    }
    return best;
}
vector<string> orderDomainValues(const string& region) {
    vector<pair<int, string>> colorConstraints;
    for (const string& color : COLORS) {
        if (isConsistent(region, color)) {
            int constrainedCount = countConstrainedValues(region, color);
            colorConstraints.push_back({constrainedCount, color});
        }
    }
    sort(colorConstraints.begin(), colorConstraints.end());
    vector<string> orderedColors;
    for (auto& [count, color] : colorConstraints)
        orderedColors.push_back(color);
    return orderedColors;
}
bool backtrack() {
    if (assignment.size() == REGIONS.size())
        return true;
    // MRV: pick the most constrained variable
    string region = selectUnassignedVariable();
    cout << "\n[MRV] Selected variable: " << region << endl;
    // LCV: try least constraining values first
    vector<string> orderedColors = orderDomainValues(region);
    cout << "[LCV] Value order for " << region << ": ";
    for (const string& c : orderedColors) cout << c << " ";
    cout << endl;
    for (const string& color : orderedColors) {
        if (isConsistent(region, color)) {
            assignment[region] = color;
            cout << "  Assigning " << region << " = " << color << endl;
            if (backtrack())
                return true;
            cout << "  Backtracking from " << region << " = " << color << endl;
            assignment.erase(region);
        }
    }
    return false; // failure
}

int main() {
    cout << "\nStarting backtracking search..." << endl;
    if (backtrack()) {
        cout << "  SOLUTION FOUND:" << endl;
        for (const string& region : REGIONS) {
            cout << "  " << region << " : " << assignment[region] << endl;
        }
    } else cout << "\nNo solution found." << endl ;
    return 0;
}