#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
const int MAX = 1 << 19;
int tab[SIZE], tr[2*MAX], pos[SIZE];
int n,k;
void update(int x){
	x += MAX;
	tr[x]++;
	while(x /= 2) tr[x]++;
}

int query(int x, int y){
	if(x >= y) return 0;
	int ans = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) ans += tr[x++];
		if(y&1) ans += tr[--y];
	}
	return ans;
}

int main() {
	ofstream fout ("friendcross.out");
	ifstream fin ("friendcross.in");

	fin >> n >> k;

	for(int i = 1; i <= n; i++) fin >> tab[i];
	
	for(int i = 1; i <= n; i++){
		int x; fin >> x;
		pos[x] = i;
	}
	
	for(int i = 1; i <= n; i++) tab[i] = pos[tab[i]];

	ll res = 0;

	for(int i = 1; i <= n; i++){
		res += query(tab[i] + k + 1, MAX);
		update(tab[i]);			
	}
	
	fout << res;

    return 0;
}
