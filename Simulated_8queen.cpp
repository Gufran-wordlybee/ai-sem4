#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;
int grid[8][8];
void printGrid(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j] == 1) cout << "Q ";
            else                cout << ". ";
        }
        cout << endl;
    }
}
int conflictsAt(int r, int c){
    int count = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(i == r && j == c) continue;
            if(grid[i][j] != 1)  continue;
            if(i == r)                   count++; 
            if(j == c)                   count++; 
            if(abs(i-r) == abs(j-c))     count++;
        }
    }
    return count;
}

// total conflicts on board
int totalConflicts(){
    int count = 0;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if(grid[i][j] == 1)
                count += conflictsAt(i, j);
    return count / 2;
}

int main(){
    srand(time(0));
    cout << "Enter 8x8 grid (0=empty, 1=queen):" << endl;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            cin >> grid[i][j];
    cout << "\nInitial board:" << endl;
    printGrid();
    cout << "Conflicts: " << totalConflicts() << endl;
    double temp    = 100.0;
    double cooling = 0.995;
    int    steps   = 0;
    while(totalConflicts() > 0 && temp > 0.01){
        int qr, qc;
        do {
            qr = rand() % 8;
            qc = rand() % 8;
        } while(grid[qr][qc] != 1);
        int nr, nc;
        do {
            nr = rand() % 8;
            nc = rand() % 8;
        } while(grid[nr][nc] == 1);
        int oldConf = totalConflicts();
        grid[qr][qc] = 0;
        grid[nr][nc] = 1;
        int newConf = totalConflicts();
        int delta   = newConf - oldConf;
        if(delta < 0){
            // better move -> always accept
        } else {
            // worse move -> accept with probability e^(-delta/temp)
            double prob = exp(-delta / temp);
            double r    = (double)rand() / RAND_MAX;
            if(r > prob){
                // reject -> undo move
                grid[nr][nc] = 0;
                grid[qr][qc] = 1;
            }
        }
        temp *= cooling;
        steps++;
    }
    cout << "\nSteps: " << steps << endl;
    cout << "Final board:" << endl;
    printGrid();
    cout << "Conflicts: " << totalConflicts() << endl;
    if(totalConflicts() == 0)
        cout << "Solved!" << endl;
    else
        cout << "Stuck with " << totalConflicts() << " conflicts (try again)" << endl;
    return 0;
}