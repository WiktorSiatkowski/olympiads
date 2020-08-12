#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
const int MAX = 1 << 19;
int tr[2*MAX];

void update(int x, int v){
	x += MAX;
	tr[x] = max(tr[x],v);
	while(x /= 2)
		tr[x] = max(tr[x],v);
}

int query(int l, int r){
	int res = 0;
	for(l += MAX, r += MAX; l < r; l >>= 1, r >>= 1){
		if(l&1) res = max(res,tr[l++]);
		if(r&1) res = max(res,tr[--r]);
	}
	return res;
}

int main() {
	ofstream fout ("nocross.out");
	ifstream fin ("nocross.in");

	int n; fin >> n;
	vector<int> dp(n+2), tab1(n+1), tab2(n+1), pos1(n+1), pos2(n+1);
	
	for(int i = 1; i <= n; i++){
		fin >> tab1[i];
		pos1[tab1[i]] = i;
	}
	
	for(int i = 1; i <= n; i++){
		fin >> tab2[i];
		pos2[tab2[i]] = i;
	}
	
	for(int i = 1; i <= n; i++){
		vector<int> tmpos;
		for(int j = max(1,tab1[i] - 4); j <= min(n,tab1[i] + 4); j++) tmpos.push_back(pos2[j]);
		sort(tmpos.rbegin(),tmpos.rend());
		for(auto it : tmpos)
			update(it,query(1,it) + 1);
	}
	
	fout << query(1,n+1);
		
    return 0;
}
