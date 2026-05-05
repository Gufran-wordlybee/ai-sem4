#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std ;
class Graph{
    int v ; 
    list<int>*l ; 
public:
    Graph(int V){
        this -> v = V ; 
        l = new list<int>[V];
    }
    void addedge(int u , int v ){
        l[u].push_back(v); 
        l[v].push_back(u); 
    }
    void bfs(int src){
        vector<bool>vis(v,false); 
        queue<int>q ; 
        q.push(src); 
        vis[src] = true ;
        while (!q.empty()){
            int node = q.front() ; 
            q.pop() ; 
            cout<<node<<" " ;
            for(auto nbr : l[node]){
                if(!vis[nbr]){
                    q.push(nbr); 
                    vis[nbr] = true ;
                }
            }
        }
    }
};
int main(){
    int n ; 
    cout<<"Enter the number of vertices " ; 
    cin >> n ; 
    Graph g(n);
    g.addedge(0,1);
    g.addedge(0,2);
    g.addedge(1,3);
    g.addedge(2,3);
    g.addedge(3,4);
    g.addedge(0,3);
    int root ; 
    cout<<"Enter the root node " ;
    cin >> root ;
    cout<<"BFS is " ;
    g.bfs(root);
    cout << endl ;
    return 0 ;
}
