# include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 2;

int n, up[N];
vector <int> g[N], roots;
pair <long long, long long> ans, dp[N];

void dfs1(int v, int pr = 0){
      dp[v] = {0, 1};
      for(int to : g[v]){
            if(to == pr)
                  continue;
            dfs1(to, v);
            if(dp[to].first + 1 > dp[v].first){
                  dp[to].first ++;
                  dp[v] = dp[to];
                  dp[to].first --;
            } else if(dp[to].first + 1 == dp[v].first){
                  dp[v].second += dp[to].second;
            }
      }
}

void dfs2(int v, int pr = 0){
      pair <int, int> mx[2];
      mx[0].first = mx[1].first = -1;
      if(up[v] > mx[0].first)
            mx[0] = {up[v], pr};
      for(int to : g[v]){
            if(to == pr)
                  continue;
            if(dp[to].first + 1 > mx[0].first){
                  mx[1] = mx[0];
                  mx[0] = {dp[to].first + 1, to};
            } else if(dp[to].first + 1 > mx[1].first)
                  mx[1] = {dp[to].first + 1, to};
      }
      for(int to : g[v]){
            if(to == pr)
                  continue;
            if(mx[0].second != to){
                  up[to] = mx[0].first + 1;
            } else {
                  up[to] = mx[1].first + 1;
            }
            dfs2(to, v);
      }
}

void update(int &mx1, int &mx2, int &mx3, int val){
      if(val > mx1){
            mx3 = mx2;
            mx2 = mx1;
            mx1 = val;
      } else if(val > mx2){
            mx3 = mx2;
            mx2 = val;
      } else if(val > mx3){
            mx3 = val;
      }
}

void dfs3(int v, int pr = 0){
      int mx1 = -1, mx2 = -1, mx3 = -1;
      if(pr){
            update(mx1, mx2, mx3, up[v]);
      }
      for(int to : g[v]){
            if(to == pr)
                  continue;
            dfs3(to, v);
            update(mx1, mx2, mx3, dp[to].first + 1);
      }
      if(mx3 != -1){
            long long ret = (mx2 + mx3)  * 1ll * mx1;
            if(ret > ans.first){
                  ans.first = ret;
                  roots.clear();
            }
            if(ret == ans.first)
                  roots.push_back(v);
      }
}

void dfs(int root){
      vector < pair <long long, long long> > vec;
      dfs1(root);
      for(int to : g[root]){
            dp[to].first ++;
            vec.push_back(dp[to]);
      }
      if(vec.size() < 3)
            return ;
      sort(vec.rbegin(), vec.rend());
      while(vec.size() > 3 && vec.back().first < vec[2].first)
            vec.pop_back();
      int sum = 0;
      for(int i = 0; i < vec.size(); i ++){
            if(vec[i].first == vec[2].first)
                  sum += vec[i].second;
      }
      for(int i = 0; i < vec.size(); i ++){
            if(vec[i].first == vec[2].first)
                  sum -= vec[i].second;
            if(vec[i].first == vec[1].first)
                  ans.second += vec[i].second * 1ll * sum;
      }
}

int main(){
      scanf("%d", &n);

      for(int i = 1; i < n; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
      }

      dfs1(1);
      dfs2(1);
      dfs3(1);

      for(int i = 0; i < roots.size(); i ++){
            dfs(roots[i]);
      }

      if(ans.first == 0)
            ans.second = 1;

      cout << ans.first << " " << ans.second << endl;
}
