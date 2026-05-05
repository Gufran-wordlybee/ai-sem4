// implement Uniform cost search return path and cost
#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std ;
class Graph{
    int v ;
    list<pair<int,int>>*l ;
public:
    Graph(int V){
        this -> v = V ;
        l = new list<pair<int,int>>[V];
    }
    void addedge(int u , int v , int w){
        l[u].push_back({v,w});
        l[v].push_back({u,w});
    }
    void ucs(int src){
        vector<int>dist(v,INT_MAX); // + infinity
        dist[src] = 0 ;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        // {distance,vertex} // min heap can i do {vertex,distance} ? yes but then i have to change the way i access the elements in the pq 
        pq.push({0,src});
        while(!pq.empty()){
            auto node = pq.top();

            pq.pop();
            int u = node.second ; // vertex
            int d = node.first ; // distance from source to u
            if(d > dist[u]) continue ;
            for(auto nbr : l[u]){
                int v = nbr.first ; // neighbor vertex
                int w = nbr.second ; // weight of edge u-v
                if(dist[u] + w < dist[v]){ // dist[0]+10 < infinity pq.push({10,1})
                    // second neighbor 2 with weight 5 dist[0]+5 < infinity pq.push({5,2})
                    dist[v] = dist[u] + w ;
                    pq.push({dist[v],v});
                }
            }
        }
        cout<<"Vertex Distance from Source "<<src<<endl;
        for(int i=0;i<v;i++){
            cout<<i<<" "<<dist[i]<<endl;
        }
    }
}; 
int main(){
    int n ;
    cout<<"Enter the number of vertices " ;
    cin >> n ;
    Graph g(n);
    g.addedge(0,1,10);
    g.addedge(0,2,5);
    g.addedge(1,3,1);
    g.addedge(2,3,9);
    g.addedge(3,4,4);
    g.addedge(0,3,2);
    int root ;
    cout<<"Enter the root node " ;
    cin >> root ;
    g.ucs(root);
    return 0 ;
}