//
//  main.cpp
//  HW2 ada squence
//
//  Created by 楊欣翰 on 2020/11/2.
//reference1:https://riptutorial.com/dynamic-programming/example/25886/longest-palindromic-subsequence
//reference2:https://medium.com/@hichetanmore/longest-palindromic-sub-sequence-7619c156afee
//reference3:https://stackoverflow.com/questions/12892912/how-to-find-the-longest-palindromic-subsequence-not-its-length
//3 dimensional dp table idea from  B08902138潘淙軒


#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
#define length 210
#define scoremax 610
#define ll long long int
using namespace std;
ll costmax =200000000010;
ll table[length][length][scoremax];//={costmax};//costtable
class Node{
public:
    int pos;
    int val;
};
class way{
public:
    int i,j,k;
};
way Way[length][length][scoremax];//={-1,-1,-1};
vector<Node> scoreope;
vector<int> path;
void makedptable();
void pathtrace(int k);
int N,D;
int s[length],a[length];
ll c[length],K;
int main(int argc, const char * argv[]) {
    cin>>N>>K>>D;
    for(int j=0;j<N;j++){
        cin>>a[j];
    }
    for(int j=0;j<N;j++){
        cin>>c[j];
    }
    for(int j=0;j<N;j++){
        cin>>s[j];
    }
    for(int i=0;i<N;i++){
        for(int j=i;j<N;j++){
            for(int k=0;k<=3*N;k++){
                table[i][j][k]=costmax;
                Way[i][i+1][k].i=-10;
                Way[i][i+1][k].j=-10;
                Way[i][i+1][k].k=-10;
                if(k==0){
                    table[i][j][k]=0;
                }
            }
        }
    }
    makedptable();
    /*for(int k=0;k<=6;k++){
        cout<<"k:"<<k<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
                cout<<table[i][j][k]<<" ";
        }
        cout<<endl;
    }
    }*/
    int S=0;
    for(int k=0;k<=3*N;k++){
        bool valid=false;
        for(int i=0;i<N;i++){
            for(int j=i;j<N;j++){
                if(table[i][j][k]<=K){
                    valid=true;
                }
            }
        }
        if(valid==true){
            S=k;
        }
    }
    cout<<S<<endl;
    pathtrace(S);
    cout<<scoreope.size()<<endl;
    for(int i=0;i<scoreope.size();i++){
        cout<<scoreope[i].pos<<" "<<scoreope[i].val<<endl;
    }
    cout<<path.size()<<endl;
    sort(path.begin(),path.end());
    for(int i=0;i<path.size()-1;i++){
        cout<<path[i]<<" ";
    }
    cout<<path[path.size()-1]<<endl;
    return 0;
}
void makedptable(){
    for(int i=0;i<N;i++){
        for(int k=1;k<=3*N;k++){
            if(k==s[i]){
                table[i][i][k]=0;
            }
        }
    }
    ll lastcost;
    for(int i=0;i<N-1;i++){
        for(int k=1;k<=3*N;k++){
            if(abs(a[i]-a[i+1])<=D){
                if(k==s[i]+s[i+1]||k==s[i]||k==s[i+1]){
                    table[i][i+1][k]=0;
                    if(k==s[i]){
                        Way[i][i+1][k].i=i;
                        Way[i][i+1][k].j=i;
                        Way[i][i+1][k].k=0;
                    }
                    if(k==s[i+1]){
                        Way[i][i+1][k].i=i+1;
                        Way[i][i+1][k].j=i+1;
                        Way[i][i+1][k].k=0;
                    }
                }
                else{
                    table[i][i+1][k]=costmax;
                }
            }
            else{
                if(k!=s[i]+s[i+1]){
                    if(table[i][i][k]<table[i+1][i+1][k]){
                        table[i][i+1][k]=table[i][i][k];
                        Way[i][i+1][k].i=i;
                        Way[i][i+1][k].j=i;
                        Way[i][i+1][k].k=k;
                    }
                    else{
                        table[i][i+1][k]=table[i+1][i+1][k];
                        Way[i][i+1][k].i=i+1;
                        Way[i][i+1][k].j=i+1;
                        Way[i][i+1][k].k=k;
                    }
                }
                else{
                    table[i][i+1][k]=min(c[i],c[i+1]);
                }
            }
        }
    }
    for(int i=3;i<=N;i++){
        for(int j=0;j<=N-i;j++){
            for(int k=1;k<=3*N;k++){
                int l=j+i-1;
                if(table[j][l-1][k]<table[j+1][l][k]){
                    lastcost=table[j][l-1][k];
                    Way[j][l][k].i=j;
                    Way[j][l][k].j=l-1;
                    Way[j][l][k].k=k;
                }
                else{
                    lastcost=table[j+1][l][k];
                    Way[j][l][k].i=j+1;
                    Way[j][l][k].j=l;
                    Way[j][l][k].k=k;
                }
                if(abs(a[j]-a[l])<=D){
                    if(s[j]+s[l]>k){
                        //不可能
                        table[j][l][k]=lastcost;
                    }
                    else{
                        if(table[j+1][l-1][k-s[l]-s[j]]<lastcost){
                            table[j][l][k]=table[j+1][l-1][k-s[l]-s[j]];
                            Way[j][l][k].i=j+1;
                            Way[j][l][k].j=l-1;
                            Way[j][l][k].k=k-s[j]-s[l];
                        }
                        else{
                            table[j][l][k]=lastcost;
                        }
                    }
                }
                else{
                    if(k>=s[j]+s[l]){
                       if(table[j+1][l-1][k-s[l]-s[j]]+min(c[l],c[j])<lastcost){
                        Way[j][l][k].i=j+1;
                        Way[j][l][k].j=l-1;
                        Way[j][l][k].k=k-s[j]-s[l];
                        table[j][l][k]=table[j+1][l-1][k-s[l]-s[j]]+min(c[l],c[j]);
                       }
                       else{
                           table[j][l][k]=lastcost;
                       }
                    }
                    else{
                        table[j][l][k]=lastcost;
                    }
                }
            }
        }
    }
    /*for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<table[i][j][0]<<" ";
        }
        cout<<endl;
    }*/
}
void pathtrace(int t){
    int i=0,j=N-1,k=t;
    while(i>=0&&j>=0&&i<=j&&k>=0){
        //cout<<i<<" "<<j<<endl;
        if(k!=Way[i][j][k].k){
            //have value
            if(i==j){
                path.push_back(i+1);
                break;
            }
            else{
                if(abs(a[i]-a[j])>D){
                    if(c[i]>c[j]){
                        Node node;
                        node.pos=j+1;
                        node.val=a[i];
                        scoreope.push_back(node);
                    }
                    else{
                        Node node;
                        node.pos=i+1;
                        node.val=a[j];
                        scoreope.push_back(node);
                    }
                }
                path.push_back(i+1);path.push_back(j+1);
            }
        }
        int lasti,lastj,lastk;
        lasti=Way[i][j][k].i;
        lastj=Way[i][j][k].j;
        lastk=Way[i][j][k].k;
        i=lasti;j=lastj;k=lastk;
    }
}
