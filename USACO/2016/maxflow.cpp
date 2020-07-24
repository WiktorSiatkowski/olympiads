#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 5e4 + 4;
const int LOGN = 16;
int n,k,timer;
vector<int> adj[SIZE];
int pre[SIZE],subtree[SIZE],parent[SIZE][LOGN], dp[SIZE];

bool child(int u, int v){
	return pre[v] >= pre[u] && pre[v] < pre[u] + subtree[u];
}

int lca(int u, int v){
	if(child(u,v)) return u;
	if(child(v,u)) return v;
	for(int i = LOGN - 1; i >= 0; i--)
		if(!child(parent[u][i],v)) u = parent[u][i];
	return parent[u][0];
}

void dfs(int v, int prev){
	parent[v][0] = prev;
	subtree[v] = 1;
	pre[v] = ++timer;
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs(it,v);
		subtree[v] += subtree[it];
	}
}

void dfs2(int v, int prev){
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs2(it,v);
		dp[v] += dp[it];
	}
}


int main() {
	ofstream fout ("maxflow.out");
	ifstream fin ("maxflow.in");

	fin >> n >> k;
	for(int i = 1; i < n; i++){
		int a,b; fin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	dfs(1,-1);
	parent[1][0] = 1;
	
	for(int i = 1; i < LOGN; i++)
		for(int j = 1; j <= n; j++)
			parent[j][i] = parent[parent[j][i-1]][i-1];
	
	while(k--){
		int a,b; fin >> a >> b;
		dp[a]++;
		dp[b]++;
		int x = lca(a,b);
		dp[x]--;
		if(x != 1) dp[parent[x][0]]--;
	}
	
	dfs2(1,-1);
	
	int res = 0;
	
	for(int i = 1; i <= n; i++) res = max(res,dp[i]);
	
	fout << res;

    return 0;
}
