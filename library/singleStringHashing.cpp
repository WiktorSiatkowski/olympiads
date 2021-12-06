#include<bits/stdc++.h>
using namespace std;

const long long MOD = 2147483647;
const long long BASE = 31;

int n,m,q;
string pattern,text;
long long patHash;
unordered_map<long long,int> mapa;

long long pot(int n){
	if(n == 0) return 1;
	if(n % 2) return (BASE * pot(n-1)) % MOD;
	return (pot(n/2) * pot(n/2))%MOD;
}

void patternHash(){
	for(int i = 0; i < n; i++){
		patHash *= BASE;
		patHash += pattern[i] - 'a' + 1;
		patHash %= MOD;
	}
}

void textHashes(){
	long long hash = 0;
	for(int i = 0; i < n - 1; i++){
		hash *= BASE;
		hash += text[i] - 'a' + 1;
		hash %= MOD;
	}
	for(int i = n-1; i < m; i++){
		hash *= BASE;
		hash += text[i] - 'a' + 1;
		hash %= MOD;
		mapa[hash]++;
		hash -= pot(n-1) * (text[i-n+1] - 'a' + 1);
		hash %= MOD;
		while(hash < 0) hash += MOD;
	}
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> m >> q >> pattern >> text;

	patternHash();
	textHashes();

	while(q--){
		int x; cin >> x; char c; cin >> c;
		patHash -= pot(n-x) * (pattern[x-1] - 'a' + 1);
		patHash %= MOD;
		while(patHash < 0) patHash += MOD;
		pattern[x-1] = c;
		patHash += pot(n-x) * (pattern[x-1] - 'a' + 1);
		patHash %= MOD;
		while(patHash < 0) patHash += MOD;
		cout << mapa[patHash] << "\n";
	}

}
