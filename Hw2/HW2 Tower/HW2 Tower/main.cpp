//
//  main.cpp
//  HW2 Tower
//
//  Created by 楊欣翰 on 2020/10/23.
// idea from B08902065 洪易

#include <iostream>
#include <climits>
#include <deque>
#define max 100005
#define ll long long int
using namespace std;
ll s[max];//各地的防禦值
deque<int> bonus;//由大到小排列
void makedptable();//建表
ll n,k,a,b;
ll table[2][max];//dp table for not counting bonus
ll powerful[401]={0};
int main(int argc, const char * argv[]) {
    cin>>n>>k>>a>>b;
    for(int i=0;i<n;i++){
        cin>>s[i];
        table[0][i]=s[i];
        if(i==0){
            powerful[0]=table[0][0];
        }
        else{
            if(table[0][i]>powerful[0]){
                powerful[0]=table[0][i];
            }
        }
    }
    if(k>n){
        k=n;
    }
    makedptable();
    ll answer=0;
    if(powerful[k-1]>0){
        answer=powerful[k-1];
    }
    for(ll j=k-2;j>=0;j--){
        if((powerful[j]>answer)){
            answer=powerful[j];
        }
    }
    cout<<answer<<endl;
    return 0;
}
void makedptable(){
    int cur,pre,realmaxid;
    for(int i=1;i<k;i++){
        bonus.clear();
        realmaxid=-10;
        cur=i%2;
        pre=(i-1)%2;
        table[cur][i]=s[i]+table[pre][i-1]+a*(b-1);
        if(table[pre][i-1]<table[cur][i-1]+a){
            realmaxid=i-1;
        }
        else{
            bonus.push_back(i-1);
        }
        bonus.push_back(i);
        powerful[i]=table[cur][i];
        for(int j=i+1;j<n;j++){
            if(bonus.size()!=0){
                while((j-bonus.front()>=b)){
                    if(realmaxid==-10){
                        realmaxid=bonus.front();
                    }
                    if(realmaxid==-10||table[pre][bonus.front()]>table[pre][realmaxid]){
                        realmaxid=bonus.front();
                    }
                    bonus.pop_front();
                    if(bonus.size()==0){
                        break;
                    }
                }
            }
            if(bonus.size()==0){
                    table[cur][j]=table[pre][realmaxid]+s[j];
            }
            else{
                if(realmaxid==-10){
                    table[cur][j]=s[j]+table[pre][bonus.front()]+a*(b-j+bonus.front());
                }
                else{
                    if(table[pre][realmaxid]>table[pre][bonus.front()]+a*(b-j+bonus.front())){
                        table[cur][j]=table[pre][realmaxid]+s[j];
                    }
                    else{
                        table[cur][j]=s[j]+table[pre][bonus.front()]+a*(b-j+bonus.front());
                    }
                }
            }
            if(bonus.size()!=0){
                while((table[pre][j]+a*j)>(table[pre][bonus.back()]+a*bonus.back())){
                    if(table[pre][bonus.back()]>table[pre][realmaxid]){
                        realmaxid=bonus.back();
                    }
                    bonus.pop_back();
                    if(bonus.size()==0){
                        break;
                    }
                }
            }
            bonus.push_back(j);
            if(powerful[i]<table[cur][j]){
                powerful[i]=table[cur][j];
            }
        }
    }
}
