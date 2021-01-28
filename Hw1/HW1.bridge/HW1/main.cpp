
//  HW1
//
//  Created by 楊欣翰 on 2020/10/5.
//
//reference: GeeksforGeeks"Closest Pair of Points using Divide and Conquer algorithm"
//website:https://www.geeksforgeeks.org/closest-pair-of-points-using-divide-and-conquer-algorithm/
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class Node{
public:
    long long int x;
    long long int y;
    int id;
};
long long int  Compare(vector<Node>,vector<Node>);
long long int compareall(vector<Node>);
bool comparex(Node,Node);
bool comparey(Node,Node);
int main(int argc, const char * argv[]) {
    long long int smallest;
    Node node;
    vector<Node> data,datay;
    int N;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>node.x>>node.y;
        node.id=i;
        data.push_back(node);
        datay.push_back(node);
    }
    sort(data.begin(), data.end(), comparex);
    sort(datay.begin(),datay.end(),comparey);
    smallest=Compare(data,datay);
    cout<<-smallest<<endl;
    return 0;
}
bool comparex(Node a,Node b){
    return a.x<b.x;
}
bool comparey(Node a,Node b){
    return a.y<b.y;
}
long long int compareall(vector<Node> data){
    int size=data.size();
    long long int com,smallest;
    if(size==1){
        smallest=data[0].x*data[0].x+data[0].y*data[0].y;
    }
    else{
    for(int i=0;i<size-1;i++){
            for(int j=i+1;j<size;j++){
                    com=(data[i].x-data[j].x)*(data[i].x-data[j].x)+(data[i].y-data[j].y)*(data[i].y-data[j].y);
                    if(i==0&&j==1){
                        smallest=com;
                    }
                    else if(smallest>=com){
                        smallest=com;
                    }
                }
        }
    }
    return smallest;
}
long long int Compare(vector<Node> data,vector<Node> datay){
    int size=data.size();
    if(size<=3){
        return compareall(data);
    }
    else{
        int mid=size/2;
        long long int midpoint=data[mid].x;
        vector<Node> data1,data2,data1y,data2y;
        set<int> ll;
        for(int i=0;i<mid;i++){
            data1.push_back(data[i]);
            ll.insert(data[i].id);
        }
        for(int i=mid;i<size;i++){
            data2.push_back(data[i]);
        }
        for(int i=0;i<datay.size();i++){
            if(ll.find(datay[i].id)==ll.end()){
                data2y.push_back(datay[i]);
            }
            else{
                data1y.push_back(datay[i]);
            }
        }
        long long int left=Compare(data1,data1y);
        long long int right=Compare(data2,data2y);
        long long int smallest=left;
        if(right<left){
            smallest=right;
        }
        bool bound=false;
        int low=mid-1;
        while(bound==false&&low!=0){
            if((midpoint-datay[low].x)*(midpoint-datay[low].x)>smallest){
                low=low+1;
                bound=true;
            }
            else{
                low--;
            }
        }
        int up=mid+1;
        bound=false;
        while(bound==false&&up!=size-1){
            if((datay[up].x-midpoint)*(datay[up].x-midpoint)>smallest){
                up=up-1;
                bound=true;
            }
            else{
                up++;
            }
        }
        long long int com;
        vector<Node> data3;
        for(int i=low;i<=up;i++){
            //if((data[i].y-data[mid].y)*(data[i].y-data[mid].y)<smallest){
                data3.push_back(datay[i]);
            //}
        }
        //sort(data3.begin(),data3.end(),comparey);
        for(int i=0;i<data3.size()-1;i++){
            for(int j=i+1;j<data3.size()&&((data3[j].y-data3[i].y)*(data3[j].y-data3[i].y)<smallest);j++){
                com=(data3[i].x-data3[j].x)*(data3[i].x-data3[j].x)+(data3[i].y-data3[j].y)*(data3[i].y-data3[j].y);
                if(smallest>=com){
                    smallest=com;
                }
            }
        }
        return smallest;
    }
}
