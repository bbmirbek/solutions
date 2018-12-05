#include "group.h"

#include <bits/stdc++.h>

# define f first
# define s second

using namespace std;

const long long N = 1e5 + 2;

long long n;
pair <long long, long long> ar[N];

bool check(long long x){
      long long a = 1, b = n, mx, mn;
      while(a + 1 <= n && ar[a + 1].f - ar[1].f <= x) a ++;
      while(b - 1 >= 1 && ar[n].f - ar[b - 1].f <= x) b --;
      if(a + 1 < b) return 0;
      if(a + 1 == b){
            mx = mn = ar[1].s;
            for(long long i = 2; i <= a; i ++)
                  mx = max(mx, ar[i].s), mn = min(mn, ar[i].s);
            if(mx - mn > x) return 0;
            mx = mn = ar[n].s;
            for(long long i = n - 1; i >= b; i --)
                  mx = max(mx, ar[i].s), mn = min(mn, ar[i].s);
            return mx - mn <= x;
      }
      if(a == n){
            mx = mn = ar[1].s;
            for(long long i = 2; i <= n; i ++)
                  mx = max(mx, ar[i].s), mn = min(mn, ar[i].s);
            for(long long i = 1; i <= n; i ++){
                  if(mn + x < ar[i].s && ar[i].s + x < mx) return 0;
            }
            return 1;
      }
      vector <long long> v;
      for(long long i = b; i <= a; i ++)
            v.push_back(ar[i].s);
      sort(v.begin(), v.end());
      long long mx1, mx2, mn1, mn2;
      mx1 = mn1 = ar[1].s;
      mx2 = mn2 = ar[n].s;
      for(long long i = 1; i < b; i ++)
            mx1 = max(mx1, ar[i].s), mn1 = min(mn1, ar[i].s);
      for(long long i = a + 1; i <= n; i ++)
            mx2 = max(mx2, ar[i].s), mn2 = min(mn2, ar[i].s);
      if(mx1 - mn1 > x || mx2 - mn2 > x) return 0;
      if(max(mx1, v.back()) - min(mn1, v[0]) <= x) return 1;
      if(max(mx2, v.back()) - min(mn2, v[0]) <= x) return 1;
      for(long long i = 0; i < v.size() - 1; i ++){
            mx = max(v[i], mx1) - min(mn1, v[0]);
            mx = max(mx, max(v.back(), mx2) - min(mn2, v[i + 1]));
            if(mx <= x) return 1;
            mx = max(v[i], mx2) - min(mn2, v[0]);
            mx = max(mx, max(v.back(), mx1) - min(mn1, v[i + 1]));
            if(mx <= x) return 1;
      }
      return 0;
}

int getMinimumDelay(int N, vector<int> X, vector<int> Y) {
      n = N;
      for(long long i = 0; i < N; i ++){
            ar[i + 1] = {X[i] + Y[i], X[i] - Y[i]};
      }
      sort(ar + 1, ar + N + 1);
      long long lo = 0, hi = 1e18;
      while(hi - lo > 1){
            long long md = (lo + hi) >> 1;
            if(check(md))
                  hi = md;
            else
                  lo = md;
      }
      if(check(lo)) hi = lo;
      return int(hi);
}
