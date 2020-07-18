#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
int n,t;
ll lis[SIZE];

int main() {
	ofstream fout ("cowjog.out");
	ifstream fin ("cowjog.in");

	fin >> n >> t;
	vector<ll> tab(n);
	for(int i = 0; i < n; i++){
		ll x,y; fin >> x >> y;
		tab[i] = -(x + y * t);
	} 

	for(int i = 0; i < SIZE; i++) lis[i] = (ll)1e18;
	
	for(int i = 0; i < n; i++){
		int l = -1, r = SIZE-1;
		while(l + 1 < r){
			int mid = (l+r)/2;
			if(lis[mid] > tab[i]) r = mid;
			else l = mid;
		}
		lis[r] = tab[i];
	}
	
	for(int i = 0; i < SIZE; i++){
		if(lis[i] == (ll)1e18){
			fout << i << "\n";
			return 0;
		}	
	}




















    return 0;
}
