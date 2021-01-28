//
//  main.cpp
//  HW3 ADA kingdom
//
//  Created by 楊欣翰 on 2020/12/7.
// idea from B08902065洪易
//reference:https://www.geeksforgeeks.org/longest-path-undirected-tree/
#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long int
#define maxN 500005
using namespace std;
class edge{
public:
    int v;
    ll w;
    edge(int,ll);
};
vector<edge> edges[maxN];//紀錄各個路
vector<ll> leaves;//紀錄到每個分支的值
ll weights[maxN]={0};
bool visited[maxN]={false};
int n;
int findroot(int);//找到最遠的點
void dfs_find(int);//用來找root的dfs
ll getleaves(int);//取得各個leaves的值
ll dfs(int,int,ll);//紀錄分支的dfs
bool bigtosmall(ll a,ll b){
    return (a>b);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    cin>>n;
    int u,v;
    ll w;
    for(int i=0;i<n-1;i++){
        cin>>u>>v>>w;
        edge front(v,w),end(u,w);
        edges[u].push_back(front);
        edges[v].push_back(end);
    }
    int root;
    ll twosoldier;
    root=findroot(1);//找到最遠的點，必定為最長路徑上的一點，證明可見reference
    twosoldier=getleaves(root);//找到兩個士兵時的最長路徑
    sort(leaves.begin(),leaves.end(),bigtosmall);
    int nofsold=0;
    //cout.sync_with_stdio(false);
    cout<<0<<" "<<twosoldier<<" ";
    for(int i=2;i<n;i++){
        if(nofsold<leaves.size()){//如果還沒找到所有路徑時
            twosoldier+=leaves[nofsold];//加上最大的分支
            nofsold++;
            cout<<twosoldier<<" ";
        }
        else{
            cout<<twosoldier<<" ";
        }
    }
    return 0;
}
edge::edge(int vx,ll wx){
    v=vx;
    w=wx;
}
int findroot(int u){//找到最遠的點
    dfs_find(u);
    ll max=0;
    int maxid=0;
    for(int i=1;i<=n;i++){
        if(weights[i]>max){
            max=weights[i];
            maxid=i;
        }
    }
    //cout<<"maxid"<<maxid<<endl;
    return maxid;
}
void  dfs_find(int u){
    visited[u]=true;
    for(int i=0;i<edges[u].size();i++){
        if(!visited[edges[u][i].v]){
            weights[edges[u][i].v]=weights[u]+edges[u][i].w;
            if(edges[edges[u][i].v].size()!=1){
                dfs_find(edges[u][i].v);
            }
        }
    }
}
ll getleaves(int u){
    ll max=0,temp=0;
    //cout<<"fall:"<<edges[u][0].w<<endl;
    max=dfs(u, edges[u][0].v,edges[u][0].w);//對於第一條路
    for(int i=1;i<edges[u].size();i++){//分支
        temp=dfs(u, edges[u][i].v,edges[u][i].w);
        if (temp<max){
            leaves.push_back(temp);//其中一個分支
        }
        else{
            leaves.push_back(max);//是主要道路（兩個士兵而言）
            max=temp;
        }
    }
    return max;
}
ll dfs(int u,int v,ll w){//類似於上一個，但不是從root開始的情形
    ll max=0,temp=0;
    if(edges[v].size()==1){
        return w;
    }
    else{
        bool getvalue=false;
        for(int i=0;i<edges[v].size();i++){
            if(edges[v][i].v!=u){
                if(!getvalue){
                    max=dfs(v,edges[v][i].v, edges[v][i].w);
                    getvalue=true;
                }
                else{
                    temp=dfs(v,edges[v][i].v, edges[v][i].w);
                    if (temp<max){
                        leaves.push_back(temp);
                    }
                    else{
                        leaves.push_back(max);
                        max=temp;
                    }
                }
            }
        }
    }
    return (max+w);
}
