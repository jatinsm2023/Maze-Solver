#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
using state = pair<int,int>;


int n,m;

vector<vector<char>> graph;
vector<vector<int>> vis;
vector<vector<int>> dis;
vector<vector<state>> par;


int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};

bool is_valid(int x, int y){
    if(x>=0 && x<n && y>=0 && y<m && graph[x][y]!='#')return true;
    else return false;
}

vector<state> neighbours(state node){
    vector<state> neighs;
    for( int i=0;i<4; i++)
    {
        if(is_valid(node.F+dx[i],node.S+dy[i])){
            neighs.push_back({node.F+dx[i],node.S+dy[i]});
        }
    }
    return neighs;
}

void bfs( state st_node){
    vis.assign(n,vector<int>(m,0));
    dis.assign(n,vector<int>(m,100));
    par.assign(n,vector<state>(m,make_pair(-1,-1)));
    
    queue<state> q;
    q.push(st_node);
    
    vis[st_node.F][st_node.S] = 1;
    dis[st_node.F][st_node.S] = 0;
    par[st_node.F][st_node.S] = {-1,-1};
    
    while(!q.empty()){
        state node = q.front();
        q.pop();
        
        for( auto v: neighbours(node)){
            if(!vis[v.F][v.S]){
                vis[v.F][v.S] = 1;
                dis[v.F][v.S] = dis[node.F][node.S]+1;
                q.push(v);
                par[v.F][v.S] = node;
            }
        }
    }
    
}

int main()
{
    cout<<"Enter the dimension of Maze (row,column) - ";
    cin>>n>>m;
    graph.resize(n);
    state st,en;
    cout<<"Enter the each vertices of maze ('S' as starting, '.' as path, '#' as wall)  \n";
    for( int i=0; i<n ;i++)
    {
        graph[i].resize(m);
        for( int j=0; j<m ;j++)
        {
            cin>>graph[i][j];
            if(graph[i][j]=='S'){
                st = {i,j};
            }
            else if(graph[i][j]=='F'){
                en = {i,j};
            }
        }
    }
    
    bfs(st);
  
    if(!vis[en.F][en.S]){
        cout<<"Can't Be Reached"<<'\n';
    }
    else {
        cout<<"Total Distance - " << dis[en.F][en.S]<<'\n';
        cout<<"Path (indexwise) - ";
        vector<state> path;
        state cur = {en.F,en.S};
        
        while(cur!=make_pair(-1,-1)){
            path.push_back({cur.F,cur.S});
            cur = par[cur.F][cur.S];
        }
        
        reverse(path.begin(),path.end());
        
        for( auto v : path){
            cout<<'('<< v.F<<","<<v.S<<')'<<"-->";
        }
        cout<<"Reached"<<'\n';
    }
    
}