#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
const int MAX = 1 << 18;
int n;

ll res = 1e18;
ll tmpres = 0;

int tab1[SIZE],tab2[SIZE],pos[SIZE],liczinw[SIZE],tab3[SIZE];
ll tr[2*MAX];

void update(int x, ll v){
	x += MAX;
	tr[x] += v;
	while(x /= 2){
		tr[x] += v;
	}
}

ll query(int x, int y){
	ll ans = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) ans += tr[x++];
		if(y&1) ans += tr[--y];
	}
	return ans;
}

int main() {
	ofstream fout ("mincross.out");
	ifstream fin ("mincross.in");

	fin >> n;
	for(int i = 1; i <= n; i++) fin >> tab1[i];
	for(int i = 1; i <= n; i++) fin >> tab2[i];
	
	for(int i = 1; i <= n; i++) tab3[i] = tab1[i];
	
	for(int i = 1; i <= n; i++){
		pos[tab2[i]] = i;
	}	

	for(int i = 1; i <= n; i++){
		liczinw[i] = pos[tab1[i]];
	}
	
	for(int i = n; i >= 1; i--){
		update(liczinw[i],1);
		tmpres += query(0,liczinw[i]);
	}
	
	res = min(res,tmpres);
	
	for(int i = n; i >= 1; i--){
		tmpres -= query(liczinw[i]+1,MAX);
		tmpres += query(0,liczinw[i]);
		res = min(res,tmpres);
	}
	
	for(int i = 0; i < 2 * MAX; i++) tr[i] = 0;
	tmpres = 0;
	
	for(int i = 1; i <= n; i++) tab1[i] = tab2[i];
	for(int i = 1; i <= n; i++) tab2[i] = tab3[i];
	
	for(int i = 1; i <= n; i++){
		pos[tab2[i]] = i;
	}	

	for(int i = 1; i <= n; i++){
		liczinw[i] = pos[tab1[i]];
	}
	
	for(int i = n; i >= 1; i--){
		update(liczinw[i],1);
		tmpres += query(0,liczinw[i]);
	}
	
	res = min(res,tmpres);
	
	for(int i = n; i >= 1; i--){
		tmpres -= query(liczinw[i]+1,MAX);
		tmpres += query(0,liczinw[i]);
		res = min(res,tmpres);
	}
	
	fout << res << endl;
	

    return 0;
}
