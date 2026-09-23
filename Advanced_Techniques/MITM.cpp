#include <bits/stdc++.h>
using namespace std;
 
void helper(vector<int>& nums,vector<long long>& curr, int start, int end){
    int m = end - start + 1;
    long long full_mask = 1LL << m;
    vector<long long> temp(m,0);
    for(int i =start; i <= end; i++) temp[i-start] = 1LL*nums[i];
 
    for(int mask = 0; mask < full_mask; mask++){
        long long sum = 0;
        for(int bit = 0; bit < m; bit++){
            // int index = (m-1) - bit;
            if(mask & (1LL << bit)) sum += temp[bit];
        }
        curr.push_back(sum);
    }
    return;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n;
    long long x;
    cin >> n;
    cin >> x;
    vector<int>nums(n,0);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
 
    // we first generate the subsets sums for left and right half using mask or rcusrison
    int n1 = n/2, n2 = n - n1;
    vector<long long>left_sum, right_sum;
    
    helper(nums,left_sum,0,n1-1);
    helper(nums,right_sum,n1,n-1);
 
    sort(right_sum.begin(), right_sum.end());
 
    long long count = 0;
 
    //now we iterate over all the vlues in left_sum and find the correspodning right_sum 
 
    for(auto it : left_sum){
        long long sum1 = it, sum2 = x - it;
 
        auto lb = lower_bound(right_sum.begin(), right_sum.end(), sum2);
        auto ub = upper_bound(right_sum.begin(), right_sum.end(), sum2);
        if(lb == ub) continue;//this particular sum doesnt exist in right_sum
 
        count += ub - lb;
    }
    cout << count << '\n';
    return 0;
}