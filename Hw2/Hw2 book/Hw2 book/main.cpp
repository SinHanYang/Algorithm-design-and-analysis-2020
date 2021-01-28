//
//  main.cpp
//  Hw2 book
//
//  Created by 楊欣翰 on 2020/11/5.
// consulted with B08902138 潘淙軒

#include <iostream>
#include <vector>
#define ll long long int
using namespace std;
vector<ll> book,book2,cal,cal2;
int n,flag,mini=0,maxi=0;
ll gogo();
ll gogogo();
void printer(int);
int main(int argc, const char * argv[]) {
    int n,flag;
    ll add=0,total=0;
    cin>>n;
    book.resize(n);
    book2.resize(n);
    cal.resize(n);
    cal2.resize(n);
    bool first=true;
    for(int i=0;i<n;i++){
        cin>>book[i];
        book2[i]=book[i];
        if(first==true&&book[i]!=0){
            mini=i;
            first=false;
        }
        if(book[i]!=0){
            maxi=i;
        }
        total+=book[i];
    }
    cin>>flag;
    ll need1,need2;
    need1=gogo();
    book2[mini+1]--;
    need2=gogogo();
    cout<<need1<<" "<<need2<<endl;
    if(need1<=need2){
        add=need1-total;
        cout<<add<<endl;
        if(flag==1){
            printer(0);
        }
    }
    else{
        add=need2-total+1;
        cout<<add<<endl;
        if(flag==1){
            printer(1);
        }
    }
    return 0;
}
ll gogo(){
    ll need=0;
    for(int i=mini;i<=maxi;i++){
        if(i!=maxi){
            if(book[i]==0){
                cal[i]=1;
                need++;
            }
            else{
                cal[i]=book[i];
                if((book[i]-1)<=book[i+1]){
                    book[i+1]-=(book[i]-1);
                }
                else{
                    book[i+1]=0;
                }
                need+=(2*book[i]-1);
            }
        }
        else{
            if(book[i]==0){
                cal[i]=0;
                break;
            }
            else{
                cal[i]=book[i];
                need+=(2*book[i]-1);
            }
        }
    }
    return need;
}
ll gogogo(){
    ll need=0;
    for(int i=mini;i<=maxi;i++){
        if(i!=maxi){
            if(book2[i]==0){
                cal2[i]=1;
                need++;
            }
            else{
                cal2[i]=book2[i];
                if((book2[i]-1)<=book2[i+1]){
                    book2[i+1]-=(book2[i]-1);
                }
                else{
                    book2[i+1]=0;
                }
                need+=(2*book2[i]-1);
            }
        }
        else{
            if(book2[i]==0){
                cal2[i]==0;
                break;
            }
            else{
                cal2[i]=book2[i];
                need+=(2*book2[i]-1);
            }
        }
    }
    return need;
}
void printer(int x){
    if(x==1){
        cout<<mini+2<<" ";
        for(int i=mini;i<maxi;i++){
            for(int j=0;j<cal2[i]-1;j++){
                cout<<i+1<<" "<<i+2<<" ";
            }
            cout<<i+1<<" ";
        }
        if(cal2[maxi]!=0){
            if(maxi==0){
                for(int j=0;j<cal2[maxi]-1;j++){
                    cout<<maxi+1<<" "<<maxi+2<<" ";
                }
                cout<<maxi+1<<" ";
            }
            else{
            for(int j=0;j<cal2[maxi]-1;j++){
                cout<<maxi+1<<" "<<maxi<<" ";
            }
            cout<<maxi+1<<" ";
            }
        }
    }
    else{
        for(int i=mini;i<maxi;i++){
            for(int j=0;j<cal[i]-1;j++){
                cout<<i+1<<" "<<i+2<<" ";
            }
            cout<<i+1<<" ";
        }
        if(cal[maxi]!=0){
            if(maxi==0){
                for(int j=0;j<cal[maxi]-1;j++){
                    cout<<maxi+1<<" "<<maxi+2<<" ";
                }
                cout<<maxi+1<<" ";
            }
            else{
            for(int j=0;j<cal[maxi]-1;j++){
                cout<<maxi+1<<" "<<maxi<<" ";
            }
            cout<<maxi+1<<" ";
            }
        }
    }
}
