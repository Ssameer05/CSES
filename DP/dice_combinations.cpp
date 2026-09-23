#include <bits/stdc++.h>
using namespace std;

int helper(int curr, int n, vector<int>& dp){
    if(curr == n) return 1;
    if(curr > n) return 0;
    const int mod = 1e9+7;
    int temp = 0;

    if(dp[curr] != -1) return dp[curr];
    for(int i = 1; i <= 6; i++){
        temp = (temp + helper(curr+i,n,dp))%mod;
    }
    return dp[curr] = temp;
}

int main(){
    int n;
    cin >> n;
    const int mod = 1e9+7;
    vector<int>dp(n+1,-1);
    int ans = helper(0,n,dp);
    cout << ans << '\n';
    return 0;

}