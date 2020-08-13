#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
int n,centroid,treesize;
int subtree[SIZE],dead[SIZE],licz[SIZE*2],zwykle[2*SIZE],niezwykle[2*SIZE];
vector<pair<int,int> > adj[SIZE];
vector<int> toAddZwykle,toAddNiezwykle;
long long res = 0;

void dfs1(int v, int prev){
	treesize++;
	subtree[v] = 1;
	for(auto it : adj[v]){
		if(dead[it.ST] || it.ST == prev) continue;
		dfs1(it.ST,v);
		subtree[v] += subtree[it.ST];
	}
}

void dfs2(int v, int prev){
	int maks = treesize - subtree[v];
	for(auto it : adj[v]){
		if(dead[it.ST] || it.ST == prev) continue;
		maks = max(maks,subtree[it.ST]);
		dfs2(it.ST,v);
	}
	if(maks <= treesize / 2) centroid = v;
}

void dfs3(int v, int prev, int sum){
	//if(v == 6) for(int i = 0; i <= 2 * n; i++) cout << zwykle[i] << " " << niezwykle[i] << endl;
	if(sum == 0 && licz[treesize] >= 2) res++;
	if(licz[sum + treesize] > 0){
		if(sum == 0) res += max(zwykle[-sum + treesize] - 1,0);
		else res += zwykle[-sum + treesize];
		toAddNiezwykle.push_back(sum + treesize);
		toAddZwykle.push_back(sum + treesize);
	} else {
		res += niezwykle[-sum + treesize];
		toAddZwykle.push_back(sum + treesize);
	}
	//cout << v << " " << sum << endl;
	//cout << v << " " << res << " " << sum << " " << licz[-sum + treesize] << endl;
	licz[sum + treesize]++; 
	for(auto it : adj[v]){
		if(dead[it.ST] || it.ST == prev) continue;
		dfs3(it.ST,v,sum+it.ND);
		if(v == centroid){
			for(auto iter : toAddZwykle) zwykle[iter]++;
			for(auto iter : toAddNiezwykle) niezwykle[iter]++;
			toAddZwykle.clear();
			toAddNiezwykle.clear();
		}
	}
	licz[sum + treesize]--;
}

void decompose(int x){
	treesize = 0;
	dfs1(x,-1);
	for(int i = 0; i <= 2 * treesize; i++) licz[i] = 0, zwykle[i] = 0, niezwykle[i] = 0;	
	dfs2(x,-1);
	dfs3(centroid,-1,0);
	dead[centroid] = 1;
	//cout << endl << endl;
	for(auto it : adj[centroid]) if(!dead[it.ST]) decompose(it.ST);
}

int main() {
	ofstream fout ("yinyang.out");
	ifstream fin ("yinyang.in");
	
	fin >> n;
	for(int i = 1; i < n; i++){
		int a,b,c; fin >> a >> b >> c;
		c = 2 * c - 1;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	
	//cout << endl << endl;
	decompose(1);
	
	fout << res;
	
	return 0;
}
