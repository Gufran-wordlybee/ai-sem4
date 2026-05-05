#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
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

    void astar(char src, char target, vector<int>& h) {
        int s = src    - 'A';
        int t = target - 'A';

        vector<int>  g(v, INT_MAX);    // g(n) = actual cost from src
        vector<int>  parent(v, -1);
        vector<bool> closed(v, false); // closed list

        // min-heap on f(n) = g(n) + h(n)
        // {f(n), node}
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> open;

        g[s] = 0;
        open.push({g[s] + h[s], s});

        cout << "Node  g(n)  h(n)  f(n)\n";
        cout << "-------------------------\n";

        while (!open.empty()) {
            auto [f, u] = open.top();
            open.pop();

            if (closed[u]) continue;   // already finalized
            closed[u] = true;

            cout << (char)('A'+u) << "     "
                 << g[u] << "     "
                 << h[u] << "     "
                 << g[u] + h[u] << "\n";

            if (u == t) {
                cout << "\nTarget " << target << " found!\n";
                break;
            }

            for (auto [nbr, w] : l[u]) {
                if (!closed[nbr]) {
                    int new_g = g[u] + w;
                    if (new_g < g[nbr]) {          // better path found
                        g[nbr]      = new_g;
                        parent[nbr] = u;
                        open.push({new_g + h[nbr], nbr}); // f = g + h
                    }
                }
            }
        }

        // Reconstruct path
        vector<char> path;
        for (int cur = t; cur != -1; cur = parent[cur])
            path.push_back('A' + cur);
        reverse(path.begin(), path.end());

        cout << "\nPath: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size()-1) cout << " -> ";
        }
        cout << "\nTotal cost g(target): " << g[t] << endl;
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
    g.astar(src, target, h);
    return 0;
}
