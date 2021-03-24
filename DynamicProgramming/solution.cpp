#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

long **Min(NULL);
vector<int> Start,End;
int Size;

void MinOp(int i, int j, vector<pair<int,int>> Mat){

    Min[i][j]=numeric_limits<int>::max();
    if (i+1==j) {
        Min[i][j]=Mat[i].first*Mat[i].second*Mat[j].second;
    }
    for (int k=i;k<j;k++){
        long tmp= Min[i][k]+Min[k+1][j];
        if (k==i){
            tmp+=Mat[i].first*Mat[i].second*Mat[j].second;
        }
        else if (k+1==j){
            tmp+=Mat[j].first*Mat[j].second*Mat[i].first;
        }
        if (tmp<Min[i][j]) {
            Min[i][j]=tmp;
        }
    }
}

long MinValue(vector<pair<int,int>> Mat){

    for(int i=0;i<Size;i++){
        Min[i][i]=0;
    }
    int j;
    for(int s=1;s<Size;s++){
        for(int i=0;i<Size-s;i++){
            j=i+s;
            MinOp(i,j,Mat);
        }
    }
    return Min[0][Size-1];
}

void Reconstruct(int i,int j,vector<pair<int,int>> Mat){

    if (i>=j){
       return;
    }
    for(int k=i;k<j;k++) {
        long tmp= Min[i][k]+Min[k+1][j];
        if (k==i){
            tmp+=Mat[i].first*Mat[i].second*Mat[j].second;
        }
        else if (k+1==j){
            tmp+=Mat[j].first*Mat[j].second*Mat[i].first;
        }
        if (tmp==Min[i][j]){
            Start.push_back(i);Start.push_back(k+1);
            End.push_back(k);End.push_back(j);
            Reconstruct(i,k,Mat);
            Reconstruct(k+1,j,Mat);
        }
    }
}

//Your program will be evaluated by this main method and several test cases.
int main()
{
    cin>>Size;
    vector<int> Input;
    for(int i=0;i<Size;i++){
        int tmp;cin>>tmp;
        Input.push_back(tmp);
    }

    Size-=1;
    Min=new long*[Size];
    vector<pair<int,int>> Mat;
    for(int i=0;i<Size;i++){
        Min[i]=new long[Size];
        pair<int,int> tmp;
        tmp.first=Input[i];tmp.second=Input[i+1];
        Mat.push_back(tmp);
    }

    long Op=MinValue(Mat);
    Reconstruct(0,Size-1,Mat);
    vector<char> Res;
    char ch='A';
    bool tmp=false;

    for(int i=0;i<Size;i++){
        int n=0;
        for(int j=0;j<Start.size();j++){
            if (i==Start[j]){
                if (Start[j]!=End[j]){
                   Res.push_back('(');
                }
            }
            if (i==End[j]){
                if (Start[j]!=End[j]){
                   n++;
                   tmp=true;
                }
            }
        }
        Res.push_back(ch+i);
        if(tmp){
            tmp=false;
            for(int k=0;k<n;k++)
               Res.push_back(')');
        }
    }

    cout<<"Optimal Parenthesization is : ";
    for(int i=0;i<Res.size();i++) {
        cout<<Res[i];
    }

    cout<<"Optimal Cost is : "<<Op;
}