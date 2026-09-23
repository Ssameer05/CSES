#include <bits/stdc++.h>
using namespace std;
 
// Constraints
 
//n --> 10^4
//k --> 30 
 
int main(){
    int n, k;
    cin >> n;
    cin >> k;
 
    vector<string>curr(n);
    for(int i = 0; i < n; i++){
        cin >> curr[i];
    }
 
    //the hamming distance of two numbers is the no of set bits in their xor
 
    vector<int>nums;
    for(auto it : curr) nums.push_back(stoi(it, nullptr, 2));
 
    int ans = INT_MAX;
 
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            int x = nums[i]^nums[j];
            ans = min(ans, __builtin_popcount(x));
        }
    }
 
    cout << ans << '\n';
    return 0;
    
}
