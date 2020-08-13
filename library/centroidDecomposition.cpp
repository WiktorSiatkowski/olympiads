#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;
const int SIZE = 1e5 + 20;

int n,k,centroid,res,treesize;
vector<pair<int,int> > adj[SIZE], toAdd;
bool dead[SIZE];
int subtree[SIZE],maxOdl[SIZE];

void dfs1(int v, int prev){
	treesize++;
	subtree[v] = 1;
	for(auto it : adj[v]){
		if(dead[it.ST] || it.ST == prev) continue;
		dfs1(it.ST,v);
		subtree[v] += subtree[it.ST];
	}
}

void dfs2(int v, int prev, int x){
	int maks = x - subtree[v];
	for(auto it : adj[v]){
		if(it.ST == prev || dead[it.ST]) continue;
		dfs2(it.ST,v,x);
		maks = max(maks,subtree[it.ST]);	
	}
	if(maks <= x / 2) centroid = v;
}

void dfs3(int v, int prev, int dep, int sum){
	if(dep <= k){
		res = max(res,sum + maxOdl[k - dep]);
		toAdd.push_back({dep,sum});
	}
	for(auto it : adj[v]){
		if(dead[it.ST] || it.ST == prev) continue;
		dfs3(it.ST,v,dep+1,sum + it.ND);
		if(v == centroid){
			for(auto it2 : toAdd) maxOdl[it2.ST] = max(maxOdl[it2.ST],it2.ND);
			toAdd.clear();
		}	
	}
}

void decompose(int v){
	treesize = 0;
	dfs1(v,-1);
	for(int i = 0; i <= treesize; i++) maxOdl[i] = 0;
	dfs2(v,-1,subtree[v]);
	dfs3(centroid,-1,0,0);
	dead[centroid] = 1;
	for(auto it : adj[centroid]) if(!dead[it.first]) decompose(it.first);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> k; k--;
	for(int i = 1; i < n; i++){
		int x,y,z; cin >> x >> y >> z;
		adj[x].push_back({y,z});
		adj[y].push_back({x,z});
	}

	decompose(1);

	cout << res;
}
