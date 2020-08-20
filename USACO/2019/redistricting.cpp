#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 3e5 + 5;
const int MAX = 1 << 19;
int n,k;
int dp[SIZE];
int pref[SIZE];
int tab[SIZE];
int trr[2*MAX];
multiset<int> tr[MAX];

void usun(int x, int v){
	tr[x].erase(tr[x].find(v));
	x += MAX;
	while(x /= 2){
		if(x * 2 >= MAX){
			trr[x] = 1e9;
			if(!tr[2*x - MAX].empty()){
				trr[x] = min(trr[x],*(tr[2*x - MAX].begin()));
			}
			if(!tr[2*x+1 - MAX].empty()){
				trr[x] = min(trr[x],*(tr[2*x+1-MAX].begin()));
			}
		} else {
			trr[x] = min(trr[2*x],trr[2*x+1]);		
		}
	}
}

void dodaj(int x, int v){
	tr[x].insert(v);
	x += MAX;
	while(x /= 2) trr[x] = min(trr[x],v);
}

int query(int x, int y){
	int ans = 1e9;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1){
			if(x >= MAX) ans = min(ans,*(tr[x++ - MAX].begin()));
			else ans = min(ans,trr[x++]);
		}
		if(y&1){
			if(y >= MAX) ans = min(ans,*(tr[--y - MAX].begin()));
			else ans = min(ans,trr[--y]);
		}
	}
	return ans;
}

vector<int> enumer;

int getind(int x){
	return lower_bound(enumer.begin(),enumer.end(),x) - enumer.begin();
}

int main() {
	ofstream fout ("redistricting.out");
	ifstream fin ("redistricting.in");

	fin >> n >> k;
	
	string s; fin >> s;
	
	for(int i = 1; i <= n; i++) {
		if(s[i-1] == 'H') tab[i] = 1;
		else tab[i] = -1;
		pref[i] = pref[i-1] + tab[i];
	}
	
	for(int i = 0; i < MAX; i++) tr[i].insert(1e9);
	for(int i = 0; i < MAX; i++) trr[i] = 1e9;
	
	for(int i = 0; i <= n; i++) enumer.push_back(pref[i]);
	
	sort(enumer.begin(),enumer.end());		
	dodaj(getind(0),0);
	for(int i = 1; i <= n; i++){
		if(i - k - 1 >= 0){
			int foo = getind(pref[i-k-1]);
			usun(foo,dp[i - k - 1]);
		}		
		int ind = getind(pref[i]);
		dp[i] = min(query(0,ind),query(ind,MAX)+1);
		dodaj(ind,dp[i]);
	}	
	
	fout << dp[n];



	return 0;
}
