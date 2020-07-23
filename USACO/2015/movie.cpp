#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 20;

ll dp[MAX];

int main() {
	ofstream fout ("movie.out");
	ifstream fin ("movie.in");

	ll n,l; fin >> n >> l;
	vector<ll> duration(n);
	vector<vector<ll> > start(n);
	for(int i = 0; i < n; i++){
		fin >> duration[i];
		ll x; fin >> x;
		for(int j = 0; j < x; j++){
			ll y; fin >> y;
			start[i].push_back(y);
		}
		if(start[i][0] == 0) dp[(1 << i)] = duration[i];
		else dp[(1 << i)] = -1;
	}
	
	int res = 1e9;
	
	for(int i = 1; i < (1 << n); i++){
		if(__builtin_popcount(i) == 1) continue;
		dp[i] = -1;
		for(int j = 0; j < n; j++){
			if(!(i & (1 << j))) continue;
			ll x = dp[i ^ (1 << j)];
			int l = -1, r = start[j].size();
			while(l + 1 < r){
				int mid = (l+r)/2;
				if(start[j][mid] > x) r = mid;
				else l = mid;
			}
			if(l == -1) continue;
			dp[i] = max({dp[i],x,start[j][l] + duration[j]});
		}
	}

	for(int i = 1; i < (1 << n); i++){
		int x = __builtin_popcount(i);
		if(dp[i] >= l) res = min(res,x);
	}

	if(res == 1e9) fout << -1;
	else fout << res;

    return 0;
}
