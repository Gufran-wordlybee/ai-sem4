#include<iostream>
#include<list>
#include<vector>
using namespace std;
class Graph {
    int v;
    list<int>* l;
public:
    Graph(int V) {
        this->v = V;
        l = new list<int>[V];
    }
    void addedge(char u, char v) {
        l[u-'A'].push_back(v-'A');
        l[v-'A'].push_back(u-'A');
    }
    bool dls(int src, int target, int limit, vector<int>& path) {
        path.push_back(src);
        if (src == target) return true; 
        if (limit == 0) {                 
            path.pop_back();
            return false;
        }
        for (auto nbr : l[src]) {
            if (dls(nbr, target, limit-1, path))  
                return true;
        }
        path.pop_back();               
        return false;
    }
    void ids(char src, char target) {
        int s = src - 'A';
        int t = target - 'A';
        for (int limit = 0; limit <= v; limit++) {
            vector<int> path;
            cout << "Trying depth limit " << limit << "...";
            if (dls(s, t, limit, path)) {
                cout << "FOUND!\n";
                cout << "\nPath: ";
                for (int i = 0; i < path.size(); i++) {
                    cout << (char)('A' + path[i]);
                    if (i != path.size()-1) cout << " -> ";
                }
                cout << "\nDepth: " << path.size()-1 << endl;
                return;
            }
            cout << "not found\n";
        }
        cout << "Target not reachable from " << src << endl;
    }
};
int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    Graph g(n);
    g.addedge('A', 'B');
    g.addedge('A', 'C');
    g.addedge('B', 'D');
    g.addedge('C', 'D');
    g.addedge('D', 'E');
    g.addedge('B', 'E');
    char src, target;
    cout << "Enter source: ";    
    cin >> src;
    cout << "Enter target: ";      
    cin >> target;
    g.ids(src, target);
    return 0;
}
