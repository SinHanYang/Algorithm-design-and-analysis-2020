//
//  main.cpp
//  Hw3 ada treasure
//
//  Created by 楊欣翰 on 2020/11/30.
//reference1:https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/?ref=rp&fbclid=IwAR2yYyGONdUD4BDIZXcDv7pmGJzmjqoOjBhWWuCeCbieKh-NKPXvkTxVjyU
//reference2:https://www.geeksforgeeks.org/strongly-connected-components/
#include <iostream>
#include <climits>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#define ll long long int
using namespace std;
class edges{//線
public:
    int v;
    ll w;
};
class Graph{//整個圖
public:
    int n;
    vector<ll> weights;//各個城市的重量
    vector<vector<edges>> lines;//路的集合
    Graph(int);//constructer
    void addline(int,int,ll);//加路
    Graph scc(map<int,int>&,stack<int> &, bool visited[]);//新的dag by sink scc
    void sccdfs(Graph &,int,int &,bool visited[],map<int,int>&,bool,ll &localweight);//找出scc裡每個點
    void rebulidline(Graph&,map<int,int>&);//對於新的dag鋪上路
    Graph trans();//把整個graph倒置
    void tpsort(stack<int>&,int,bool visited[]);//topoloficalSort
    void dfs(ll maxdp[],int node,bool visited[]);//dp 每個點為起點時能獲得的最大weight
    ll solve();//主要解決函式
};
int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    Graph g(n);
    for(int i=1;i<=n;i++){
        cin>>g.weights[i];
    }
    int u,v,w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        g.addline(u,v,w);
    }
    cout<<g.solve()<<endl;
    return 0;
}
Graph::Graph(int v){
    n=v;
    weights.resize(v+1);
    lines.resize(v+1);
}
void Graph::addline(int u,int v, ll w){
    edges edge;
    edge.v=v;
    edge.w=w;
    //cout<<"u:"<<u<<"v:"<<v<<"w:"<<w<<endl;
    lines[u].push_back(edge);
}
ll Graph::solve(){
    stack<int> order;//dfs後的排序
    bool visited[500000]={false};
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            tpsort(order, i, visited);//dfs後，把順序存在order
        }
    }
    Graph revg=trans();//倒置
    for(int i=1;i<=n;i++){
        visited[i]=false;
    }
    map<int,int> oldtonew;
    Graph dag=revg.scc(oldtonew,order,visited);//能找到scc 並把scc 存成一點
    ll ans=-1;
    if(dag.n==n){//沒有cycle的情況，因為沒有任何點被合併
        ll maxdp[n+1];
        for(int i=1;i<=n;i++){
            maxdp[i]=weights[i];//每個點初始值的weight
        }
        for(int i=1;i<=n;i++){
            visited[i]=false;
        }
        for(int i=1;i<=n;i++){
            if(!visited[i]){
                dfs(maxdp,i,visited);//dp
            }
        }
        for(int i=1;i<=n;i++){
            if(maxdp[i]>ans){
                ans=maxdp[i];//求出最大值
            }
        }
    }
    else{
    revg.rebulidline(dag,oldtonew);//把新的dag鋪路
    ll maxdp[dag.n+1];
    bool visitdag[500000]={false};
    for(int i=1;i<=dag.n;i++){
        maxdp[i]=dag.weights[i];
    }
    for(int i=1;i<=dag.n;i++){
        if(!visitdag[i]){
            dag.dfs(maxdp, i, visitdag);//dp
        }
    }
    for(int i=1;i<=dag.n;i++){
        //cout<<"i:"<<i<<"max:"<<maxdp[i]<<endl;
        if(maxdp[i]>ans){
            ans=maxdp[i];
        }
    }
    }
    return ans;
}
Graph Graph::trans(){
    Graph g(n);
    for(int i=1;i<=n;i++){
        g.weights[i]=weights[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<lines[i].size();j++){
            g.addline(lines[i][j].v,i,lines[i][j].w);//(u,v)->(v,u)
        }
    }
    return g;
}
void Graph::tpsort(stack<int> &order,int i,bool visited[]){
    visited[i]=true;
    for(int j=0;j<lines[i].size();j++){
        if(visited[lines[i][j].v]==false){
            tpsort(order,lines[i][j].v, visited);//dfs
        }
    }
    order.push(i);//finish time最晚的在上面
}
Graph Graph::scc(map<int,int> &oldtonew,stack<int> &order,bool visited[]){
    Graph dag(n);
    int dagn=0;
    bool source=true;
    ll localweight=0;
    while(order.size()!=0){
        int u=order.top();
        order.pop();
        if(!visited[u]){
            sccdfs(dag,u,dagn,visited,oldtonew,source,localweight);//找到scc's components
        }
    }
    dag.n=dagn;
    return dag;
}
void Graph::sccdfs(Graph &dag,int node,int &dagn,bool visited[],map<int,int>&oldtonew,bool source,ll &localweight){
    bool init=false;
    if(source){
        //代表第一次進入這個scc
        init =true;
        dagn++;
        localweight=0;
    }
    localweight+=weights[node];//這個scc的weight =sum of citys' weight
    oldtonew[node]=dagn;// map ,把舊的graph 裡的index 變成dag裡的index
    visited[node]=true;
    for(int i=0;i<lines[node].size();i++){
        if(!visited[lines[node][i].v]){
            localweight+=lines[node][i].w;//the road inside scc
            source=false;//不是第一次進入此scc
            sccdfs(dag,lines[node][i].v,dagn, visited, oldtonew, source, localweight);
        }
        else if(oldtonew[lines[node][i].v]==dagn){
            //是scc裡的路雖然已經拜訪過了
            localweight+=lines[node][i].w;
        }
    }
    if(init){
        dag.weights[dagn]=localweight;
    }
}
void Graph::rebulidline(Graph &dag,map<int,int>&oldtonew){
    for(int i=1;i<=n;i++){
        for(int j=0;j<lines[i].size();j++){
            if(oldtonew[lines[i][j].v]!=oldtonew[i]/*如果不是scc裡面的路*/){
                dag.addline(oldtonew[i],oldtonew[lines[i][j].v], lines[i][j].w);
            }
        }
    }
}
void Graph::dfs(ll maxdp[],int node,bool visited[]){
    visited[node]=true;
    for(int i=0;i<lines[node].size();i++){
        if(!visited[lines[node][i].v]){
            dfs(maxdp,lines[node][i].v,visited);
        }
        maxdp[node]=max(maxdp[node],weights[node]+lines[node][i].w+maxdp[lines[node][i].v]);//relaxiation dp
    }
}
