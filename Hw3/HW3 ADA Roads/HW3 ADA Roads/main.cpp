//
//  main.cpp
//  HW3 ADA Roads
//
//  Created by 楊欣翰 on 2020/12/9.
//reference1:https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
//reference2:https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
//consulted with B08902138 潘淙軒
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define ll long long 
#define maxN 300005
using namespace std;
typedef  pair<ll,int> Pair;
class edge{
public:
    int u,v;
    ll w;
    edge();
    edge(int,int,ll);
};
edge::edge(){
    
}
edge::edge(int ux,int vx,ll wx){
    u=ux;
    v=vx;
    w=wx;
}
int root[maxN];
ll Rank[maxN];
vector<edge> roads; //紀錄各個路
vector<edge> mst;
vector<Pair> mstroads[maxN];
bool comp(edge a,edge b){
    return a.w<b.w;
}
void mstgraph();
int find(int);
void Union(int,int);
void shortestpath(int,int);
ll weight[maxN+1];
int n,m;
int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll s,t;
    cin>>n>>m>>s>>t;
    roads.resize(m);
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        edge front(u,v,w);
        //cout<<front.u<<front.v<<front.w<<endl;
        roads[i]=front;
    }
    for(int i=0;i<=n;i++){
        weight[i]=__LONG_LONG_MAX__;//找shortest path 的初始設定
        //對於找mst的初始設定
        root[i]=i;
        Rank[i]=0;
    }
    mstgraph();
    weight[s]=0;
    shortestpath(s,t);
    cout<<weight[t]<<endl;
    /*for(int i=1;i<=n;i++){
        cout<<i<<" "<<weight[i]<<endl;
        if(i==t){
            cout<<"fuck ";
        }
    }
    cout<<endl;*/
    return 0;
}
void mstgraph(){
    //Kruskal’s algorithm
    sort(roads.begin(),roads.end(),comp);
    for(int i=0;i<m;i++){
        //cout<<"root:"<<roads[i].u<<" "<<roads[i].v<<endl;
        if(find(roads[i].u)!=find(roads[i].v)){
            //不會存在circle
            mst.push_back(roads[i]);
        }
        if(roads[i].w!=roads[i+1].w||i==m-1){
            //此題特別的地方，等最後一條路判完
            //或者有不同的值的時候，就要把這一階段union，讓後面路段進來時判斷有無構成cycle
            //有相同值時，代表其可以是另一種mst的構成，所以不能先把這些路的parent統一->就是不能先定義root，因為每個都有可能是邊（可以用歸納法去證明從最小值的邊的集合~最大值的邊的集合）
            //ex1:全部都一樣的值時，就只能最後再union
            //ex2:如果中間有不一樣的，那就要找最小可以連接的。
            //如果有多個mst存在，代表其值都一樣。
            for(int i=0;i<mst.size();i++){
                Union(mst[i].u,mst[i].v);//要重新判斷各個節點的root
                mstroads[mst[i].u].push_back(Pair(mst[i].w,mst[i].v));
                mstroads[mst[i].v].push_back(Pair(mst[i].w,mst[i].u));
            }
            mst.clear();
        }
    }
}
int find(int x){
    //找到root
    //cout<<"parent:"<<root[x]<<" "<<x<<endl;
    if(root[x]==x){
        return x;
    }
    else{
        root[x]=find(root[x]);
        return root[x];
    }
}
void Union(int u,int v){
    //refernece1裡的樣版，重新定義root
    int x=find(u),y=find(v);
    if(Rank[x]==Rank[y]){
        root[y]=x;
        Rank[x]++;
    }
    else if(Rank[x]<Rank[y]){
        root[x]=y;
    }
    else{
        root[y]=x;

    }
}
void shortestpath(int s,int t){
    //Dijkstra algorithm
    priority_queue< Pair, vector <Pair> , greater<Pair> > pq;//還沒在explore vetrices裡
    pq.push(Pair(0,s));
    while(pq.size()!=0){
        ll Weight=pq.top().first;
        int u=pq.top().second;
        pq.pop();
        for(int i=0;i<mstroads[u].size();i++){
            if(weight[mstroads[u][i].second]>(Weight +mstroads[u][i].first)){
                /*if(v==6){
                    cout<<weight[v];
                }*/
                //cout<<"inside"<<endl;
                weight[mstroads[u][i].second] = Weight + mstroads[u][i].first;
                pq.push(Pair(weight[mstroads[u][i].second],mstroads[u][i].second));
            }
        }
    }
}
