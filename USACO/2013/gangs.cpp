#include<bits/stdc++.h>

using namespace std;

int n,m;
int poprzednia;

int sprawdz(vector<int> x, int ile, int co){
	multiset<int> secior;
	for(int i = 1; i < x.size(); i++) 
		if(x[i] != 0 && i != co)
			secior.insert(x[i]);
	
	if(ile % 2 == 1){
		if(!secior.empty()){
			auto it = secior.end();
			--it;
			if(*it > 1) secior.insert(*it - 1);
			secior.erase(it);
		} else {
			secior.insert(x[co]+1);
		}
	} else {
		if(co != -1) secior.insert(x[co]);
	}
	
	while(secior.size() > 1){
		auto it1 = secior.end();
		auto it2 = secior.end();
		it1--;
		it2--; it2--;
		int a = *it1;
		int b = *it2;
		secior.erase(it1);
		secior.erase(it2);
		if(a - 1 > 0) secior.insert(a-1);
		if(b - 1 > 0) secior.insert(b-1);
	}
	int res = -1;
	if(secior.size() == 0) res = 0;
	else res = *secior.begin();
	return x[0] - res;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("gangs.out");
	ifstream fin ("gangs.in");

	fin >> n >> m;
	vector<int> tab(m);
	for(int i = 0; i < m; i++) fin >> tab[i];
	
	int ans = sprawdz(tab,0,-1);
	
	if(ans > 0){	 
		fout << "YES\n";
		fout << ans << "\n";
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(tab[j] == 0) continue;
				tab[j]--;
				if(sprawdz(tab,i+1,j) == ans){
					fout << j + 1 << "\n";
					break;
				}
				tab[j]++;
			}	
		}
		while(tab[0]){
			fout << 1 << "\n";
			tab[0]--;
		}
	} else {
		fout << "NO\n";
	}
    
    return 0;
}
