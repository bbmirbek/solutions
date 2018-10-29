# include <bits/stdc++.h>

using namespace std;

const int N = 52;

int n, a[N], dp[N][N][N][N];

int get(int l, int r, int mx, int mn){
	if(dp[l][r][mx][mn] >= 0) return dp[l][r][mx][mn];
	if(mx > mn) return -1e9;
	if(l > r) return 0;
	if(l == r) {
		if(mx <= a[l] && a[l] <= mn) return 1;
		return 0;
	}
	dp[l][r][mx][mn] = 0;
	int &res = dp[l][r][mx][mn]; 
	res = max(res, get(l + 1, r - 1, mx, mn));
	if(a[r] >= mx){
		res = max(res, get(l + 1, r - 1, a[r], mn) + 1);
	}
	if(a[l] <= mn){
		res = max(res, get(l + 1, r - 1, mx, a[l]) + 1);
	}
	if(a[r] <= a[l] && mx <= a[r] && a[l] <= mn){
		res = max(res, get(l + 1, r - 1, a[r], a[l]) + 2);
	}
	res = max(res, get(l, r - 1, mx, mn));
	if(a[r] <= mn){
		res = max(res, get(l, r - 1, mx, a[r]) + 1);
	}
	res = max(res, get(l + 1, r, mx, mn));
	if(a[l] >= mx){
		res = max(res, get(l + 1, r, a[l], mn) + 1);
	}
	return res;
}

int main(){
	freopen("subrev.in", "r", stdin);
	freopen("subrev.out", "w", stdout);
	
	cin >> n;
	
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	
	memset(dp, -1, sizeof(dp));
	
	cout << get(1, n, 0, 50) << endl;
}
