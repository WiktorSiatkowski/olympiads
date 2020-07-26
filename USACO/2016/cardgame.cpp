#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int n;

int main() {
	ofstream fout ("cardgame.out");
	ifstream fin ("cardgame.in");

	fin >> n;

	vector<bool> vis(2*n+1);
	vector<int> tab(n+1);
	for(int i = 1; i <= n; i++){
		fin >> tab[i];
		vis[tab[i]] = 1;
	}	
	
	set<int> secior;
	for(int i = 1; i <= 2 * n; i++){
		if(!vis[i]) secior.insert(i);
	}
	
	vector<int> pref(n+2), suf(n+2);
	for(int i = 1; i <= n; i++){
		pref[i] = pref[i-1];
		auto it = secior.upper_bound(tab[i]);
		if(it == secior.end()) continue;
		secior.erase(it);
		pref[i]++;
	}
	
	secior.clear();
	
	for(int i = 1; i <= 2 * n; i++){
		if(!vis[i]) secior.insert(i);
	}
	
	for(int i = n; i >= 1; i--){
		suf[i] = suf[i+1];
		auto it = secior.upper_bound(tab[i]);
		if(it == secior.begin()) continue;
		--it;
		secior.erase(it);
		suf[i]++;
	}
	
	int res = 0;
	
	for(int i = 0; i <= n; i++) res = max(res,pref[i] + suf[i+1]);
	
	fout << res;
	
    return 0;
}
