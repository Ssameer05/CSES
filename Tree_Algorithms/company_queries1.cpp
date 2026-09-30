#include <bits/stdc++.h>
using namespace std;

int solve(int node, int jumps, vector<vector<int>>& dp){
    int max_bits = log2(jumps)+1;
    int curr_node = node;
    for(int bit = 0; bit < max_bits; bit++){
        if(!(jumps & (1 << bit))) continue;
        if(curr_node == -1) return -1;
        curr_node = dp[curr_node][bit];
    }
    return curr_node;
}

void dfs(int curr_node, int par_node, map<int,vector<int>>& adj, vector<vector<int>>& dp){
    dp[curr_node][0] = par_node;
    for(auto it : adj[curr_node]){
        if(it == par_node) continue;
        dfs(it,curr_node,adj,dp);
    }
    return;
}

int main(){
    int n, q;
    cin >> n;
    cin >> q;

    vector<int>nums(n+1);
    nums[0] = -1;
    nums[1] = -1;
    for(int i = 2; i < n+1; i++){
        cin >> nums[i];
    }

    map<int,vector<int>>adj;
    for(int i = 2; i <= n; i++){
        adj[i].push_back(nums[i]);
        adj[nums[i]].push_back(i);
    }
    int max_jumps = log2(n)+1;
    vector<vector<int>>dp(n+1, vector<int>(max_jumps,-1));

    dfs(1,-1,adj,dp);

    for(int j = 1; j < max_jumps; j++){
        for(int node = 2; node <= n; node++){
            int next_node = dp[node][j-1];
            if(next_node != -1){
                dp[node][j] = dp[next_node][j-1];
            }
        }
    }

    while(q--){
        int x, k;
        cin >> x;
        cin >> k;

        //jumps are k
        cout << solve(x,k,dp) << '\n';
    }
    return 0;
}