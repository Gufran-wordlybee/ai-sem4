#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
class Graph {
    int v;
    list<pair<int,int>>* l;
public:
    Graph(int V) {
        this->v = V;
        l = new list<pair<int,int>>[V];
    }
    void addedge(char u, char v, int w) {
        l[u-'A'].push_back({v-'A', w});
        l[v-'A'].push_back({u-'A', w});
    }
    void ucs(char src) {
        vector<int> dist(v, INT_MAX);
        dist[src-'A'] = 0;
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;
        pq.push({0, src-'A'});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : l[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        cout << "Vertex Distance from Source " << src << endl;
        for (int i = 0; i < v; i++)
            cout << (char)('A'+i) << " " << dist[i] << endl;
    }
};
int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    Graph g(n);
    g.addedge('A', 'B', 10);
    g.addedge('A', 'C',  5);
    g.addedge('B', 'D',  1);
    g.addedge('C', 'D',  9);
    g.addedge('D', 'E',  4);
    g.addedge('A', 'D',  2);
    char root;
    cout << "Enter the root node: ";
    cin >> root;
    g.ucs(root);
    return 0;
}