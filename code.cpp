#include <bits/stdc++.h>
#include <chrono>
using namespace std;
pair<int,int> find(pair<int,int> x,vector<vector<pair<int,int>>> &v){
    //union find using path compression
    pair<int,int> p = x;
    while(v[p.first][p.second]!=p){
        p = v[p.first][p.second];
    }
    while(x!=p){
        pair<int,int> parent = v[x.first][x.second];
        v[x.first][x.second] = p;
        x = parent;
    }
    return x;
}
void Union(pair<int,int> a,pair<int,int> b,vector<vector<pair<int,int>>> &v){
    pair<int,int> p = find(a,v);
    v[p.first][p.second]=find(b,v);
}
namespace std {
    template <>
    struct hash<std::pair<std::pair<int, int>, std::pair<int, int>>> {
        size_t operator()(const std::pair<std::pair<int, int>, std::pair<int, int>>& p) const {
            size_t hash1 = std::hash<int>()(p.first.first);
            size_t hash2 = std::hash<int>()(p.first.second);
            size_t hash3 = std::hash<int>()(p.second.first);
            size_t hash4 = std::hash<int>()(p.second.second);
            return hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3);
        }
    };
}
int main(){
    int n;
    cout<<"Enter the dimension of the maze(nxn): ";
    cin>>n;
    vector<vector<int>> v(n,vector<int>(n));
    vector<pair<pair<int,int>,pair<int,int>>> edges;
    set<pair<int,int>> visited;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i<n-1 && visited.find({i,j})==visited.end()){
                edges.push_back({{i,j},{i+1,j}});
            }
            if(j<n-1 && visited.find({i,j})==visited.end()){
                edges.push_back({{i,j},{i,j+1}});
            }
            visited.insert({i,j});
        }
    }
    auto start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 g(rd());
    shuffle(edges.begin(),edges.end(),g);

    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           parent[i][j] = {i,j};
        }
    }
    unordered_set<pair<pair<int,int>,pair<int,int>>> path;
    for(int i=0;i<edges.size();i++){
        pair<int,int> a=edges[i].first,b=edges[i].second;
        if(find(a,parent)!=find(b,parent)){
            Union(a,b,parent);
            path.insert({a,b});
        }
    }
    unordered_set<pair<pair<int,int>,pair<int,int>>> maze;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i<n && (path.find({{i,j-1},{i,j}})==path.end()|| j==0 || j==n)){
                maze.insert({{i,j},{i+1,j}});
            }
            if(j<n && (path.find({{i-1,j},{i,j}})==path.end()|| i==0 || i==n)){
                maze.insert({{i,j},{i,j+1}});
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    maze_creation_duration = duration.count();