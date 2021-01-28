//
//  main.cpp
//  HW1.bomb game
//
//  Created by 楊欣翰 on 2020/10/8.
// cdq idea from B08902138 潘淙軒
//reference:https://robert1003.github.io/2020/01/31/cdq-divide-and-conquer.html

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include "helper.h"
using namespace std;
class event{
public:
    char action;
    int i;
    int c;
    int d;
    int l;
    int r;
    int p;
    long long int k;
};
bool Asorter(event a,event key){
    return a.p < key.p;
}
bool Psorter(event a,event key){
    return a.d < key.d;
}
void cdq(int ,int );
vector<event> totalevent;
vector< long long int> ans;
int main(int argc, const char * argv[]) {
    int N,M;
    cin>>N>>M;
    Memory::reset();
    int anssize=0;
    //讀入
    for(int i=0;i<M;i++){
        event b;
        cin>>b.action;
        if(b.action=='P'){
            cin>>b.c>>b.d;
            anssize++;
            b.i=anssize;
        }
        else{
        cin>>b.l>>b.r>>b.p>>b.k;
        }
        totalevent.push_back(b);
    }
    ans.resize(anssize+1);
    for(int i=1;i<=anssize;i++){
        ans[i]=0;
    }
    Memory::reset();
    cdq(0,totalevent.size()-1);
    for(int i=1;i<=anssize;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}
//T(n)=2*T(n/2)+O(nlogn) --> O(n(logn)^2)
void cdq(int begin,int end){
    //base case T(1)
    if(end-begin==0){
        return;
    }
    else{
        int mid=(begin+end)/2;
        //遞迴
        if((begin+end)%2==0){
            mid=mid-1;
        }
        cdq(begin,mid);
        cdq(mid+1,end);
        //Memory::reset();
        vector<event> P;
        vector<event> A;
        //Merge O(n)+O(nlogn)+O(n)
        //O(n)
        for(int i=begin;i<=mid;i++){
            if(totalevent[i].action=='P'){
                P.push_back(totalevent[i]);
            }
        }
        for(int i=mid+1;i<=end;i++){
            if(totalevent[i].action=='A'){
                Memory::add(totalevent[i].l, totalevent[i].r, totalevent[i].k);
                A.push_back(totalevent[i]);
            }
        }
        //2*O(nlogn)
        if(P.size()>=2){
        sort(P.begin(),P.end(),Psorter);
        }
        if(A.size()>=2){
        sort(A.begin(),A.end(),Asorter);
        }
        int x=0,y=0;
        //理想上下面只要O(n)
        while(x<P.size()&&y<A.size()){
            if(P[x].d>A[y].p){
                Memory::add(A[y].l, A[y].r, -A[y].k);
                y++;
            }
            else{
                ans[P[x].i]+=Memory::get(P[x].c);
                x++;
            }
        }
        while(y<A.size()){
            Memory::add(A[y].l, A[y].r, -A[y].k);
            y++;
        }
        while(x<P.size()){
            ans[P[x].i]+=Memory::get(P[x].c);
            x++;
        }
    }
}
