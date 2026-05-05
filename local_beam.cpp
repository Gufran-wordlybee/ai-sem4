#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;
// nodes: S=0,A=1,B=2,E=3,H=4,I=5,C=6,N=7,J=8,K=9,D=10,F=11,G=12,L=13,M=14
#define S  0
#define A  1
#define B  2
#define E  3
#define H  4
#define I  5
#define C  6
#define N  7
#define J  8
#define K  9
#define D  10
#define F  11
#define G  12
#define L  13
#define M  14
string name[] = {"S","A","B","E","H","I","C","N","J","K","D","F","G","L","M"};
int V = 15;
list<pair<int,int>> adj[15];
void addedge(int u, int v, int w){
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}
// heuristic h(n) = straight line / estimated cost to G
// using edge weights as proxy — lower neighbor index closer to G
int h[] = {
    // S   A   B   E   H   I   C   N   J   K   D   F   G   L   M
      50, 40, 45, 60, 20, 30, 40, 45, 70, 15,  9, 22,  0, 35, 16
};

void buildGraph(){
    addedge(S, A, 26);
    addedge(S, I,  6);
    addedge(S, N,  7);
    addedge(S, J, 19);
    addedge(A, B,  2);
    addedge(B, E, 12);
    addedge(E, H, 28);
    addedge(I, H,  8);
    addedge(I, C, 20);
    addedge(H, F,  5);
    addedge(H, K, 33);
    addedge(K, G, 14);
    addedge(K, D,  3);
    addedge(D, G,  9);
    addedge(F, G, 22);
    addedge(F, M, 11);
    addedge(M, G, 16);
    addedge(N, L, 18);
    addedge(L, C,  9);
    addedge(L, F, 35);
    addedge(J, N, 30);
    addedge(C, L,  9);
}

struct State {
    int node;
    int cost;           // g(n) actual cost from S
    vector<int> path;
};

void localBeamSearch(int src, int goal, int beamSize){
    cout << "\n=== Beam Size = " << beamSize << " ===" << endl;
    // initial beam — start with src
    vector<State> beam;
    beam.push_back({src, 0, {src}});

    int step = 0;
    bool found = false;

    while(!beam.empty()){
        cout << "Step " << step << " beam: ";
        for(auto& s : beam) cout << name[s.node] << "(f=" << s.cost + h[s.node] << ") ";
        cout << endl;
        for(auto& s : beam){
            if(s.node == goal){
                cout << "Goal found!" << endl;
                cout << "Path: ";
                for(int i = 0; i < s.path.size(); i++){
                    cout << name[s.path[i]];
                    if(i != s.path.size()-1) cout << " -> ";
                }
                cout << "\nCost: " << s.cost << endl;
                found = true;
                return;
            }
        }
        vector<State> candidates;
        for(auto& s : beam){
            for(auto [nbr, w] : adj[s.node]){
                bool visited = false;
                for(int p : s.path)
                    if(p == nbr) { visited = true; break; }
                if(visited) continue;
                State next;
                next.node = nbr;
                next.cost = s.cost + w;
                next.path = s.path;
                next.path.push_back(nbr);
                candidates.push_back(next);
            }
        }
        if(candidates.empty()){
            cout << "No candidates. Search failed." << endl;
            return;
        }
        sort(candidates.begin(), candidates.end(), [](State& a, State& b){
            return (a.cost + h[a.node]) < (b.cost + h[b.node]);
        });
        beam.clear();
        for(int i = 0; i < min(beamSize, (int)candidates.size()); i++)
            beam.push_back(candidates[i]);
        step++;
        if(step > 20) break; 
    }
    if(!found)
        cout << "Goal not found with beam size " << beamSize << endl;
}
int main(){
    buildGraph();
    localBeamSearch(S, G, 2);
    localBeamSearch(S, G, 3);
    localBeamSearch(S, G, 4);
    return 0;
}