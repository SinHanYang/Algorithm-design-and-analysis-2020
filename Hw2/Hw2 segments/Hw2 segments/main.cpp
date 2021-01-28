//
//  main.cpp
//  Hw2 segments
//
//  Created by 楊欣翰 on 2020/11/7.
// consulted with B08902138 潘淙軒

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define ll long long int
using namespace std;
class segment{
public:
    int l,r,i;
    ll w,use;
    friend bool operator < (const segment &a, const segment &b){
        if(a.r!=b.r){
            return a.r<b.r;
        }
        else{
            return a.i>b.i;
        }
    }
};
bool larger(const segment,const segment);
vector<segment> Segment;
vector<ll> pos;
int n,m;
ll k;
bool make;
int solve(ll);
void reset();
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll real=0,expect=0,hope=0;
    cin>>n>>m>>k;
    Segment.resize(n);
    for(int i=0;i<n;i++){
        cin>>Segment[i].l>>Segment[i].r>>Segment[i].w;
        expect+=Segment[i].w;
        Segment[i].i=i;
    }
    //cout<<"hello"<<endl;
    sort(Segment.begin(),Segment.end(),larger);
    while(real<expect){
        //cout<<"inside"<<endl;
        reset();
        hope=(real+expect+1)/2;
        make=true;
        solve(hope);
        if(make==false){
            expect=hope-1;
        }
        else{
            real=hope;
        }
    }
    //make=true;
    reset();
    solve(real);
    if(k!=0){
    cout<<real<<endl;
    for(int i=0;i<n-1;i++){
        cout<<Segment[i].use<<" ";
    }
        cout<<Segment[n-1].use<<endl;
    }
    else{
        cout<<0<<endl;
        for(int i=0;i<n-1;i++){
            cout<<0<<" ";
        }
        cout<<0<<endl;
    }
    return 0;
}
bool larger(const segment a,const segment b){
    if(a.l==b.l){
        return a.r>b.r;
    }
    else{
        return a.l<b.l;
    }
}
void reset(){
    pos.clear();
    pos.resize(m);
    for(int i=0;i<n;i++){
        Segment[i].use=0;
    }
}
int solve(ll hope){
    priority_queue<segment> wider;
    segment seg;
    int posit;
    ll mini,usage;
    posit=mini=usage=0;
    for(int p=0;p<m/*&&make!=false*/;p++){
        while(posit!=n&&Segment[posit].l==p){
            wider.push(Segment[posit]);
            posit++;
        }
        if(p!=0){
            mini+=pos[p-1];
        }
        while(mini<hope/*&&make!=false*/){
            if(wider.empty()==true){
                make=false;
                return 0;
                break;
            }
            else{
                ll gap=hope-mini;
                if(wider.top().r>p){
                    seg=wider.top();
                    ll ww=seg.w;
                    wider.pop();
                    if(seg.w>gap){
                        seg.w-=gap;
                        wider.push(seg);
                        mini=hope;
                        usage+=gap;
                        if(usage>k){
                            make=false;
                            return 0;
                        }
                        pos[seg.r-1]-=gap;
                        /*if(wider.top().i==4){
                            cout<<"before:"<<Segment[wider.top().i].use<<"gap:"<<gap<<endl;
                        }*/
                        Segment[seg.i].use+=gap;
                    }
                    else{
                        pos[seg.r-1]-=ww;
                        mini+=ww;
                        usage+=ww;
                        if(usage>k){
                            make=false;
                            return 0;
                        }
                        /*if(wider.top().i==4){
                            cout<<"before:"<<Segment[wider.top().i].use<<"gap2:"<<wider.top().w<<endl;
                        }*/
                        Segment[seg.i].use+=ww;
                        /*if(wider.top().i==4){
                            cout<<"after:"<<Segment[wider.top().i].use<<endl;
                        }*/
                    }
                }
                else{
                    wider.pop();
                }
            }
        }
    }
    return 1;
}
