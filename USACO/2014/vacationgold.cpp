#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 2e4 + 4;
const ll LINF = (ll)1e18 + 69;
int n,m,k,q;
vector<pair<int,ll> > adj[SIZE];
int numer[SIZE];
vector<int> special;
ll dis[202][SIZE];

int main() {
	ofstream fout ("vacationgold.out");
	ifstream fin ("vacationgold.in");

	fin >> n >> m >> k >> q;
	
	for(int i = 0; i < m; i++){
		ll a,b,c; fin >> a >> b >> c;
		adj[a].push_back({b,c});
	}
	
	for(int i = 1; i <= n; i++) numer[i] = -1;
	
	for(int i = 1; i <= k; i++){
		ll x; fin >> x;
		numer[x] = i;
		special.push_back(x);
	}
	
	for(int i = 1; i <= 201; i++)
		for(int j = 1; j < SIZE; j++)
			dis[i][j] = LINF;
			
	for(auto it : special){
		int nr1 = numer[it];
		priority_queue<pair<ll,int> > q;
		q.push({0,it});
		
		while(!q.empty()){
			auto iter = q.top();
			q.pop();
			int ver = iter.ND;
			ll odl = -iter.ST;
			if(odl > dis[nr1][ver]) continue;
			dis[nr1][ver] = odl;
			for(auto it2 : adj[ver]){
				if(dis[nr1][it2.ST] > odl + it2.ND){
					dis[nr1][it2.ST] = odl + it2.ND;
					q.push({-(odl + it2.ND),it2.ST});
				}
			}
		}
	}
	
	int res = 0;
	ll res2 = 0;
	
	while(q--){
		int a,b; fin >> a >> b;

		if(numer[a] != -1){
			if(dis[numer[a]][b] < (ll)1e18){
				res++;
				res2 += dis[numer[a]][b];
			}
		} else {
			long long minn = (ll)1e18;
			for(auto it : adj[a]){
				minn = min(minn,dis[numer[it.ST]][b] + it.ND);
			}			
			if(minn < (ll)1e18){
				res++;
				res2 += minn;
			}
		}
		
	}
	
	fout << res << "\n";
	fout << res2 << "\n";
	
    return 0;
}
