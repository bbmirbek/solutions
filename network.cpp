# include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 2;

int n;
vector <int> g[N], l;

void dfs(int v, int pr = 0){
      if(g[v].size() == 1)
            l.push_back(v);
      for(int to : g[v]){
            if(to == pr)
                  continue;
            dfs(to, v);
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

      dfs(1);

      int m = (int)l.size();

      if(m & 1){
            cout << m / 2 + 1 << endl;
            l.push_back(1);
            for(int i = 0; i <= m / 2; i ++)
                  cout << l[i] << " " << l[i + m / 2 + 1] << endl;
      } else {
            cout << m / 2 << endl;
            for(int i = 0; i < m / 2; i ++)
                  cout << l[i] << " " << l[i + m / 2] << endl;
      }
}
