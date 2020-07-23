#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 752;
const int MOD = 1e9 + 7;
const int MAX = 1 << 10;
int n,m,k;

int tab[SIZE][SIZE];
int ile[SIZE*SIZE];
int indeks[SIZE*SIZE];
vector<int> duze;
vector<pair<int,int> > store[SIZE*SIZE];
int drzewa[1800][2*MAX];
int tr[2*MAX];

inline int add(int a, int b){
	int res = a + b;
	if(res < 0) res += MOD;
	while(res >= MOD) res -= MOD;
	return res;
}

void upd(int x, int y, int v){
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) {
			tr[x] = add(tr[x],v);
			x++;
		}
		if(y&1) {
			--y;
			tr[y] = add(tr[y],v);
		}
	}
}

int qr(int x){
	x += MAX;
	int res = tr[x];
	while(x /= 2)
		res = add(res,tr[x]);
	return res;
}

void update(int nr, int x, int val){
	x += MAX;
	drzewa[nr][x] = add(drzewa[nr][x],val);
	while(x /= 2){
		drzewa[nr][x] = add(drzewa[nr][x],val);
	}
}

int query(int nr, int x, int y){
	int res = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res = add(res,drzewa[nr][x++]);
		if(y&1) res = add(res,drzewa[nr][--y]);
	}
	return res;
}

int main() {
	ofstream fout ("hopscotch.out");
	ifstream fin ("hopscotch.in");

	fin >> n >> m >> k;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			fin >> tab[i][j];
			ile[tab[i][j]]++;
		}
	}
	
	for(int i = 1; i <= k; i++){
		if(ile[i] > 350){
			indeks[i] = duze.size();
			duze.push_back(i);
		} else {
			indeks[i] = -1;
		}
	}	
	
	if(indeks[tab[1][1]] == -1){
		store[tab[1][1]].push_back({1,1});
	} else {
		update(indeks[tab[1][1]],1,1);
	}
	
	upd(2,MAX,1);
	
	for(int i = 2; i <= m; i++){
		vector<int> rozwy(n+1);
		for(int j = 2; j <= n; j++){
			int tmp = qr(j);
			if(indeks[tab[j][i]] == -1){
				int sum = 0;
				for(auto it : store[tab[j][i]])
					if(it.ST < j) sum = add(sum,it.ND);
				rozwy[j] = add(tmp,-sum);
			} else {
				rozwy[j] = add(tmp,-query(indeks[tab[j][i]],1,j));
			}
		}

		if(i == m){
			fout << rozwy[n];
			return 0;
		}
		for(int j = 2; j <= n; j++){
			upd(j+1,MAX,rozwy[j]);
			if(indeks[tab[j][i]] == -1){
				store[tab[j][i]].push_back({j,rozwy[j]});
			} else {
				update(indeks[tab[j][i]],j,rozwy[j]);
			}
		}
	}
	
	
    return 0;
}
