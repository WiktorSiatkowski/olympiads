#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 9;
const long long MOD2 = 1e9 + 7;
const long long BASE = 31;
const long long BASE2 = 29;

int n,m,q;
string pattern,text;
pair<long long, long long> patHash;
map<pair<long long, long long>,int> mapa;

long long pot1(int n){
	if(n == 0) return 1;
	if(n % 2) return (BASE * pot1(n-1)) % MOD;
	return (pot1(n/2) * pot1(n/2))%MOD;
}

long long pot2(int n){
	if(n == 0) return 1;
	if(n % 2) return (BASE2 * pot2(n-1)) % MOD2;
	return (pot2(n/2) * pot2(n/2))%MOD2;
}

void patternHash(){
	for(int i = 0; i < n; i++){
		patHash.first *= BASE;
		patHash.first += pattern[i] - 'a' + 1;
		patHash.first %= MOD;
		patHash.second *= BASE2;
		patHash.second += pattern[i] - 'a' + 1;
		patHash.second %= MOD2;
	}
}

void textHashes(){
	pair<long long,long long> hash = make_pair(0,0);
	for(int i = 0; i < n - 1; i++){
		hash.first *= BASE;
		hash.first += text[i] - 'a' + 1;
		hash.first %= MOD;
		hash.second *= BASE2;
		hash.second += text[i] - 'a' + 1;
		hash.second %= MOD2;
	}
	for(int i = n-1; i < m; i++){
		hash.first *= BASE;
		hash.first += text[i] - 'a' + 1;
		hash.first %= MOD;
		hash.second *= BASE2;
		hash.second += text[i] - 'a' + 1;
		hash.second %= MOD2;
		mapa[hash]++;
		//cout << hash.first << " " << hash.second << endl;
		hash.first -= pot1(n-1) * (text[i-n+1] - 'a' + 1);
		hash.first %= MOD;
		while(hash.first < 0) hash.first += MOD;
		hash.second -= pot2(n-1) * (text[i-n+1] - 'a' + 1);
		hash.second %= MOD2;
		while(hash.second < 0) hash.second += MOD2;
	}
}

void changeHash(int ind, char c){
	patHash.first -= pot1(n - ind - 1) * (pattern[ind] - 'a' + 1);
	patHash.first %= MOD;
	while(patHash.first < 0) patHash.first += MOD;
	patHash.second -= pot2(n - ind - 1) * (pattern[ind] - 'a' + 1);
	patHash.second %= MOD2;
	while(patHash.second < 0) patHash.second += MOD2;
	pattern[ind] = c;
	patHash.first += pot1(n - ind - 1) * (pattern[ind] - 'a' + 1);
	patHash.first %= MOD;
	while(patHash.first < 0) patHash.first += MOD;
	patHash.second += pot2(n - ind - 1) * (pattern[ind] - 'a' + 1);
	patHash.second %= MOD2;
	while(patHash.second < 0) patHash.second += MOD2;
}

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	cin >> n >> m >> q >> pattern >> text;

	patternHash();
	textHashes();

	/*
	cout << endl;

	cout << patHash.first << " " << patHash.second << " " << mapa[patHash] << endl;

	cout << endl;
	*/

	while(q--){
		int x; cin >> x; char c; cin >> c;
		changeHash(x-1,c);
		//cout << patHash.first << " " << patHash.second << " " << mapa[patHash] << endl;
		cout << mapa[patHash] << "\n";
	}

}
