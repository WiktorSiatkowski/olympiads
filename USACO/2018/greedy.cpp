#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
int n;
ll tab[SIZE],tab2[SIZE];
ll num[SIZE];

bool check(int x){
	for(int i = 1; i <= n; i++) num[i] = 0;
	for(int i = 1; i < x; i++){
		num[tab2[i]]++;
	}
	int total = 0;
	for(int i = 1; i <= n; i++){
		total += num[i];
		if(total >= i) {
			return false;
		}
	}
	return true;
}

int main() {
	//ofstream fout ("greedy.out");
	//ifstream fin ("greedy.in");

	cin >> n;
	for(int i = 1; i <= n; i++) cin >> tab[i], tab2[i] = n - tab[i];
	
	int lo = 1, hi = n + 1;
	while(lo + 1 < hi){
		int mid = (lo + hi)/2;
		if(check(mid)) hi = mid;
		else lo = mid;
	}
	
	cout << n - lo;












	return 0;
}
