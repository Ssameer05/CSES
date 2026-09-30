// #include <bits/stdc++.h>
// using namespace std;

// // void dfs(int curr_node, vector<vector<int>>& dp, vector<int>& parent, map<int,bool>& vis){
// //     vis[curr_node] = true;
// //     if(curr_node == parent[curr_node]){
// //         dp[curr_node][0] = curr_node;
// //         return;
// //     }
// //     //curr_node ---> jump tp parent[curr_node]
// //     dp[curr_node][0] = parent[curr_node];
// //     if(!vis[parent[curr_node]]) dfs(parent[curr_node],dp,parent,vis);
// //     return;
// // }

// int main(){
//     //since it is given that each planet can go to another planet or to itself only, this means that for every plant/node oudegree is 1 or 0
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n ,q;
//     cin >> n;
//     cin >> q;

//     vector<int>parent(n+1);
//     for(int i = 1; i <= n; i++){
//         cin >> parent[i];
//     }
//     int max_jumps = 30;
//     vector<vector<int>>dp(n+1, vector<int>(max_jumps,-1));
//     map<int,bool>vis;

//     for(int i = 1; i <= n; i++){
//         dp[i][0] = parent[i];
//     }

//     for(int j = 1; j < max_jumps; j++){
//         for(int row = 1; row <= n; row++){
//             int next_node = dp[row][j-1];
//             if(next_node != -1){
//                 dp[row][j] = dp[next_node][j-1];
//             }
//         }
//     }

//     while(q--){
//         int x, k;
//         cin >> x;
//         cin >> k;
//         if(parent[x] == x){
//             cout << x << '\n';
//             continue;
//         }
//         int max_bits = 30;
//         int curr_node = x;
//         for(int bit = 0; bit < max_bits; bit++){
//             if(k & (1 << bit)){
//                 if(curr_node == -1) break;
//                 if(parent[curr_node] == curr_node) break;
//                 curr_node = dp[curr_node][bit];
//             }
//         }
//         cout << curr_node << '\n';
//     }
//     return 0;
// }



#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    // 30 bits are enough for k <= 10^9 (2^29 < 10^9 < 2^30)
    const int max_jumps = 30;
    vector<vector<int>> dp(n + 1, vector<int>(max_jumps, -1));

    for (int i = 1; i <= n; i++) {
        cin >> dp[i][0];
    }

    // Build binary lifting table
    for (int j = 1; j < max_jumps; j++) {
        for (int row = 1; row <= n; row++) {
            int next_node = dp[row][j - 1];
            if (next_node != -1) {
                dp[row][j] = dp[next_node][j - 1];
            }
        }
    }

    // Process queries
    while (q--) {
        int x, k;
        cin >> x >> k;

        int curr_node = x;
        for (int bit = 0; bit < max_jumps; bit++) {
            if (k & (1 << bit)) {
                curr_node = dp[curr_node][bit];
            }
        }
        cout << curr_node << '\n';
    }

    return 0;
}