#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std ;
class Graph{
    int v ; 
    list<char>*l ; 
public:
    Graph(int V){
        this -> v = V ; 
        l = new list<char>[V];
    }
    void addedge(char u , char v ){

        l[u-'A'].push_back(v); 
        l[v-'A'].push_back(u); 
    }
    void dfs_helper(char src, vector<bool>& vis){
        vis[src-'A'] = true ;
        cout<<src<<" " ;
        for(auto nbr : l[src-'A']){
            if(!vis[nbr-'A']){
                dfs_helper(nbr,vis);
            }
        }
    }
    void dfs(char src){
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
    g.addedge('A','B');
    g.addedge('A','C');
    g.addedge('B','D');
    g.addedge('C','D');
    g.addedge('D','E');
    g.addedge('A','D');
    g.addedge('C','E');
    g.addedge('A','E');
    char root ; 
    cout<<"Enter the root node " ;
    cin >> root ;
    cout<<"DFS is " ;
    g.dfs(root);
    return 0 ;
}