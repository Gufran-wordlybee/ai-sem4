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
    void dfs_helper(int src, vector<bool>& vis){
        vis[src] = true ;
        cout<<src<<" " ;
        for(auto nbr : l[src]){
            if(!vis[nbr]){
                dfs_helper(nbr,vis);
            }
        }
    }

    void dfs(int src){
        vector<bool>vis(v,false); 
        dfs_helper(src,vis);
        cout<<endl ;
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
    g.addedge(2,4);
    g.addedge(0,4);
    int root ; 
    cout<<"Enter the root node " ;
    cin >> root ;
    g.dfs(root);
    return 0 ;
}
