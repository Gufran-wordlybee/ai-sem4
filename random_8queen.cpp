#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
int grid[8][8];
void printGrid(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j] == 1) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
}
int conflicts(){
    int count = 0;
    for(int r1 = 0; r1 < 8; r1++){
        for(int c1 = 0; c1 < 8; c1++){
            if(grid[r1][c1] != 1) continue;
            for(int r2 = 0; r2 < 8; r2++){
                for(int c2 = 0; c2 < 8; c2++){
                    if(r2 == r1 && c2 == c1) continue;
                    if(grid[r2][c2] != 1)    continue;
                    if(r1 == r2) count++;
                    if(c1 == c2) count++;
                    if(abs(r1-r2) == abs(c1-c2)) count++;
                }
            }
        }
    }
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
    cout << "Conflicts: " << conflicts() << endl;
    int steps = 0;
    while(conflicts() > 0){
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
        grid[qr][qc] = 0;
        grid[nr][nc] = 1;
        steps++;
    }
    cout << "\nSolved in " << steps << " steps" << endl;
    cout << "Final board:" << endl;
    printGrid();
    cout << "Conflicts: " << conflicts() << endl;
    return 0;
}