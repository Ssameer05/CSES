#include <bits/stdc++.h>
using namespace std;


long long dp[20][11][2][2];
long long helper(string& temp, int pos, int prev,int leading_zeros, int tight){
    int n = temp.size();
    //if leading zero is 1 then it means that we havent started forming out anser 
    //thus if leading zero is 1 then we can alwats skip 
    
    if(pos == n){
        return 1;
    }

    if(dp[pos][prev+1][leading_zeros][tight] != -1) return dp[pos][prev+1][leading_zeros][tight]; 

    int num = temp[pos] - '0';
    if(num < 0) return 0;

    long long take = 0;

    int limit = 9;
    if(tight == 1) limit = num;

    for(int digit = 0; digit <= limit; digit++){
        if(!leading_zeros && digit == prev) continue;
        //if tight is 1 then it means that number has been equal as now 
        int new_leading_zero = leading_zeros & (digit == 0);

        int new_prev = -1;

        if(new_leading_zero == 0) new_prev = digit; 

        int new_tight = tight & (digit == num);
        take += helper(temp,pos+1,new_prev,new_leading_zero,new_tight);
    }

    return dp[pos][prev+1][leading_zeros][tight] = take;
}
int main(){
    long long a, b;
    cin >> a;
    cin >> b;

    //we have to find the numbers from a to b(inclusive) such that adjacent digits are not same
    //thus we have to keep track of the previous digit that we used
    a--;
    string s1 = to_string(a), s2 = to_string(b);

    //we can find the numbers from 0 to s1 and 0 to s2 and answer will be their difference 

    memset(dp,-1,sizeof(dp));

    long long count1 = helper(s1,0,-1,true,1);
    memset(dp,-1,sizeof(dp));
    long long count2 = helper(s2,0,-1,true,1);

    long long ans = count2 - count1;

    cout << ans << '\n';
    return 0;
}