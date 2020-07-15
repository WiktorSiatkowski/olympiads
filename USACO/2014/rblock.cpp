#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 300;
const ll LINF = (ll)1e18 + 1;

int n,m;
map<pair<int,int>,bool> forbidden;
vector<pair<int,ll> > adj[SIZE];
vector<ll> minpath;
ll dis[SIZE];
int from[SIZE];
ll jebacdisa = 0;
ll res = 0;

void update(){
	for(int i = 1; i <= n; i++) dis[i] = LINF;

	priority_queue<pair<ll,int> > q;
	q.push({0,1});
	
	while(!q.empty()){
		int ver = q.top().ND;
		ll odl = (-q.top().ST);
		q.pop();
		if(odl > dis[ver]) continue;
		dis[ver] = odl;
		for(auto it : adj[ver]){
			if(forbidden[make_pair(it.ST,ver)]){
				if(odl + 2 * it.ND < dis[it.ST]){
					from[it.ST] = ver;
					dis[it.ST] = odl + 2 * it.ND;
					q.push({-(odl + 2 * it.ND),it.ST});
				}
				continue;
			}
			if(odl + it.ND < dis[it.ST]){
				from[it.ST] = ver;
				dis[it.ST] = odl + it.ND;
				q.push({-(odl + it.ND),it.ST});
			}
		}
	}
	
	res = max(res,dis[n] - jebacdisa);
}

int main() {
	ofstream fout ("rblock.out");
	ifstream fin ("rblock.in");

	fin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int a,b,c; fin >> a >> b >> c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	
	for(int i = 1; i <= n; i++) dis[i] = LINF;

	priority_queue<pair<ll,int> > q;
	q.push({0,1});
	
	while(!q.empty()){
		int ver = q.top().ND;
		ll odl = (-q.top().ST);
		q.pop();
		if(odl > dis[ver]) continue;
		dis[ver] = odl;
		for(auto it : adj[ver])
			if(odl + it.ND < dis[it.ST]){
				from[it.ST] = ver;
				dis[it.ST] = odl + it.ND;
				q.push({-(odl + it.ND),it.ST});
			}
	}
	
	jebacdisa = dis[n];
	
	int tmp = n;
	while(tmp != 1){
		minpath.push_back(tmp);
		tmp = from[tmp];	
	}
	minpath.push_back(1);
	
	reverse(minpath.begin(),minpath.end());
	
	for(int i = 1; i < (int)minpath.size(); i++){
		forbidden.clear();
		int ver = minpath[i];
		forbidden[make_pair(ver,minpath[i-1])] = 1;
		forbidden[make_pair(minpath[i-1],ver)] = 1;
		update();
	}
	
	fout << res << "\n";
	
    return 0;
}
