//
//  main.cpp
//  HW3 another ada party
//
//  Created by 楊欣翰 on 2020/12/6.
//

#include <iostream>
#include <deque>
#include <vector>
#include <string>
#define ll long long int
#define maxN 200005
using namespace std;
class package{//一個group
public:
    int type;
    ll number;
    package(int ,ll);
};
package::package(int t,ll n){
    type=t;
    number=n;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    bool flip[maxN]={false};
    ll total[maxN]={0}/*總共的人數*/,previous[maxN]/*上一輪在隊伍裡的人數*/,current[maxN]={0}/*這一輪減少的人數*/,c,k;
    ll lastchange[maxN]={0};/*上一次改變的時間點*/
    int n,q,t;
    cin>>n>>q;
    deque<package> line;//隊伍
    string action;
    vector<ll> change;//在這一輪改變的組別
    for(int time=0;time<q;time++){
        cin>>action>>c>>t>>k;
        if(line.size()==0){//第一個放入時
            previous[t]+=c;//目前在隊伍裡的人數
            package p(t,c);
            line.push_front(p);
        }
        else{
            if(action=="front"){//插到隊伍前面
                ll pick=0;
                while(pick<k){//把前面裡的前k個挖出來
                    package top=line.front();//前面的這組
                    line.pop_front();
                    pick+=top.number;//已經挖出的人數
                    if(flip[top.type]==false){//將改變在隊伍裡數目的組別叫出來
                        change.push_back(top.type);
                        flip[top.type]=true;
                    }
                    if(pick>k){//挖太多人
                        pick-=top.number;
                        top.number-=(k-pick);//只挖（k-目前挖出的人）
                        current[top.type]+=(k-pick);
                        line.push_front(top);
                        break;
                    }
                    else{
                        current[top.type]+=top.number;
                    }
                }
                package p(t,c+k);//新插入的組別
                line.push_front(p);
            }
            else{//跟前面一樣
                ll pick=0;
                while(pick<k){
                    package top=line.back();
                    line.pop_back();
                    pick+=top.number;
                    if(flip[top.type]==false){
                        change.push_back(top.type);
                        flip[top.type]=true;
                    }
                    if(pick>k){
                        pick-=top.number;
                        top.number-=(k-pick);
                        current[top.type]+=(k-pick);
                        line.push_back(top);
                        break;
                    }
                    else{
                        current[top.type]+=top.number;
                    }
                }
                package p(t,c+k);
                line.push_back(p);
            }
            //這一輪t有改變
            total[t]+=previous[t]*(time-lastchange[t]);//前一次改變到這一次改變所增加的人
            previous[t]+=(c+k);//在隊伍裡t組的人變多
            lastchange[t]=time;//t組改變的時間
            for(int j=0;j<change.size();j++){
                //同樣意思
                total[change[j]]+=previous[change[j]]*(time-lastchange[change[j]]);
                previous[change[j]]-=current[change[j]];
                lastchange[change[j]]=time;
                //maintain current and flip
                flip[change[j]]=false;
                current[change[j]]=0;
            }
            change.clear();//maintain change
            //cout<<t<<endl;
        }
    }
    for(int i=1;i<=n;i++){
        total[i]+=previous[i]*(q-lastchange[i]);//把所有人加上上次改變到最後所增加的人
    }
    for(int i=1;i<=n-1;i++){
        cout<<total[i]<<" ";
    }
    cout<<total[n]<<endl;
    return 0;
}
