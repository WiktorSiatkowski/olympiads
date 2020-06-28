#include<bits/stdc++.h>
using namespace std;
const int SIZE = 1e5 + 7;
const int MAX = 1 << 20	;
vector<int> adj[SIZE];
vector<vector<int> > heavyEdg;
map<int, pair<int,int> > mapa;
bool isHeavy[SIZE],bilans[SIZE];
int subtree[SIZE],in[SIZE],parent[SIZE][20],delta[2*MAX],drzewo[2*MAX];
int timer = 0, posInTree = 0;

void subtreeSizes(int v){
	subtree[v] = 1;
	in[v] = timer; timer++;
	for(auto it : adj[v])
		if(it != parent[v][0]){
			parent[it][0] = v;
			subtreeSizes(it);
			subtree[v] += subtree[it];
		}
}

void decompose(int v){
	int HAF = -1;
	for(auto it : adj[v])
		if(it != parent[v][0] && subtree[it] * 2 > subtree[v])
			HAF = it;
	
	if(HAF != -1){
		if(!isHeavy[parent[HAF][0]]){
			vector<int> x;
			heavyEdg.push_back(x);	
		}
		mapa[HAF] = {heavyEdg.size()-1,posInTree};
		posInTree++;
		heavyEdg.back().push_back(HAF);
		isHeavy[HAF] = 1;
		decompose(HAF);
	}
	for(auto it : adj[v])
		if(it != parent[v][0] && it != HAF)
			decompose(it);
}

bool child(int u, int v) { return (in[v] >= in[u] && in[v] < in[u] + subtree[u]); }

int lca(int u, int v){
	if(child(u,v)) return u; if(child(v,u)) return v;
	int r = 19;
	while(r >= 0){
		if(child(parent[u][r],v)) r--;
		else u = parent[u][r];
	}
	return parent[u][0];
}

void lazy(int u, int lo, int mid, int hi){
	if(delta[u]!=-1){
		delta[2*u] = delta[u];
		delta[2*u+1] = delta[u];
		drzewo[2*u] = (mid-lo) * delta[u];
		drzewo[2*u+1] = (hi - mid) * delta[u];
		delta[u] = -1;
	}
}

void update(int a,int b, int u, int lo, int hi, int v){
	if(a==lo && b==hi){
		delta[u] = v;
		drzewo[u] = (hi - lo) * delta[u];
		return;
	}
	if(b <= a) return;
	int mid = (lo+hi)/2;
	lazy(u,lo,mid,hi);
	update(a,min(b,mid),2*u,lo,mid,v);
	update(max(a,mid),b,2*u+1,mid,hi,v);
	drzewo[u] = drzewo[2*u] + drzewo[2*u+1];
}

int query(int a, int b, int u, int lo, int hi){
	if(a==lo && b==hi)
		return drzewo[u];
	if(b <= a) return 0;
	int mid = (lo+hi)/2;
	lazy(u,lo,mid,hi);
	int l = query(a,min(b,mid),2*u,lo,mid);
	int r = query(max(a,mid),b,2*u+1,mid,hi);
	return l + r;
}

int rozbicie(int a, int b, int v){
	int res = 0;
	int LCA = lca(a,b);
	while(a != LCA){
		if(isHeavy[a]){
			pair<int,int> mapaA = mapa[a];
			if(isHeavy[LCA] && mapaA.first == mapa[LCA].first){
				res += query(mapa[LCA].second+1,mapaA.second+1,1,0,MAX);
				if(v != 69) update(mapa[LCA].second+1,mapaA.second+1,1,0,MAX,v);
				a = LCA;
			} else {
				res += query(mapa[heavyEdg[mapaA.first][0]].second,mapaA.second+1,1,0,MAX);
				if(v != 69) update(mapa[heavyEdg[mapaA.first][0]].second,mapaA.second+1,1,0,MAX,v);
				a = parent[heavyEdg[mapaA.first][0]][0];
			}
		} else {
			res += bilans[a];
			if(v != 69) bilans[a] = v;
			a = parent[a][0];	
		}
	}
	while(b != LCA){
		if(isHeavy[b]){
			pair<int,int> mapaA = mapa[b];
			if(isHeavy[LCA] && mapaA.first == mapa[LCA].first){
				res += query(mapa[LCA].second+1,mapaA.second+1,1,0,MAX);
				if(v != 69) update(mapa[LCA].second+1,mapaA.second+1,1,0,MAX,v);
				b = LCA;
			} else {
				res += query(mapa[heavyEdg[mapaA.first][0]].second,mapaA.second+1,1,0,MAX);
				if(v != 69) update(mapa[heavyEdg[mapaA.first][0]].second,mapaA.second+1,1,0,MAX,v);
				b = parent[heavyEdg[mapaA.first][0]][0];
			}
		} else {
			res += bilans[b];
			if(v != 69) bilans[b] = v;
			b = parent[b][0];	
		}
	}
	return res;
}

int main(){
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	int n,q; cin >> n >> q;
	for(int i = 1; i < n; i++){
		int a,b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	parent[1][0] = 1;
	subtreeSizes(1);
	for(int i = 1; i < 20; i++) 
		for(int j = 1; j <= n; j++) parent[j][i] = parent[parent[j][i-1]][i-1];
	for(int i = 1; i < 2 * MAX; i++) delta[i] = -1, drzewo[i] = 0;
	decompose(1);
	
	while(q--){
		int t,a,b; cin >> t >> a >> b;
		int val = (t == 3 ? 69 : (t == 2 ? 0 : 1));
		int res = rozbicie(a,b,val);
		if(val == 69) cout << res << "\n";
	}
}
