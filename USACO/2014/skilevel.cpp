#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 502;
const int DX[] = {-1,0,0,1};
const int DY[] = {0,-1,1,0};

int n,m,t;
ll tab[SIZE][SIZE];
ll special[SIZE*SIZE];
ll parent[SIZE*SIZE];
ll rozmiar[SIZE*SIZE];
ll ilespecjalnych[SIZE*SIZE];

int findd(int x){
	if(parent[x] == x) return x;
	int tmp = findd(parent[x]);
	parent[x] = tmp;
	return tmp;
}

void unionn(int x, int y){
	rozmiar[findd(x)] += rozmiar[findd(y)];
	ilespecjalnych[findd(x)] += ilespecjalnych[findd(y)];
	parent[findd(y)] = findd(x);	
}

int nr(int x, int y){
	return x * m + y;
}

bool ok(int i, int j){
	return i >= 0 && i < n && j >= 0 && j < m;
}

struct edge{
	ll cost = 0, nr1 = 0, nr2 = 0;
	edge(ll a, ll b, ll c){
		cost = a, nr1 = b, nr2 = c;
	}
};

int main() {
	ofstream fout ("skilevel.out");
	ifstream fin ("skilevel.in");

	fin >> n >> m >> t;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fin >> tab[i][j];
			
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++){
			fin >> special[nr(i,j)];
			parent[nr(i,j)] = nr(i,j);
			rozmiar[nr(i,j)] = 1;	
			if(special[nr(i,j)]) ilespecjalnych[nr(i,j)] = 1;
		}
			
	vector<edge> differences;
			
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			for(int k = 0; k < 4; k++)
				if(ok(i+DX[k],j+DY[k]))
					differences.push_back(edge(abs(tab[i][j]-tab[i+DX[k]][j+DY[k]]),nr(i,j),nr(i+DX[k],j+DY[k])));
		
	sort(differences.begin(),differences.end(),[](edge a, edge b){
		return a.cost < b.cost;
	});

	ll res = 0;	
	
	for(auto it : differences){
		int a = findd(it.nr1);
		int b = findd(it.nr2);
		if(a == b) continue;
		unionn(a,b);
		if(rozmiar[a] >= t){
			res += ilespecjalnych[a] * it.cost;
			ilespecjalnych[a] = 0;
		}
	}
	
	fout << res;	

    return 0;
}
