#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e6 + 6;

ll dp[SIZE][2],val[SIZE],parent[SIZE],from[SIZE][2];
vector<int> adj[SIZE],result;
ll ans = (ll)-1e18,n,bestver;
bool state = false;

void dfs(int v, int prev){
	ll sum = 0;
	parent[v] = prev;
	for(auto it : adj[v]){
		if(it == prev) continue;
		sum += val[it];
	}
	from[v][1] = v;
	from[v][0] = -1;
	dp[v][1] = val[v];
	dp[v][0] = (ll)-1e18;
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs(it,v);
		if(dp[it][0] + val[v] > dp[v][1]){
			from[v][1] = it;
		}
		if(dp[it][1] + sum - val[it] > dp[v][0]){
			from[v][0] = it;
		}
		dp[v][1] = max(dp[v][1],dp[it][0] + val[v]);
		dp[v][0] = max(dp[v][0],dp[it][1] + sum - val[it]);
	}
}

void dfs2(int v, int prev){
	ll maks1 = 0, maks2 = 0;
	for(auto it : adj[v]){
		if(it == prev) continue;
		if(dp[it][0] >= maks1){
			maks2 = maks1;
			maks1 = dp[it][0];
		} else if(dp[it][0] >= maks2){
			maks2 = dp[it][0];
		}
	}
	if(maks1 + maks2 + val[v] > ans){
		state = true;
		ans = maks1 + maks2 + val[v];
		bestver = v;		
	}
	maks1 = 0, maks2 = 0;
	ll sum = (prev == -1 ? 0 : val[prev]);
	for(auto it : adj[v]){
		if(it == prev) continue;
		sum += val[it];
		if(dp[it][1] - val[it] >= maks1){
			maks2 = maks1;
			maks1 = dp[it][1] - val[it];
		} else if(dp[it][1] - val[it] >= maks2){
			maks2 = dp[it][1] - val[it];
		}
	}
	if(maks1 + maks2 + sum > ans){
		state = false;
		ans = maks1 + maks2 + sum;
		bestver = v;
	}
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs2(it,v);
	}
}

void odzyskaj(int v, bool stan){
	if(stan){
		if(from[v][stan] != v) odzyskaj(from[v][stan],!stan);
		result.push_back(v);
		return;
	} else {
		odzyskaj(from[v][stan],!stan);
		result.push_back(v);
		for(auto it : adj[v]){
			if(it == parent[v] || it == from[v][stan]) continue;
			result.push_back(it);
			result.push_back(v);
		}
	}
}

void odzyskaj2(int v, bool stan){
	if(stan){
		result.push_back(v);
		if(from[v][stan] != v) odzyskaj2(from[v][stan],!stan);
		return;
	} else {
		result.push_back(v);
		for(auto it : adj[v]){
			if(it == parent[v] || it == from[v][stan]) continue;
			result.push_back(it);
			result.push_back(v);
		}
		odzyskaj2(from[v][stan],!stan);
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n;
	
	for(int i = 1; i <= n; i++) cin >> val[i];
	
	for(int i = 1; i < n; i++){
		int a,b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(1,-1);

	dfs2(1,-1);
				
	cout << ans << "\n";
	
	if(state){
		ll maks1 = 0, maks2 = 0, co1 = -1, co2 = -1;
		for(auto it : adj[bestver]){
			if(it == parent[bestver]) continue;
			if(dp[it][0] >= maks1){
				maks2 = maks1;
				co2 = co1;
				maks1 = dp[it][0];
				co1 = it;
			} else if(dp[it][0] >= maks2){
				maks2 = dp[it][0];
				co2 = it;
			}
		}
		if(co1 > 0){
			odzyskaj(co1,0);
		}
		result.push_back(bestver);
		if(co2 > 0){
			odzyskaj2(co2,0);
		}
	} else {
		ll maks1 = 0, maks2 = 0, co1 = -1, co2 = -1, sum = 0;
		for(auto it : adj[bestver]){
			if(it == parent[bestver]) continue;
			sum += val[it];
		}	
		for(auto it : adj[bestver]){
			if(it == parent[bestver]) continue;
			if(dp[it][1] - val[it] >= maks1){
				maks2 = maks1;
				co2 = co1;
				maks1 = dp[it][1] - val[it];
				co1 = it;
			} else if(dp[it][1] - val[it] >= maks2){
				maks2 = dp[it][1] - val[it];
				co2 = it;
			}
		}
		if(co1 > 0){
			odzyskaj(co1,1);
		}
		for(auto it : adj[bestver]){
			if(it == co1 || it == co2) continue;
			result.push_back(bestver);
			result.push_back(it);
		}
		if(co2 > 0){
			result.push_back(bestver);
			odzyskaj2(co2,1);
		}	
	}
	
	ll cursum = 0;
	for(int i = 0; i < result.size(); i+=2) cursum += val[result[i]];
	assert(result.size() % 2);
	assert(cursum == ans);	

	cout << result.size() / 2 + 1 << "\n";
	
	for(auto it : result) cout << it << " ";


}
