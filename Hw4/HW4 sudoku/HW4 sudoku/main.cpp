//
//  main.cpp
//  HW4 sudoku
//
//  Created by 楊欣翰 on 2020/12/22.
// reference1:https://www.ocf.berkeley.edu/%7Ejchu/publicportal/sudoku/sudoku.paper.html
//reference2:https://www.geeksforgeeks.org/perfect-sum-problem-print-subsets-given-sum/

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <cmath>
#include "helper.h"
#define ll long long int
using namespace std;
using namespace DLX;
set<ll> inside;//有沒有在DLX裡
void sunmoon(int,int,int,const int,const int,const int);//找到能不能構成sum
void dpsum(int a[],int,const int,const int,const int,const int,const int);//不是一個二個八個九個的判斷又沒有sum
void tracedp(int a[],int,int,vector<int>&,const int,const int,const int,const int,const int,const int);//trace dp找回所有的sum
void addin(vector<int>&,const int,const int,const int,const int,const int);//把moon加進DLX
bool** dp;
int column,c;
int main(int argc, const char * argv[]){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    set<char> color;
    map<char,int> colortonumber;
    vector<int> sum;
    vector<int> cell;
    char square[10][10]={0};
    for(int i=1;i<=9;++i){
        for(int j=1;j<=9;++j){
            cin>>square[i][j];
            if(color.find(square[i][j])==color.end()){//確認有幾種顏色
                color.insert(square[i][j]);
            }
        }
    }
    char c;
    int s;
    cell.resize(color.size());
    sum.resize(color.size());
    for(int i=0;i<color.size();++i){
        cin>>c>>s;
        colortonumber[c]=i;//顏色編號
        sum[i]=s;//顏色付值
    }
    for(int i=1;i<10;++i){
        for(int j=1;j<10;++j){
            cell[colortonumber[square[i][j]]]++;//確認顏色格數
        }
    }
    column=9*9*4+9*color.size();//X=古典數獨(324)+c*9
    Init(column);
    for(int i=1;i<=9;++i){
        for(int j=1;j<=9;++j){
            for(int k=1;k<=9;++k){
                //i是橫的(row) j是直的(column)
                int g=colortonumber[square[i][j]];
                sunmoon(g,sum[g],cell[g],k,i,j);//找到sum
            }
        }
    }
    int ans[9][9]={0};
    //cout<<"size"<<Solver().size()<<endl;
    //找到hitting set
    for(int i=0;i<Solver().size();i++){
        if(Solver()[i]>0){//不是moon
        int r,w,v;
        r=Solver()[i]/100;
        w=(Solver()[i]-100*r)/10;
        v=(Solver()[i]-100*r-10*w);
        ans[r][w]=v;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<ans[i][j];
        }
        cout<<"\n";
    }
    return 0;
}
void sunmoon(int color,int sum,int cell,const int k,const int r,const int w){
    vector<int> v,v2;
    if(cell==1||cell==2||cell==8||cell==9){
    switch (cell) {
        case 9:
            v2.push_back(9*(r-1)+w);//每一格
            v2.push_back(81+9*(r-1)+k);//每一列
            v2.push_back(162+9*(w-1)+k);//每一欄
            v2.push_back(243+27*((r-1)/3)+9*((w-1)/3)+k);//每一個
            v2.push_back(324+9*color+k);
            AddRow(100*(r-1)+10*(w-1)+k,v2);
            return;
        case 1:
            if(sum==k){//是可行的
                ll code=color;
                for(int i=1;i<=9;++i){
                    if(i!=k){
                        v.push_back(324+9*color+i);
                        code+=i*pow(10,i+1);
                    }
                }
                if(inside.find(code)==inside.end()){
                    //沒有在DLX裡
                    inside.insert(code);
                    AddRow(-1,v);
                }
                v2.push_back(9*(r-1)+w);//每一格
                v2.push_back(81+9*(r-1)+k);//每一列
                v2.push_back(162+9*(w-1)+k);//每一欄
                v2.push_back(243+27*((r-1)/3)+9*((w-1)/3)+k);//每一9*9
                v2.push_back(324+9*color+k);
                AddRow(100*(r-1)+10*(w-1)+k,v2);
            }
            return;
        case 2:
            if(sum-k>0&&sum-k<=9){
                ll code=color;
                for(int i=1;i<=9;++i){
                    if(i!=(sum-k)&&i!=k){
                        v.push_back(324+9*color+i);
                        code+=i*pow(10,i+1);//編碼
                    }
                }
                if(inside.find(code)==inside.end()){
                    inside.insert(code);
                    AddRow(-1,v);
                }
                v2.push_back(9*(r-1)+w);//每一格
                v2.push_back(81+9*(r-1)+k);//每一列
                v2.push_back(162+9*(w-1)+k);//每一欄
                v2.push_back(243+27*((r-1)/3)+9*((w-1)/3)+k);//每一個
                v2.push_back(324+9*color+k);
                AddRow(100*(r-1)+10*(w-1)+k,v2);
            }
            return;
        case 8:
            int pool=45-sum;
            if(pool!=k){
                ll code=color;
                v.push_back(324+9*color+pool);
                code+=(pool*pow(10,pool+1));
                if(inside.find(code)==inside.end()){
                    inside.insert(code);
                    AddRow(-1,v);
                }
                v2.push_back(9*(r-1)+w);//每一格
                v2.push_back(81+9*(r-1)+k);//每一列
                v2.push_back(162+9*(w-1)+k);//每一欄
                v2.push_back(243+27*((r-1)/3)+9*((w-1)/3)+k);//每一個
                v2.push_back(324+9*color+k);
                AddRow(100*(r-1)+10*(w-1)+k,v2);
            }
            return;
    }
        return;
    }
    if(sum>k&&(sum-k)/(cell-1)<=9&&(sum-k)/(cell-1)>=1){//可行的
        int arr[8],x=0;
        for(int i=1;i<10;++i){
            if(i!=k){
                arr[x]=i;
                x++;
            }
        }
        dpsum(arr,sum-k,cell-1,k,color,r,w);
    }
}
void dpsum(int arr[],int sum,const int cell,const int k,const int color,const int r,const int w){
        dp = new bool*[8];
        for (int i=0;i<8;i++){
            dp[i]=new bool[sum + 1];
            dp[i][0]=true;
        }
        if (arr[0]<=sum){
           dp[0][arr[0]]=true;
        }
        for (int i=1;i<8;++i){
            for (int j=0;j<sum+1;++j){
                if(arr[i]>j){
                    dp[i][j]=dp[i-1][j];
                }
                else{
                    dp[i][j]=(dp[i-1][j])||(dp[i-1][j-arr[i]]);
                }
            }
        }
        if (!dp[7][sum]){return;}//沒有解
        vector<int> v2;
        v2.push_back(9*(r-1)+w);//每一格
        v2.push_back(81+9*(r-1)+k);//每一列
        v2.push_back(162+9*(w-1)+k);//每一欄
        v2.push_back(243+27*((r-1)/3)+9*((w-1)/3)+k);//每一個
        v2.push_back(324+9*color+k);
        AddRow(100*(r-1)+10*(w-1)+k,v2);
        vector<int> p;
        tracedp(arr,sum,7,p,cell,k,color,sum,r,w);
}
void tracedp(int a[],int sum,int i,vector<int>& l,const int cell,const int k,const int color,const int tsum,const int r,const int w){
        if (sum!=0&&i==0&&dp[0][sum]){
            l.push_back(a[i]);
            if(l.size()==cell){
                //有解
                addin(l,k,tsum,color,r,w);
            }
            return;
        }
        if (sum == 0 && i == 0){
            if(l.size()==cell){
                //有解
                addin(l, k, tsum,color,r,w);
            }
            return;
        }
        if(dp[i-1][sum]){
            vector<int> x=l;
            tracedp(a,sum,i-1,x,cell,k,color,tsum,r,w);
        }
        if(sum >= a[i]&&dp[i-1][sum-a[i]]){
            l.push_back(a[i]);
            tracedp(a,sum-a[i],i-1,l,cell,k,color,tsum,r,w);
        }
}
void addin(vector<int>&l,const int k,const int tsum,const int color,const int r,const int w){
    bool moon[10]={false};
    moon[k]=true;
    int lsum=0;
    ll code=color;
    for(int j=0;j<l.size();++j){
        if(l[j]==k){
            //一個顏色裡不能重複
            return;
        }
        lsum+=l[j];
        moon[l[j]]=true;
    }
    if(lsum!=tsum){
        return;
    }
    vector<int> add;//不是sum的，所以需要補(moon)
    for(int j=1;j<=9;++j){
        if(!moon[j]){
            add.push_back(324+9*color+j);
            code+=j*pow(10,j+1);
        }
    }
    if(inside.find(code)==inside.end()){
        inside.insert(code);
        AddRow(-1,add);
    }
}
