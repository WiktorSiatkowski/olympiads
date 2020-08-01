#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
const int MAX = 1 << 18;

int n,timer;
vector<int> adj[SIZE];
vector<pair<int,int>> segs;
int ans[SIZE],pre[SIZE],val[SIZE],tr[2*MAX],subtree[SIZE];

void update(int x, int val){
	x += MAX;
	tr[x] += val;
	while(x /= 2)
		tr[x] += val;
}

int query(int x, int y){
	int res = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res += tr[x++];
		if(y&1) res += tr[--y];
	}
	return res;
}

void dfs(int v, int prev){
	subtree[v] = 1;
	pre[v] = ++timer;
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs(it,v);
		subtree[v] += subtree[it];
	}
}

int main() {
	ofstream fout ("promote.out");
	ifstream fin ("promote.in");

	fin >> n;
	for(int i = 1; i <= n; i++)
		fin >> val[i];
		
	for(int i = 2; i <= n; i++){
		int x; fin >> x;
		adj[i].push_back(x);
		adj[x].push_back(i);
	}
	
	dfs(1,-1);
	
	for(int i = 1; i <= n; i++){
		segs.push_back({val[i],i});
	}	
	
	sort(segs.rbegin(),segs.rend());
	
	for(auto it : segs){
		ans[it.ND] = query(pre[it.ND],pre[it.ND] + subtree[it.ND]);
		update(pre[it.ND],1); 
	}

	for(int i = 1; i <= n; i++){
		fout << ans[i] << "\n";
	}
	
    return 0;
    
}
