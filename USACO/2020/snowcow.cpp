#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const ll  SIZE = 1e5 + 5;
const ll  MAX = 1 << 19;

ll tr1[2*MAX],updt[2*MAX];
ll n,q,timer;
vector<ll> adj[SIZE];
ll pre[SIZE],subtree[SIZE];
vector<pair<ll,pair<ll,ll> > > queries;
vector<pair<ll,ll> > upd[SIZE];
vector<pair<ll,ll > > dousuniecia[SIZE];
bool skip[SIZE];

void update2(ll  a, ll  b, ll  u, ll lo, ll hi, ll v){
	if(a == lo && b == hi){
		tr1[u] += (hi-lo) * v;
		updt[u] += v;
		return;
	}
	if(b <= a) return;
	ll  mid = (lo+hi)/2;
	if(updt[u] != 0){
		updt[2*u] += updt[u];
		tr1[2*u] += (mid-lo) * updt[u];
		updt[2*u+1] += updt[u];
		tr1[2*u+1] += (hi-mid) * updt[u];
		tr1[u] = tr1[2*u] + tr1[2*u+1];
		updt[u] = 0;
	}
	update2(a,min(b,mid),2*u,lo,mid,v);
	update2(max(a,mid),b,2*u+1,mid,hi,v);
	tr1[u] = tr1[2*u] + tr1[2*u+1];
}

ll query2(ll  a, ll  b, ll  u, ll  lo, ll  hi){
	if(a == lo && b == hi){
		return tr1[u];	
	}
	if(b <= a) return 0;
	ll  mid = (lo+hi)/2;
	if(updt[u] != 0){
		updt[2*u] += updt[u];
		tr1[2*u] += (mid-lo) * updt[u];
		updt[2*u+1] += updt[u];
		tr1[2*u+1] += (hi-mid) * updt[u];
		tr1[u] = tr1[2*u] + tr1[2*u+1];
		updt[u] = 0;
	}
	ll l = query2(a,min(b,mid),2*u,lo,mid);
	ll r = query2(max(a,mid),b,2*u+1,mid,hi);
	return l + r;
}


void dfs(ll  v, ll  prev){
	pre[v] = ++timer;
	subtree[v] = 1;
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs(it,v);
		subtree[v] += subtree[it];
	}
}


int32_t main() {
	ofstream fout ("snowcow.out");
	ifstream fin ("snowcow.in");

	fin >> n >> q;
	for(ll  i = 1; i < n; i++){
		ll  x,y; fin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	dfs(1,-1);
	
	for(ll  i = 1; i <= q; i++){
		ll  t; fin >> t;
		if(t == 1){
			ll  v,x; fin >> v >> x;
			queries.push_back({t,{v,x}});
			upd[x].push_back({v,i});
		} else {
			ll  v; fin >> v;
			queries.push_back({t,{v,-1}});
		}
	}	
	
	for(ll  i = 1; i < SIZE; i++){
		if(upd[i].empty()) continue;
		vector<pair<pair<ll ,ll >,ll  > > tmp;
		for(auto it : upd[i]) tmp.push_back({{pre[it.ST],pre[it.ST] + subtree[it.ST] - 1},it.ND});
		sort(tmp.begin(),tmp.end(),[](pair<pair<ll ,ll >,ll > a, pair<pair<ll ,ll >,ll > b){
			if(a.ST.ND != b.ST.ND) return a.ST.ND < b.ST.ND;
			else return a.ST.ST > b.ST.ST;
		});
		stack<pair<pair<ll ,ll >,ll > > st;
		for(auto it : tmp){
			while(!st.empty() && it.ST.ST <= st.top().ST.ST){
				if(it.ND > st.top().ND){
					dousuniecia[it.ND].push_back(st.top().ST);
				} else {
					skip[st.top().ND] = 1;
				}
				st.pop();
			}
			st.push(it);
		}
	}
	
	ll  licz = 1;
	for(auto iter : queries){
		if(iter.ST == 1){
			if(skip[licz]) continue;
			for(auto it : dousuniecia[licz]){
				update2(it.ST,it.ND+1,1,0,MAX,-1);
			}
			update2(pre[iter.ND.ST],pre[iter.ND.ST] + subtree[iter.ND.ST],1,0,MAX,1);
		} else {
			ll secondPart = query2(pre[iter.ND.ST],pre[iter.ND.ST]+subtree[iter.ND.ST],1,0,MAX);
			fout << secondPart << "\n";
		}
		licz++;
	}
	
	return 0;
}
