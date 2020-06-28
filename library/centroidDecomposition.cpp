#include<bits/stdc++.h>
using namespace std;
const int SIZE = 1e5 + 20;

int n,k,centroid,res;
vector<pair<int,int> > adj[SIZE];
bool dead[SIZE];
int subtree[SIZE];
vector<pair<int,int> > toAdd;
int maxOdl[SIZE];

void subtreeSize(int v, int prev){
	subtree[v] = 1;
	for(auto it : adj[v]) 
		if(!dead[it.first] && it.first != prev){
			subtreeSize(it.first,v);
			subtree[v] += subtree[it.first];
		} 
}

void findCentroid(int v, int prev, int treeSize){
	int which = -1;
	for(auto it : adj[v])
		if(!dead[it.first] && it.first != prev && subtree[it.first] * 2 > treeSize) 
			which = it.first;
	if(which == -1)
		centroid = v;
	else
		findCentroid(which,v,treeSize);
}

void kPaths(int v, int prev, int level, int sum){
	if(level <= k) res = max(res,sum + maxOdl[k - level]);
	for(auto it : adj[v]){
		if(!dead[it.first] && it.first != prev) 
			kPaths(it.first,v,level+1,sum + it.second);
		if(v == centroid){
			for(auto it2 : toAdd) maxOdl[it2.first] = max(maxOdl[it2.first],it2.second);
			toAdd.clear();
		}	
	}
	if(level <= k) toAdd.push_back({level,sum});
}

void findFor(int v){
	for(int i = 0; i <= k; i++) maxOdl[i] = 0;
	centroid = -1;
	subtreeSize(v,-1);
	findCentroid(v,-1,subtree[v]);
	kPaths(centroid,-1,0,0);
	dead[centroid] = 1;
	for(auto it : adj[centroid]) if(!dead[it.first]) findFor(it.first);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> k; k--;
	for(int i = 1; i < n; i++){
		int x,y,z; cin >> x >> y >> z;
		adj[x].push_back({y,z});
		adj[y].push_back({x,z});
	}

	findFor(1);

	cout << res;

}
