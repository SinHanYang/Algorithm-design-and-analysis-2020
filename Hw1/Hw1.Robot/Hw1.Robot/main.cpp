//
//  main.cpp
//  Hw1.Robot
//
//  Created by 楊欣翰 on 2020/10/13.
//k>=1 solution's idea from B08902065 洪易(3 dimensional dp array)
//reference:http://web.ntnu.edu.tw/~algo/DynamicProgramming.html

#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;
class step{
public:
    string way;
    int a,b;
};
bool move(int ,int ,int );
long long int Maxstart(int,int);
int nmax,mmax;
long long int map[500][500];
long long int co[500][500];
void maketable(int);
long long int makefork(long long int ,long long int ,int ,int ,long long int );
void makestep(int,int ,int ,int );
void makestepfork(int ,int ,int );
vector<step> Step;
long long int big[11][3];
long long int cou[11][500][500];
long long int max(long long int,long long int);
int jumpx,jumpy;
int main(int argc, const char * argv[]) {
    long long int k,c;
    cin>>nmax>>mmax>>k>>c;
    for(int i=0;i<nmax;i++){
        for(int j=0;j<mmax;j++){
            cin>>map[i][j];
        }
    }
    long long int sum=LLONG_MIN;
    if(k==0){
        maketable(0);
        sum=Maxstart(nmax-1,mmax-1);
        makestep(0,0, nmax-1, mmax-1);
    }
    else{
        maketable(0);
        for(long long int left=0;left<=k;left++){
            big[left][0]=LLONG_MIN;
            for(int i=0;i<nmax;i++){
                for(int j=0;j<mmax;j++){
                    if(left==0){
                        if(makefork(0, 0,i,j,0)>big[0][0]){
                            big[0][0]=makefork(0, 0, i, j,0);
                            big[0][1]=i;
                            big[0][2]=j;
                        }
                    }
                    else{
                        if(makefork(left,c*left, i, j,big[left-1][0])>big[left][0]){
                            big[left][0]=makefork(left,c*left,i, j,big[left-1][0]);
                            big[left][1]=i;
                            big[left][2]=j;
                        }
                    }
                }
            }
        }
        long long int bestk=0;
        for(long long int left=0;left<=k;left++){
            if(cou[left][nmax-1][mmax-1]>sum){
                sum=cou[left][nmax-1][mmax-1];
                bestk=left;
            }
        }
        /*for(int i=0;i<=bestk;i++){
            cout<<"big"<<big[i][1]<<big[i][2]<<endl;
        }*/
        int locx=nmax-1,locy=mmax-1;
        step step;
        step.way="Jump";
        if(bestk>=1){
            for(long long int i=bestk;i>=1;i--){
                makestepfork(i, locx, locy);
                step.a=jumpx;
                step.b=jumpy;
                Step.push_back(step);
                locx=big[i-1][1];
                locy=big[i-1][2];
            }
        }
        //cout<<"makestep:"<<locx<<" "<<locy<<endl;
        makestep(0, 0, locx, locy);
    }
    cout<<sum<<endl;
    cout<<Step.size()<<endl;
    for(int i=Step.size()-1;i>=0;i--){
        cout<<Step[i].way<<" "<<Step[i].a<<" "<<Step[i].b<<endl;
    }
    return 0;
}
void makestep(int fromx,int fromy,int endx,int endy){
    step step;
    step.way="Move";
    int i=endx,j=endy;
    while(i>fromx||j>fromy){
        step.a=i;
        step.b=j;
        Step.push_back(step);
        if(i>=fromx+1&&j>=fromy+1&&co[i-1][j]>co[i][j-1]){
            i--;
        }
        else if(i>=fromx+1&&j>=fromy+1&&co[i-1][j]>co[i][j-1]){
            j--;
            
        }
        else if(j==fromy){
            i--;
            
        }
        else if(i==fromx){
            j--;
        }
        else{
            j--;
        }
        //cout<<"i,j:"<<i<<j<<endl;
    }
}
bool move(int locx,int locy,int left){
    if(locx==0&&locy==0){
        return false;
    }
    else if(locx==0){
        if(cou[left][0][locy-1]<big[left-1][0]){
            return false;
        }
    }
    else if(locy==0){
        if(cou[left][locx-1][0]<big[left-1][0]){
            return false;
        }
    }
    else{
        if(cou[left][locx-1][locy]<big[left-1][0]&&cou[left][locx][locy-1]<big[left-1][0]){
            return false;
        }
    }
    return true;
}
void makestepfork(int left,int fromx,int fromy){
    step step;
    step.way="Move";
    int locx,locy;
    locx=fromx;
    locy=fromy;
    while(move(locx,locy,left)==true){
        if(locx==0){
            step.a=locx;
            step.b=locy;
            locy--;
        }
        else if(locy==0){
            step.a=locx;
            step.b=locy;
            locx--;
        }
        else if(locx>=1&&locy>=1&&cou[left][locx-1][locy]>cou[left][locx][locy-1]){
            step.a=locx;
            step.b=locy;
            locx--;
        }
        else if(locx>=1&&locy>=1&&cou[left][locx-1][locy]<cou[left][locx][locy-1]){
            step.a=locx;
            step.b=locy;
            locy--;
        }
        else{
            step.a=locx;
            step.b=locy;
            locy--;
        }
        Step.push_back(step);
    }
    jumpx=locx;
    jumpy=locy;
}
void maketable(int c){
    for(int i=0;i<nmax;i++){
        for(int j=0;j<mmax;j++){
            map[i][j]=map[i][j]-c;
        }
    }
    co[0][0]=map[0][0];
    for(int i=1;i<nmax;i++){
        co[i][0]=co[i-1][0]+map[i][0];
    }
    for(int i=1;i<mmax;i++){
        co[0][i]=co[0][i-1]+map[0][i];
    }
    for (int i=1; i<nmax;i++){
        for(int j=1;j<mmax;j++){
            co[i][j]=max(co[i-1][j],co[i][j-1])+map[i][j];
        }
    }
}
long long int makefork(long long int left,long long int c,int i,int j,long long int big){
    if(left==0){
        if(i==0&&j==0){
            cou[0][0][0]=map[0][0];
            return cou[0][0][0];
        }
        else if(i!=0&&j==0){
            cou[left][i][0]=map[i][0]+cou[left][i-1][0];
            return cou[left][i][0];
        }
        else if(i==0&&j!=0){
            cou[left][0][j]=map[0][j]+cou[left][0][j-1];
            return cou[left][0][j];
        }
        else{
            long long int twomax;
            twomax=max(cou[left][i][j-1],cou[left][i-1][j]);
            cou[left][i][j]=map[i][j]+twomax;
            return cou[left][i][j];
        }
    }
    else{
        if(i==0&&j==0){
            cou[left][0][0]=map[0][0]-c+big;
            return cou[left][0][0];
        }
        else if(j==0){
            cou[left][i][0]=map[i][0]-c+max(big,cou[left][i-1][0]);
            return cou[left][i][0];
        }
        else if(i==0){
            cou[left][0][j]=map[0][j]-c+max(big,cou[left][0][j-1]);
            return cou[left][0][j];
        }
        else{
            long long int twomax;
            twomax=max(cou[left][i][j-1],cou[left][i-1][j]);
            cou[left][i][j]=map[i][j]-c+max(big,twomax);
            return cou[left][i][j];
        }
    }
}
long long int max(long long int a,long long int b){
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}
long long int Maxstart(int endx,int endy){
        return co[endx][endy];
}
