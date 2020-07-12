#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 4e4 + 1;
const int BLOCK = 201;

int n,q,nob;
int tab[SIZE];
ll dp[BLOCK][2];
ll blo[BLOCK][2][2];

void updateblock(int x){
	vector<vector<ll> > minidp(BLOCK,vector<ll>(2));
	minidp[0][0] = 0;
	minidp[0][1] = 0;
	int indeks = 0;
	for(int i = 1; i + x * BLOCK < min(n,(x+1)*BLOCK); i++){
		indeks = i;
		minidp[i][0] = max(minidp[i-1][0],minidp[i-1][1]);
		minidp[i][1] = minidp[i-1][0] + tab[i+x*BLOCK];
	}
	blo[x][0][0] = minidp[indeks][0];
	blo[x][0][1] = minidp[indeks][1];
	// part 2
	minidp[0][0] = 0;
	minidp[0][1] = tab[x*BLOCK];
	for(int i = 1; i + x * BLOCK < min(n,(x+1)*BLOCK); i++){
		minidp[i][0] = max(minidp[i-1][0],minidp[i-1][1]);
		minidp[i][1] = minidp[i-1][0] + tab[i+x*BLOCK];
	}
	blo[x][1][0] = minidp[indeks][0];
	blo[x][1][1] = minidp[indeks][1];
}

void updatedp(){
	dp[0][1] = max({blo[0][0][1],blo[0][1][1]});
	dp[0][0] = max({blo[0][0][0],blo[0][1][0]});
	for(int i = 1; i <= nob; i++){
		dp[i][0] = max(blo[i][0][0] + max(dp[i-1][0],dp[i-1][1]), blo[i][1][0] + dp[i-1][0]);
		dp[i][1] = max(blo[i][0][1] + max(dp[i-1][0],dp[i-1][1]), blo[i][1][1] + dp[i-1][0]);
	}
}

int main() {

	ofstream fout ("optmilk.out");
	ifstream fin ("optmilk.in");

	fin >> n >> q;
	
	nob = (n-1)/BLOCK;
	
	for(int i = 0; i < n; i++) fin >> tab[i];
	
	for(int i = 0; i <= nob; i++) updateblock(i);

	ll res = 0;

	//cout << blo[0][0][0] << " " << blo[0][0][1] << " " << blo[0][1][0] << " " << blo[0][1][1] << endl;

	while(q--){
		int x,y; fin >> x >> y;
		x--;
		tab[x] = y;
		updateblock(x/BLOCK);
		updatedp();
		res += max(dp[nob][0],dp[nob][1]);
	}
	
	fout << res;
	
    return 0;
}
