# include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 2;

int n, m, q, par[N], sz[N];
int p[20][N], mn[20][N], tin[N], tout[N], timer;
vector < pair <int, int> > v[N], g[N];

int get(int v){
      return (par[v] == v) ? v : par[v] = get(par[v]);
}

void unite(int a, int b){
      if(sz[a] < sz[b])
            swap(a, b);
      par[b] = a;
      sz[a] += sz[b];
}

void dfs(int v, int pr = 0, int we = 0){
      tin[v] = ++ timer;
      p[0][v] = pr;
      mn[0][v] = we;
      for(int i = 1; i < 20; i ++){
            p[i][v] = p[i - 1][ p[i - 1][v] ];
            mn[i][v] = min(mn[i - 1][v], mn[i - 1][ p[i - 1][v] ]);
      }
      for(int i = 0; i < g[v].size(); i ++){
            int to = g[v][i].first, w = g[v][i].second;
            if(to == pr) continue;
            dfs(to, v, w);
      }
      tout[v] = timer;
}

bool upper(int a, int b){
      return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int main(){
      scanf("%d %d %d", &n, &m, &q);

      for(int i = 1; i <= n; i ++)
            par[i] = i, sz[i] = 1;

      for(int i = 1; i <= m; i ++){
            for(int j = i + i; j <= n; j += i){
                  v[__gcd(i, j)].push_back({i, j});
            }
      }

      for(int i = m; i >= 1; i --){
            for(int j = 0; j < v[i].size(); j ++){
                  int a = v[i][j].first, b = v[i][j].second;
                  if(get(a) != get(b)){
                        g[a].push_back({b, i});
                        g[b].push_back({a, i});
                        unite(get(a), get(b));
                  }
            }
      }

      dfs(1);

      while(q --){
            int a, b, ans = 1e9;
            cin >> a >> b;
            if(!upper(a, b)){
                  for(int i = 19; i >= 0; i --){
                        if(p[i][a] && !upper(p[i][a], b)){
                              ans = min(ans, mn[i][a]);
                              a = p[i][a];
                        }
                  }
                  ans = min(ans, mn[0][a]);
            }
            if(!upper(b, a)){
                  for(int i = 19; i >= 0; i --){
                        if(p[i][b] && !upper(p[i][b], a)){
                              ans = min(ans, mn[i][b]);
                              b = p[i][b];
                        }
                  }
                  ans = min(ans, mn[0][b]);
            }
            cout << m - ans + 1 << endl;
      }
}

