#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;

ld tab[SIZE];
ll n,k;
ld ans = 0;

bool check(ld x){
	ll used = 0;
	for(int i = 1; i <= n; i++){
		if(used > k) break;
		used += (ll)(-0.5 + sqrtl(0.25 + tab[i]/(x*x)));
	}
	return (used <= k);
}

void xd(ld x){
	for(int i = 1; i <= n; i++){
		ld tmp = (ll)(-0.5 + sqrtl(0.25 + tab[i]/(x*x))) + 1;
		ans += (ld)tab[i] / tmp;
	}
}

int main() {
	ofstream fout ("tallbarn.out");
	ifstream fin ("tallbarn.in");

	fin >> n >> k;
	
	k -= n;
	
	for(int i = 1; i <= n; i++) fin >> tab[i];
	
	ld l = 0, r = 1e12 / 2;
	while(l + 1e-10 < r){
		ld mid = (l+r)/(ld)2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	
	xd(r);
	
	fout << (ll)(ans + 0.5);

    return 0;
}
