// #include <bits/stdc++.h>
// using namespace std;

// int solve(int node, int jumps, vector<vector<int>>& dp){
//     int max_bits = log2(jumps) + 1;
//     int curr_node = node;
//     for(int bit = 0; bit < max_bits; bit++){
//         if(jumps & (1 << bit)){
//             if(curr_node == -1) break;
//             curr_node = dp[curr_node][bit];
//         }
//     }
//     return curr_node;
// }

// int helper(int u, int v, vector<int>& depth, vector<vector<int>>& dp){
//     int source = -1, target = -1;
//     int n = dp.size();
//     if(u == v) return u;

//     if(depth[u] < depth[v]){
//         source = v;
//         target = u;
//     }
//     else {
//         source = u;
//         target = v;
//     }

//     int diff = abs(depth[target] - depth[source]);

//     if(diff > 0){
//         source = solve(source,diff,dp);
//     }

//     if(source == target) return target;

//     //now source and target are at same level 
//     //now we have the source and target, so we move them in such a way that they are never equal but we take the max jumps 
//     int max_jumps = dp[0].size() - 1;
//     u = source, v = target;
//     for(int bit = max_jumps; bit >= 0; bit--){
//         int u1 = dp[u][bit];
//         int u2 = dp[v][bit];
//         if(u1 == -1 || u2 == -1) continue;
//         if(u1 != u2){
//             u = u1;
//             v = u2;
//         }
//     }
//     int lca = dp[u][0];
//     return lca;
// }

// void dfs(int curr_node, int par_node, vector<vector<int>>& dp,map<int, vector<int>>& adj,int level, vector<int>& depth){
//     dp[curr_node][0] = par_node;
//     depth[curr_node] = level;
//     for(auto it : adj[curr_node]){
//         if(it == par_node) continue;
//         dfs(it,curr_node,dp,adj,level+1,depth);
//     }
//     return;
// }

// int main(){
//     int n, q;
//     cin >> n;
//     cin >> q;
//     vector<int>arr(n+1,0);

//     for(int i = 2; i <= n; i++){
//         cin >> arr[i];
//     }

//     map<int,vector<int>>adj;
//     for(int i= 2; i <= n; i++){
//         adj[i].push_back(arr[i]);
//         adj[arr[i]].push_back(i);
//     }
//     int max_jumps = log2(n)+1;
//     vector<vector<int>>dp(n+1, vector<int>(max_jumps,-1));
//     vector<int>depth(n+1,0);

//     dfs(1,-1,dp,adj,1,depth);

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
//         cin >> node1;
//         cin >> node2;
//         cout << helper(node1,node2,depth,dp) << '\n';
//     }
//     return 0;
// }




#include <bits/stdc++.h>
using namespace std;

// O(log N) jump using precomputed powers of 2
int solve(int node, int jumps, int max_jumps, const vector<vector<int>>& dp) {
    int curr_node = node;
    for (int bit = 0; bit < max_jumps; bit++) {
        if ((jumps >> bit) & 1) {
            if (curr_node == -1) break;
            curr_node = dp[curr_node][bit];
        }
    }
    return curr_node;
}

int helper(int u, int v, int max_jumps, const vector<int>& depth, const vector<vector<int>>& dp) {
    if (u == v) return u;

    int source = (depth[u] > depth[v]) ? u : v;
    int target = (depth[u] > depth[v]) ? v : u;

    int diff = depth[source] - depth[target];
    if (diff > 0) {
        source = solve(source, diff, max_jumps, dp);
    }

    if (source == target) return target;

    // Binary lifting to find LCA
    for (int bit = max_jumps - 1; bit >= 0; bit--) {
        int u1 = dp[source][bit];
        int v1 = dp[target][bit];
        if (u1 != -1 && u1 != v1) {
            source = u1;
            target = v1;
        }
    }
    return dp[source][0];
}

void dfs(int curr_node, int par_node, vector<vector<int>>& dp, const vector<vector<int>>& adj, int level, vector<int>& depth) {
    dp[curr_node][0] = par_node;
    depth[curr_node] = level;
    for (int neighbor : adj[curr_node]) {
        if (neighbor == par_node) continue;
        dfs(neighbor, curr_node, dp, adj, level + 1, depth);
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<vector<int>> adj(n + 1);

    // Read parent array for nodes 2 to N
    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        adj[i].push_back(parent);
        adj[parent].push_back(i);
    }

    int max_jumps = __lg(n) + 1; // Faster integer log2 computation
    vector<vector<int>> dp(n + 1, vector<int>(max_jumps, -1));
    vector<int> depth(n + 1, 0);

    // Precalculate depths & parents
    dfs(1, -1, dp, adj, 1, depth);

    // Build binary lifting table
    for (int j = 1; j < max_jumps; j++) {
        for (int node = 1; node <= n; node++) {
            int next_node = dp[node][j - 1];
            if (next_node != -1) {
                dp[node][j] = dp[next_node][j - 1];
            }
        }
    }

    // Process queries
    while (q--) {
        int node1, node2;
        cin >> node1 >> node2;
        cout << helper(node1, node2, max_jumps, depth, dp) << '\n';
    }

    return 0;
}