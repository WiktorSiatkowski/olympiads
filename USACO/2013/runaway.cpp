#include<bits/stdc++.h>

using namespace std;

const int SIZE = 2e5 + 5;
const int LOGN = 20;

int answer[SIZE], parent[SIZE][LOGN], depth[SIZE];
pair<int,int> toadd[SIZE];
long long dis[SIZE][LOGN];
vector<int> adj[SIZE];

int n;
long long l;

void dfs(int v, int prev){
	for(auto it : adj[v]){
		if(it == prev) continue;
		depth[it] = depth[v] + 1;
		dfs(it,v);	
	}
}

void dfs2(int v, int prev){
	answer[v] = -toadd[v].second + toadd[v].first;
	for(auto it : adj[v]){
		if(it == prev) continue;
		dfs2(it,v);		
		answer[v] += answer[it];
	}
}

int getparent(int x, int y){
	if(y == -1) return x;
	int tmp = LOGN - 1;
	int goaldepth = max(depth[x] - y - 1,0);
	while(tmp >= 0){
		if(depth[parent[x][tmp]] >= goaldepth) x = parent[x][tmp];
		tmp--;
	}
	if(depth[x] != goaldepth) assert(false);
	return x;
}

long long odl(int x, int y){
	if(y == -1) return 0;
	int tmp = LOGN - 1;
	long long result = 0;
	int goaldepth = max(depth[x] - y - 1,0);
	while(tmp >= 0){
		if(depth[parent[x][tmp]] >= goaldepth){
			result += dis[x][tmp];		
			x = parent[x][tmp];
		}
		tmp--;
	}
	if(depth[x] != goaldepth) assert(false);
	return result;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("runaway.out");
	ifstream fin ("runaway.in");
	
	fin >> n >> l;
    
    parent[1][0] = 1;
    for(int i = 2; i <= n; i++){
    	long long a,b; fin >> a >> b;
    	parent[i][0] = a;
    	dis[i][0] = b;
    	adj[a].push_back(i);
    	adj[i].push_back(a);
    }
    
    for(int i = 1; i < LOGN; i++)
    	for(int j = 1; j <= n; j++){
    		dis[j][i] = dis[j][i-1] + dis[parent[j][i-1]][i-1];
    		parent[j][i] = parent[parent[j][i-1]][i-1];
    	}

	dfs(1,-1);

	for(int i = 1; i <= n; i++){
		int ll = -1, rr = depth[i];
		while(ll + 1 < rr){
			int mid = (ll+rr)/2;
			if(odl(i,mid) <= l) ll = mid;
			else rr = mid;
		}
		int ver = getparent(i,ll);
		if(ver != 1) toadd[parent[ver][0]].second++;
		toadd[i].first++;
	}
    
    dfs2(1,-1);
    
	for(int i = 1; i <= n; i++)
		fout << answer[i] << "\n";
    
    return 0;
}
