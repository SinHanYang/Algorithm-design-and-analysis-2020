//
//  main.cpp
//  HW1 ada party
//
//  Created by 楊欣翰 on 2020/10/18.
//  idea from B08902138 潘淙軒

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
typedef long long  ll;
using namespace std;
int n;
int state[500010];
//state 1 minleft, state 2 maxleft
ll a[500010],prefix[500010],mini[500010],maxi[500010];
ll minrmaxr[500010],minrmaxl[500010],minlmaxr[500010],minlmaxl[500010];
ll sum,k;
ll sunmoon(ll);
ll dc(int,int);
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >>n>>k;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    ll pairs=dc(0,n-1);
    cout<<pairs<<endl;
    return 0;
}
ll sunmoon(ll a){
    if(a<0){
        ll x;
        x=k+(a%k);
        if(x==k){
            return 0;
        }
        else{
            return x;
        }
    }
    else{
        return a%k;
    }
}
ll dc(int begin,int end){
    if(end-begin==0){
        return 0;
    }
    else{
        ll small,big;
        ll pairs=0;
        int mid=(begin+end)/2;
        pairs+=dc(begin,mid);
        pairs+=dc(mid+1,end);
        small=big=a[mid+1];
        mini[mid]=maxi[mid]=a[mid+1];
        for(int i=mid+1;i<=end;i++){
            small=min(a[i],mini[i-1]);
            mini[i]=small;
            big=max(a[i],maxi[i-1]);
            maxi[i]=big;
            if(i>=mid+2){
                prefix[i]=prefix[i-1]+a[i];
            }
            else{
                prefix[i]=a[i];
            }
            state[i]=0;
            minrmaxr[sunmoon(prefix[i]-mini[i]-maxi[i])]++;
        }
        ll sum=0;
        int mincell,maxcell;
        small=a[mid];
        big=0;
        mincell=maxcell=mid+1;
        for(int i=mid;i>=begin;i--){
            sum+=a[i];
            small=min(small,a[i]);
            big=max(big,a[i]);
                    while(mincell<=end&&a[i]<mini[mincell]){
                        if(state[mincell]==0){
                            minrmaxr[sunmoon(prefix[mincell]-mini[mincell]-maxi[mincell])]--;
                            minlmaxr[sunmoon(prefix[mincell]-maxi[mincell])]++;
                            state[mincell]=1;
                        }
                        else{
                            minrmaxl[sunmoon(prefix[mincell]-mini[mincell])]--;
                            minlmaxl[sunmoon(prefix[mincell])]++;
                            state[mincell]=3;
                        }
                        mincell++;
                    }
                    while(maxcell<=end&&a[i]>maxi[maxcell]){
                        if(state[maxcell]==0){
                            minrmaxr[sunmoon(prefix[maxcell]-mini[maxcell]-maxi[maxcell])]--;
                            minrmaxl[sunmoon(prefix[maxcell]-mini[maxcell])]++;
                            state[maxcell]=2;
                        }
                        else{
                            minlmaxr[sunmoon(prefix[maxcell]-maxi[maxcell])]--;
                            minlmaxl[sunmoon(prefix[maxcell])]++;
                            state[maxcell]=3;
                        }
                        maxcell++;
                    }
                pairs+=minlmaxr[sunmoon(small-sum)]+minrmaxl[sunmoon(big-sum)]+minlmaxl[sunmoon(small+big-sum)]+minrmaxr[sunmoon(-sum)];
        }
        //maintain
        for(int i=mid+1;i<=end;i++){
            if(state[i]==0){
                minrmaxr[sunmoon(prefix[i]-mini[i]-maxi[i])]--;
            }
            if(state[i]==1){
                minlmaxr[sunmoon(prefix[i]-maxi[i])]--;
            }
            if(state[i]==2){
                minrmaxl[sunmoon(prefix[i]-mini[i])]--;
            }
            if(state[i]==3){
                minlmaxl[sunmoon(prefix[i])]--;
            }
        }
        return pairs;
    }
}
