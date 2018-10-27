/**
start coding : 11:20
	
**/
# include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 2;

int n, a[N];
long long ans;
vector < int > v;

int main(){
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
	}
	
	for(int i = 1; i <= n; i ++){
		if(!v.empty()){
			int lo = 0, hi = v.size() - 1;
			while(hi - lo > 1){
				int md = (lo + hi) >> 1;
				if(v[md] <= a[i])
					hi = md;
				else 
					lo = md;
			}
			if(v[lo] <= a[i]) hi = lo;
			if(v[hi] <= a[i]) {
				ans += v.size() - hi;	
				if(hi) ans ++;
			} else {
				ans ++;
			}
		}
		while(v.size() && v.back() < a[i]) v.pop_back();
		v.push_back(a[i]);
	}
	
	cout << ans << endl;
}
