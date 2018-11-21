# include <bits/stdc++.h>

using namespace std;

const int N = 3e3 + 2;

int n, m, dp[4][N], fl[3][N][N], ans;
char c[N][N];

int main(){
      scanf("%d %d", &n, &m);

      for(int i = 1; i <= n; i ++){
            scanf("\n");
            for(int j = 1; j <= m; j ++)
                  scanf("%c", &c[i][j]);
      }

      for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
                  if(c[i][j] == 'G'){
                        if(c[i - 1][j] == 'R' && c[i + 1][j] == 'W')
                              fl[1][i][j] = 1;
                        if(c[i][j - 1] == 'R' && c[i][j + 1] == 'W')
                              fl[2][i][j] = 1;
                  }
            }
      }

      for(int d = 2; d <= n + m; d ++){
            int last = 0;
            memset(dp, 0, sizeof(dp));
            for(int i = 1; i <= n; i ++){
                  int j = d - i;
                  if(1 > j || j > m) continue;
                  dp[0][i] = max(dp[0][i - 1], max(dp[1][i - 1], dp[2][i - 1]));
                  if(fl[1][i][j])
                        dp[1][i] = max(dp[0][i - 1], dp[1][i - 1]) + 1;
                  if(fl[2][i][j])
                        dp[2][i] = max(dp[0][i - 1], dp[2][i - 1]) + 1;
                  last = i;
            }
            ans += max(dp[0][last], max(dp[1][last], dp[2][last]));
      }

      cout << ans << endl;
}
