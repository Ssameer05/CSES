// #include <bits/stdc++.h>
// using namespace std;

// int solve(int node, int jumps, vector<vector<int>>& dp){
//     int max_jumps = dp[0].size();
//     int curr_node = node;
//     for(int bit = 0; bit < max_jumps; bit++){
//         if(curr_node == -1) break;
//         if(jumps & (1 << bit)){
//             curr_node = dp[curr_node][bit];
//         }
//     }
//     return curr_node;
// }

// int helper(int u, int v,vector<int>& depth,vector<vector<int>>& dp){
//     int source = -1, target = -1;
//     if(u == v) return 0;
//     if(depth[u] > depth[v]){
//         source = u;
//         target = v;
//     }
//     else{
//         source = v;
//         target = u;
//     }

//     int diff = abs(depth[source] - depth[target]);
//     int extra_low = 0;
//     if(diff > 0){
//         extra_low += diff;
//         source = solve(source,diff,dp);
//     }

//     if(source == target) return extra_low;

//     int extra_equal = 0;

//     int low = 1, high = depth[source];
//     while(low <= high){
//         int mid = (low+high)/2;

//         int ns = solve(source,mid,dp);
//         int nt = solve(target,mid,dp);
//         if(ns == -1 || nt == -1) high = mid-1;

//         else if(ns == nt){
//             extra_equal = mid;
//             high = mid-1;
//         }
//         else low= mid+1;
//     }
//     return 2*extra_equal + extra_low;
// }

// void dfs(int curr_node, int par_node,vector<int>& depth,vector<vector<int>>& dp,vector<vector<int>>& adj,int level){
//     depth[curr_node] = level;
//     dp[curr_node][0] = par_node;
//     for(auto it : adj[curr_node]){
//         if(it == par_node) continue;
//         dfs(it,curr_node,depth,dp,adj,level+1);
//     }
//     return;
// }
// int main(){

//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n, q;
//     cin >> n >> q;

//     vector<vector<int>>adj(n+1);

//     for(int i = 2; i <= n;i++){
//         int x, y;
//         cin >> x >> y;
//         adj[x].push_back(y);
//         adj[y].push_back(x);
//     }
//     int max_jumps = log2(n)+1;
//     vector<vector<int>>dp(n+1, vector<int>(max_jumps,-1));
//     vector<int>depth(n+1,0);

//     dfs(1,-1,depth,dp,adj,1);

//     for(int j = 1; j < max_jumps; j++){
//         for(int node = 1; node <= n; node++){
//             int next_node = dp[node][j-1];
//             if(next_node != -1){
//                 dp[node][j] = dp[next_node][j-1];
//             }
//         }
//     }

//     while(q--){
//         int node1,node2;
//         cin >> node1 >> node2;
//         cout << helper(node1,node2,depth,dp) << '\n';
//     }
//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

// Fast binary jump in O(log N)
int solve(int node, int jumps, vector<vector<int>>& dp) {
    int max_jumps = dp[0].size();
    int curr_node = node;
    for (int bit = 0; bit < max_jumps; bit++) {
        if (curr_node == -1) break;
        if ((jumps >> bit) & 1) {
            curr_node = dp[curr_node][bit];
        }
    }
    return curr_node;
}

// Distance query in O(log N) using Binary Lifting
int helper(int u, int v, vector<int>& depth, vector<vector<int>>& dp) {
    if (u == v) return 0;

    int source = (depth[u] > depth[v]) ? u : v;
    int target = (depth[u] > depth[v]) ? v : u;

    int extra_low = depth[source] - depth[target];
    if (extra_low > 0) {
        source = solve(source, extra_low, dp);
    }

    if (source == target) return extra_low;

    int max_jumps = dp[0].size();
    int extra_equal = 0;

    // Move upwards simultaneously as long as parents differ
    for (int bit = max_jumps - 1; bit >= 0; bit--) {
        int ns = dp[source][bit];
        int nt = dp[target][bit];

        if (ns != -1 && nt != -1 && ns != nt) {
            source = ns;
            target = nt;
            extra_equal += (1 << bit);
        }
    }

    // Step up one last node to reach LCA
    extra_equal += 1;

    return 2 * extra_equal + extra_low;
}

// DFS with const reference to avoid std::vector copies
void dfs(int curr_node, int par_node, vector<int>& depth, vector<vector<int>>& dp, const vector<vector<int>>& adj, int level) {
    depth[curr_node] = level;
    dp[curr_node][0] = par_node;
    for (auto it : adj[curr_node]) {
        if (it == par_node) continue;
        dfs(it, curr_node, depth, dp, adj, level + 1);
    }
}

int main() {
    // Fast I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> adj(n + 1);

    for (int i = 2; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int max_jumps = log2(n) + 1;
    vector<vector<int>> dp(n + 1, vector<int>(max_jumps, -1));
    vector<int> depth(n + 1, 0);

    // Compute node depths and initial parents
    dfs(1, -1, depth, dp, adj, 1);

    // Build binary lifting DP table
    for (int j = 1; j < max_jumps; j++) {
        for (int node = 1; node <= n; node++) {
            int next_node = dp[node][j - 1];
            if (next_node != -1) {
                dp[node][j] = dp[next_node][j - 1];
            }
        }
    }

    // Process Q queries
    while (q--) {
        int node1, node2;
        cin >> node1 >> node2;
        cout << helper(node1, node2, depth, dp) << '\n';
    }

    return 0;
}