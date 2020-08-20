#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e6 + 6;
ld tab[SIZE];
ld pref[SIZE];
ld ans;
int n;

int main() {
	ofstream fout ("cowdate.out");
	ifstream fin ("cowdate.in");

	fin >> n;
	for(int i = 1; i <= n; i++){
		ld x; fin >> x;
		tab[i] = x / 1e6;
		ans = max(ans,tab[i]);
	}

	int l = 1, r = 1;
	ld w = tab[1];
	ld p = (1 - tab[1]);
	while(r < n){
		r++;
		w = w * (1 - tab[r]) + tab[r] * p;
		p *= (1 - tab[r]);
		ld wprim = (w - tab[l] * (p/(1-tab[l]))) / (1 - tab[l]);
		while(l != r && wprim > w){
			p /= (1 - tab[l]);
			w -= tab[l] * p; 
			w /= (1 - tab[l]);
			ans = max(ans,w);
			l++;
			if(l != r) wprim = (w - tab[l] * (p/(1-tab[l]))) / (1 - tab[l]);
		}
		ans = max(ans,w);
	} 
	
	while(l < n){
		p /= (1 - tab[l]);
		w -= tab[l] * p; 
		w /= (1 - tab[l]);
		l++;
		ans = max(ans,w);
	}
	
	fout << (ll)(ans * 1e6);	


	return 0;
}
