#include<bits/stdc++.h>

#define ll long long
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define all(a) a.begin(),a.end()
#define turbo ios::sync_with_stdio(false)
#define VI vector<int>
#define VLL vector<ll>
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)

const int MOD = 1e9 + 7;

template<class T> inline T fastExp(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

using namespace std;

const int SIZE = 10e4 + 1;
const int LOGN = 16;

int jumpP[LOGN][SIZE],pre[SIZE],subtree[SIZE];
bool visited[SIZE];
VI adj[SIZE];

int vertices,edges,t;

bool child(int u, int v){
	return pre[u] >= pre[v] && pre[u] < pre[v] + subtree[v];
}

int lca(int u, int v){
	if(child(u,v)) return v;
	if(child(v,u)) return u;

	int i = u, j = LOGN - 1;
	while(j >= 0){
		if(child(v,jumpP[j][i]))
			j--;
		else
			i = jumpP[j][i];
	}

	return jumpP[0][i];
}

void dfs(int v, int prev){
	t++;
	subtree[v] = 1;
	pre[v] = t;
	for(auto i : adj[v])
		if(i != prev){
			jumpP[0][i] = v;
			dfs(i,v);
			subtree[v] += subtree[i];
		}
}

int main(){
	//turbo;
	int queries;
	cin >> vertices >> queries;
	FOR(i,1,vertices-1){
		int x,y; cin >> x >> y;
		adj[x].PB(y);
		adj[y].PB(x);
	}
	dfs(1,-1);

	jumpP[0][1] = 1;
	for(int i = 1; i < LOGN; i++)
		for(int j = 1; j < SIZE; j++)
			jumpP[i][j] = jumpP[i-1][jumpP[i-1][j]];

	while(queries--){
		int x,y; cin >> x >> y;
		cout << lca(x,y) << endl;
	}	

}
