# include <bits/stdc++.h>

using namespace std;

const int N = 33002;

int n, m, k, mt[N], used[N], ans, L, R, pt = 1;
vector <int> g[N], mr;

bool dfs(int v){
      if(used[v])
            return 0;
      used[v] = 1;
      for(int to : g[v]){
            if(to < L) break;
            if(to <= n && to > R)
                  continue;
            if(mt[to] == -1 || dfs(mt[to])){
                  mt[to] = v;
                  mt[v] = to;
                  return true;
            }
      }
      return false;
}

bool check(){
      while(!mr.empty()){
            int v = mr.back();
            if(mt[v] == -1){
                  memset(used, 0, sizeof(used));
                  if(!dfs(v))
                        return false;
            }
            mr.pop_back();
      }
      return mr.empty();
}

int main(){
      scanf("%d %d %d", &n, &m, &k);

      for(int i = 1; i <= k; i ++){
            int a, b;
            scanf("%d %d", &a, &b);
            g[a].push_back(b + n);
            g[b + n].push_back(a);
      }

      for(int i = n + 1; i <= n + m; i ++)
            sort(g[i].rbegin(), g[i].rend());

      memset(mt, -1, sizeof(mt));

      for(int i = n + 1; i <= n + m; i ++)
            mr.push_back(i);

      for(int i = 1; i <= n; i ++){
            L = i, R = pt;
            while(pt <= n && !check())
                  pt ++, R = pt;
            ans += n - pt + 1;
            if(mt[L] != -1){
                  mt[mt[L]] = -1;
                  mr.push_back(mt[L]);
            }
      }

      printf("%d", ans);
}
