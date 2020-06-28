#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

const int SIZE = 51;
const int MAX = 1 << 16;
const int DX[] = {-1,0,0,1};
const int DY[] = {0,1,-1,0};

int n,m,cur;
char tab[SIZE][SIZE];
int id[SIZE][SIZE];
int adj[20][20];

pair<int,int> represent[20];

int diss[SIZE][SIZE];
int odl[16][MAX];

bool ok(int x, int y){
	return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y){
	id[x][y] = cur;
	for(int i = 0; i < 4; i++){
		int tmpx = x + DX[i];
		int tmpy = y + DY[i];
		if(ok(tmpx,tmpy) && tab[tmpx][tmpy] == 'X' && id[tmpx][tmpy] == 0) dfs(tmpx,tmpy);
	}
}

void cleardis(){
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			diss[i][j] = 1e9;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("island.out");
	ifstream fin ("island.in");

	fin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			fin >> tab[i][j];
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(tab[i][j] == 'X' && id[i][j] == 0){
				cur++;
				represent[cur] = {i,j};
				dfs(i,j);
			}
		}
	}
	
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 20; j++)
			adj[i][j] = 1e9;
			
	for(int i = 1; i <= cur; i++){
	
		cleardis();
		queue<pair<int,int> > q;
		q.push(represent[i]);
		diss[represent[i].ST][represent[i].ND] = 0;

		while(!q.empty()){

			auto it = q.front();
			q.pop();
			
			for(int j = 0; j < 4; j++){
				int tmpx = it.ST + DX[j];
				int tmpy = it.ND + DY[j];

				if(!ok(tmpx,tmpy) || tab[tmpx][tmpy] == '.') continue;

				if(tab[tmpx][tmpy] == 'X'){			
					int ind = id[tmpx][tmpy];
					if(ind == i && diss[tmpx][tmpy] == 1e9){
						diss[tmpx][tmpy] = 0;
						q.push({tmpx,tmpy});
					} else if(ind != i){
						adj[i][ind] = min(adj[i][ind],diss[it.ST][it.ND]);
						adj[ind][i] = min(adj[ind][i],diss[it.ST][it.ND]);
					}
				} else if(diss[it.ST][it.ND] + 1 < diss[tmpx][tmpy]){
					diss[tmpx][tmpy] = diss[it.ST][it.ND] + 1;
					q.push({tmpx,tmpy});
				}
			}
		}
	}
	
	int res = 1e9;
	priority_queue<pair<int,pair<int,int> > > q;

	for(int i = 1; i <= 15; i++)
		for(int j = 0; j < MAX; j++)
			odl[i][j] = 1e9;

	for(int i = 1; i <= cur; i++){
		q.push({0,{i,(1 << (i-1))}});
		odl[i][1 << (i-1)] = 0;
	}
	while(!q.empty()){
		auto it = q.top();
		q.pop();
		int x = it.ND.ST;
		int maska = it.ND.ND;
		int odle = -it.ST;
	
		if(odle > odl[x][maska] || maska == (1 << cur) - 1) continue;
			
		for(int j = 1; j <= cur; j++){
			if(j == x || adj[x][j] == 1e9) continue;
			int maska2 = (maska | (1 << (j-1)));
			int odl2 = odle + adj[x][j];
			if(odl[j][maska2] > odl2){
				odl[j][maska2] = odl2;
				q.push({-odl2,{j,maska2}});
			}
		}
	}
	for(int j = 1; j <= cur; j++)
		res = min(res,odl[j][(1 << cur) - 1]);
	
    fout << res;
     
    return 0;
}
