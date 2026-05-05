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
    void bfs(char src){
        vector<bool>vis(v,false); 
        queue<char>q ; 
        q.push(src); 
        vis[src-'A'] = true ;
        while (!q.empty()){
            char node = q.front() ; 
            q.pop() ; 
            cout<<node<<" " ;
            for(auto nbr : l[node-'A']){
                if(!vis[nbr-'A']){
                    q.push(nbr); 
                    vis[nbr-'A'] = true ;
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
    cout<<"BFS is " ;
    g.bfs(root);
    cout << endl ;
    return 0 ;
}