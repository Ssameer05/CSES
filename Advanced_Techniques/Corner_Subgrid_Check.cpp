#include <bits/stdc++.h>
using namespace std;
 
int main(){
    int n, k;
    cin >> n;
    cin >> k;
 
   vector<string>grid(n);
 
   for(int i = 0; i < n; i++) cin >> grid[i];
 
   vector<bool>seen(26,false);
 
    for(char ch = 'A'; ch <= 'Z'; ch++){
        int i = ch - 'A';
        vector<vector<bool>>vis(n,vector<bool>(n,false));
        bool flag = false;
        
        for(int row = 0; !flag && row < n; row++){
            vector<int>cols;
            for(int col = 0; col < n; col++){
                if(grid[row][col] == ch) cols.push_back(col);
            }
 
            int m = cols.size();
            for(int i = 0; !flag && i < m; i++){
                for(int j = i+1; j < m; j++){
                    int c1 = cols[i], c2 = cols[j];
                    if(vis[c1][c2]){
                        flag = true;
                        break;
                    }
                    else{
                        vis[c1][c2] = true;
                    }
                }
            }
        }
        
        seen[i] = flag;
    }
 
    for(int i = 0; i < k; i++){
        if(seen[i]){
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }
   return 0;
}