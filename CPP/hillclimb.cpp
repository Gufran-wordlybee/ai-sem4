#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int ROWS, COLS;
int gx, gy;

int heuristic(int x, int y){
    return abs(x-gx) + abs(y-gy);
}
void hillClimbing(vector<vector<char>>& grid, int x, int y){
    int currheu = heuristic(x, y);
    while(x != gx || y != gy){
        int bestH = currheu;
        int bx = x, by = y;
        string bestdir = "";
        if(x-1 >= 0 && grid[x-1][y] != '1'){
            int h = heuristic(x-1, y);
            if(h < bestH){ bestH = h; bx = x-1; by = y; bestdir = "UP"; }
        }
        if(x+1 < ROWS && grid[x+1][y] != '1'){
            int h = heuristic(x+1, y);
            if(h < bestH){ bestH = h; bx = x+1; by = y; bestdir = "DOWN"; }
        }
        if(y-1 >= 0 && grid[x][y-1] != '1'){
            int h = heuristic(x, y-1);
            if(h < bestH){ bestH = h; bx = x; by = y-1; bestdir = "LEFT"; }
        }
        if(y+1 < COLS && grid[x][y+1] != '1'){
            int h = heuristic(x, y+1);
            if(h < bestH){ bestH = h; bx = x; by = y+1; bestdir = "RIGHT"; }
        }
        if(bestdir == ""){
            cout << "Stuck at (" << x << "," << y << ") h=" << currheu << endl;
            cout << "FAILED." << endl;
            return;
        }
        if(grid[x][y] != 'S') grid[x][y] = '*';
        x = bx; y = by;
        currheu = bestH;
        cout << bestdir << " -> (" << x << "," << y << ") h=" << currheu << endl;
    }
    cout << "Goal reached!" << endl;
    cout << endl;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}
int main(){
    cout << "Enter rows and cols: ";
    cin >> ROWS >> COLS;
    vector<vector<char>> grid(ROWS, vector<char>(COLS));
    int sx, sy;
    cout << "Enter grid:" << endl;
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cin >> grid[i][j];
            if(grid[i][j] == 'S'){ sx=i; sy=j; }
            if(grid[i][j] == 'G'){ gx=i; gy=j; }
        }
    }
    hillClimbing(grid, sx, sy);
    return 0;
}