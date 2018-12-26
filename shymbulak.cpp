# include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 2;

int n, m, used[N], ar[N];
vector <int> g[N], vr;
pair <int, long long> ans, mx[N];
int b[N * 4], val[N * 4];
pair <int, int> t[N * 4];

void cycle(int v, int pr = 0){
      used[v] = 1;
      vr.push_back(v);
      for(int to : g[v]){
            if(to == pr)
                  continue;
            if(used[to]){
                  if(m)
                        continue;
                  for(int j = (int)vr.size() - 1; j >= 0; j --){
                        ar[++ m] = vr[j];
                        if(vr[j] == to)
                              break;
                  }
            } else {
                  cycle(to, v);
            }
      }
      vr.pop_back();
}

void mrg(pair <int, long long> &a, pair <int, long long> b){
      b.first ++;
      if(b.first > a.first)
            a = b;
      else if(b.first == a.first)
            a.second += b.second;
}

void dfs(int v){
      used[v] = 1;
      vector < pair <int, long long> > vec;
      mx[v] = {0, 1};
      for(int to : g[v]){
            if(used[to])
                  continue;
            dfs(to);
            mrg(mx[v], mx[to]);
            mx[to].first ++;
            vec.push_back(mx[to]);
            mx[to].first --;
      }
      if(mx[v].first > ans.first){
            ans = mx[v];
            ans.second *= 2;
      } else if(mx[v].first == ans.first) {
            ans.second += mx[v].second * 2;
      }
      if((int)vec.size() < 2)
            return ;
      sort(vec.rbegin(), vec.rend());
      while((int)vec.size() > 2 && vec.back().first < vec[1].first)
            vec.pop_back();
      int ret = vec[0].first + vec[1].first, sz = (int)vec.size();
      long long cnt = 0;
      if(vec[0].first == vec[1].first){
            int sum = 0;
            for(int i = 0; i < vec.size(); i ++)
                  sum += vec[i].second;
            for(int i = 0; i < vec.size(); i ++){
                  cnt += (sum - vec[i].second) * 1ll * vec[i].second;
            }
      } else {
            for(int i = 1; i < vec.size(); i ++)
                  cnt += vec[i].second;
            cnt *= vec[0].second;
            cnt *= 2;
      }
      if(ret > ans.first){
            ans = {ret, cnt};
      } else if(ret == ans.first){
            ans.second += cnt;
      }
}

pair <int, int> combine(pair <int, int> a, pair <int, int> b){
      if(b > a)
            swap(a, b);
      if(b.first == a.first)
            a.second += b.second;
      return a;
}

void build(int v = 1, int tl = 1, int tr = m){
      if(tl == tr){
            t[v] = {mx[ar[tl]].first + min(tl - 1, m - tl + 1), mx[ar[tl]].second};
      } else {
            int tm = (tl + tr) >> 1;
            build(v << 1, tl, tm);
            build((v << 1) | 1, tm + 1, tr);
            t[v] = combine(t[v << 1], t[(v << 1) | 1]);
      }
}

void push(int v, int tl, int tr){
      if(b[v]){
            t[v].first += val[v];
            if(tl != tr){
                  val[v << 1] += val[v];
                  val[(v << 1) | 1] += val[v];
                  b[v << 1] = 1;
                  b[(v << 1) | 1] = 1;
            }
      }
      b[v] = 0;
      val[v] = 0;
}

void update(int l, int r, int x, int v = 1, int tl = 1, int tr = m){
      push(v, tl, tr);
      if(l > tr || tl > r)
            return ;
      if(l <= tl && tr <= r){
            b[v] = 1;
            val[v] += x;
            push(v, tl, tr);
            return ;
      }
      int tm = (tl + tr) >> 1;
      update(l, r, x, v << 1, tl, tm);
      update(l, r, x, (v << 1) | 1, tm + 1, tr);
      t[v] = combine(t[v << 1], t[(v << 1) | 1]);
}

pair <int, int> get(int l, int r, int v = 1, int tl = 1, int tr = m){
      push(v, tl, tr);
      if(l > tr || tl > r)
            return {0, 0};
      if(l <= tl && tr <= r)
            return t[v];
      int tm = (tl + tr) >> 1;
      return combine(get(l, r, v << 1, tl, tm),
                        get(l, r, (v << 1) | 1, tm + 1, tr));
}

int main(){
      scanf("%d", &n);

      for(int i = 1; i <= n; i ++){
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
      }

      ans = {-1, 0};

      cycle(1);
      memset(used, 0, sizeof(used));
      for(int i = 1; i <= m; i ++){
            used[ar[i]] = 1;
      }
      for(int i = 1; i <= m; i ++){
            dfs(ar[i]);
      }

      build();

      for(int i = 1; i <= m; i ++){
            pair <int, long long> ret;
            if(i > 1 && i < m){
                  ret = combine(get(1, i - 1), get(i + 1, m));
            } else if(i > 1)
                  ret = get(1, i - 1);
            else
                  ret = get(i + 1, m);
            if(m % 2 == 0){
                  pair <int, int> p;
                  if(i + (m / 2) <= m){
                        p = get(i + (m / 2), i + (m / 2));
                  } else {
                        p = get(i - (m / 2), i - (m / 2));
                  }
                  if(p.first == ret.first)
                        ret.second += p.second;
            }
            ret.first += mx[ar[i]].first;
            ret.second = ret.second * mx[ar[i]].second;
            if(ret.first > ans.first)
                  ans = ret;
            else if(ret.first == ans.first)
                  ans.second += ret.second;
            int l = i - ((m + 1) / 2 - 1), r = i + (m + 1) / 2;
            if(l < 1){
                  update(1, i, 1);
                  update(m + l, m, 1);
            } else {
                  update(l, i, 1);
            }
            if(r > m){
                  update(i + 1, m, -1);
                  update(1, r - m, -1);
            } else {
                  update(i + 1, r, -1);
            }
      }

      cout << ans.second / 2 << endl;
}
