#include <bits/stdc++.h>
using namespace std;

int dp[100][100] = {0};
int rooms[100][100];
int n,m;

int recur(int x, int y, int p){
    if(dp[x][y] > 0){
        return dp[x][y];
    }
    int ans = 0;
    if(p && x>0 && rooms[x-1][y] > rooms[x][y]){
        ans = max(ans, recur(x-1, y,p));
    }
    if(p && y>0 && rooms[x][y-1] > rooms[x][y]){
        ans = max(ans, recur(x, y-1,p));
    }
    if(x<n-1 && rooms[x+1][y] > rooms[x][y]){
        ans = max(ans, recur(x+1, y,p));
    }
    if(y<m-1 && rooms[x][y+1] > rooms[x][y]){
        ans = max(ans, recur(x, y+1,p));
    }
    dp[x][y] = ans+1;
    return dp[x][y];
}

int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>rooms[i][j];
        }
    }    
    recur(0,0,0);
    cout<<dp[0][0]<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dp[i][j] = 0;
        }
    }
    recur(0,0,1);
    cout<<dp[0][0]<<" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(dp[i][j]==0){
                recur(i,j,1);
            }
        }
    }
    int ans = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans = max(ans, dp[i][j]);
        }
    }
    cout<<ans<<endl;
}