# include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 2;

int n, m, a[N], b[N], sum[1<<20], used[21][1 << 20];
vector <int> vec[N];

void f(int i, int mask){
      if(i == n){
            puts("YES");
            exit(0);
      }
      if(used[i][mask]) return;
      used[i][mask] = 1;
      for(int j = 0; j < vec[i].size(); j ++){
            int now = vec[i][j];
            if(mask & now) continue;
            f(i + 1, mask | now);
      }
}

int main(){
      cin >> n >> m;

      for(int i = 0; i < n; i ++){
            cin >> a[i];
      }

      for(int i = 0; i < m; i ++){
            cin >> b[i];
      }

      for(int mask = 0; mask < (1 << m); mask ++){
            for(int j = 0; j < m; j ++)
                  if(mask & (1 << j))
                        sum[mask] += b[j];
      }
      for(int i = 0; i < n; i ++){
            for(int mask = 0; mask < (1 << m); mask ++){
                  if(sum[mask] == a[i])
                        vec[i].push_back(mask);
            }
      }

      f(0, 0);

      puts("NO");
}
