#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 6969;

int n,m,spojne;
vector<pair<int,int> > edges;
map<pair<int,int>,bool> mam;
vector<int> adj[SIZE],adj2[SIZE],adj3[SIZE];
int low[SIZE], pre[SIZE], timer = 0, spojna[SIZE], rozmiar[SIZE], dp[SIZE], in2[SIZE], dp2[SIZE];
stack<int> st;

void dfs(int v){
	st.push(v);
	pre[v] = ++timer;
	low[v] = pre[v];
	for(auto it : adj[v]){
		if(pre[it] != 0){
			low[v] = min(low[v],low[it]);		
		} else {
			dfs(it);
			low[v] = min(low[v],low[it]);		
		}
	}
	if(low[v] == pre[v]){
		spojne++;
		while(st.top() != v){
			spojna[st.top()] = spojne;
			low[st.top()] = 1e9;
			st.pop();
			rozmiar[spojne]++;
		}	
		spojna[st.top()] = spojne;
		low[st.top()] = 1e9;
		st.pop();
		rozmiar[spojne]++;
	}
}

int main() {
	ofstream fout ("grass.out");
	ifstream fin ("grass.in");

	fin >> n >> m;
	for(int i = 0; i < m; i++){
		int a,b; fin >> a >> b;
		adj[a].push_back(b);
		edges.push_back({a,b});
	}
	
	for(int i = 1; i <= n; i++){
		if(pre[i] != 0) continue;
		dfs(i);
	}
	
	for(auto it : edges){
		int x = spojna[it.ST];
		int y = spojna[it.ND];
		if(x == y) continue;
		if(mam[{x,y}]) continue;
		mam[{x,y}] = 1;
		adj2[x].push_back(y);
		in2[y]++;
	}
	
	queue<int> q;

	for(int i = 1; i <= spojne; i++)
		if(in2[i] == 0 && i != spojna[1])
			q.push(i);
	
	while(!q.empty()){
		int x = q.front();
		q.pop();
		if(x == spojna[1]) continue;
		dp[x] = -1e6;
		for(auto it : adj2[x]){
			in2[it]--;
			if(in2[it] == 0)
				q.push(it);
		}
	}
	
	q.push(spojna[1]);
	
	while(!q.empty()){
		int x = q.front();
		q.pop();
		dp[x] += rozmiar[x];
		for(auto it : adj2[x]){
			in2[it]--;
			dp[it] = max(dp[it],dp[x]);
			if(in2[it] == 0)
				q.push(it);
		}
	}

	for(int i = 1; i <= spojne; i++)
		for(auto it : adj2[i]){
			adj3[it].push_back(i);
			in2[i]++;
		}	
	
	for(int i = 1; i <= spojne; i++)
		if(in2[i] == 0 && i != spojna[1])
			q.push(i);
	
	while(!q.empty()){
		int x = q.front();
		q.pop();
		if(x == spojna[1]) continue;
		dp2[x] = -1e6;
		for(auto it : adj3[x]){
			in2[it]--;
			if(in2[it] == 0)
				q.push(it);
		}
	}
	
	q.push(spojna[1]);
	
	while(!q.empty()){
		int x = q.front();
		q.pop();
		dp2[x] += rozmiar[x];
		for(auto it : adj3[x]){
			in2[it]--;
			dp2[it] = max(dp2[it],dp2[x]);
			if(in2[it] == 0)
				q.push(it);
		}
	}
	
	int res = rozmiar[spojna[1]];
	
	for(auto it : adj2[spojna[1]])
		res = max(res,rozmiar[spojna[1]] + rozmiar[it]);
	
	for(auto it : edges){
		int x = spojna[it.ST];
		int y = spojna[it.ND];
		if(x == y) continue;
		res = max(res,dp2[x] + dp[y] - rozmiar[spojna[1]]);
		res = max(res,dp2[y] + dp[x] - rozmiar[spojna[1]]);
	}
	
	fout << res;

    return 0;
}
