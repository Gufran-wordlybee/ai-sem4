#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

class Graph {
    int v;
    list<pair<int,int>>* l;   // {neighbor_index, weight}

public:
    Graph(int V) {
        this->v = V;
        l = new list<pair<int,int>>[V];
    }
    void addedge(char u, char v, int w) {
        l[u-'A'].push_back({v-'A', w});
        l[v-'A'].push_back({u-'A', w});
    }
    void bestFirstSearch(char src, char target, vector<int>& h) {
        int s = src - 'A';
        int t = target - 'A';
        vector<bool> visited(v, false);
        vector<int>  parent(v, -1);
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({h[s], s});
        visited[s] = true;
        cout << "Node  h(n)  (order of expansion)\n";
        while (!pq.empty()) {
            auto [hn, u] = pq.top();
            pq.pop();

            cout << (char)('A'+u) << "     " << hn << "\n";

            if (u == t) {
                cout << "\nTarget " << target << " found!\n";
                break;
            }
            for (auto [nbr, w] : l[u]) {
                if (!visited[nbr]) {
                    visited[nbr] = true;
                    parent[nbr]  = u;
                    pq.push({h[nbr], nbr}); 
                }
            }
        }
        vector<char> path;
        for (int cur = t; cur != -1; cur = parent[cur])
            path.push_back('A' + cur);
        reverse(path.begin(), path.end());
        cout << "\nPath: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size()-1) cout << " -> ";
        }
        cout << endl;
    }
};
int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    Graph g(n);
    g.addedge('A', 'B', 10);
    g.addedge('A', 'C',  5);
    g.addedge('B', 'D',  1);
    g.addedge('C', 'D',  9);
    g.addedge('D', 'E',  4);
    g.addedge('A', 'D',  2);
    g.addedge('B', 'E',  7);
    // h(n) = estimated cost from each node to target E
    // A=6, B=5, C=8, D=4, E=0
    vector<int> h = {6, 5, 8, 4, 0};
    char src, target;
    cout << "Enter source: ";  cin >> src;
    cout << "Enter target: ";  cin >> target;
    g.bestFirstSearch(src, target, h);
    return 0;
}