#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 2;
const ll MOD = 1e9 + 7;
const ll BASE = 37;

vector<vector<ll> > hasze;
ll pot[SIZE];
int leftind[SIZE],rightind[SIZE];
int n;
vector<string> tab;
vector<ll> res;
vector<pair<int,int> > sufarr;

bool same(int nr1, int a1, int b1, int nr2, int a2, int b2){
	if(b1 > tab[nr1].size() || b2 > tab[nr2].size()) return false;
	ll ha1 = (hasze[nr1][b1] - hasze[nr1][a1-1]) % MOD;
	ll ha2 = (hasze[nr2][b2] - hasze[nr2][a2-1]) % MOD;
	if(b1 > b2){
		ha2 = (ha2 * pot[b1 - b2]) % MOD;	
	} else if(b2 > b1){
		ha1 = (ha1 * pot[b2 - b1]) % MOD;
	}
	if(ha1 < 0) ha1 += MOD;
	if(ha2 < 0) ha2 += MOD;
	return (ha1 == ha2);
}

int lcp(pair<int,int> s1, pair<int,int> s2){
	int nr1 = s1.ND, nr2 = s2.ND;
	int a1 = tab[nr1].size() - s1.ST + 1, b1 = tab[nr1].size();
	int a2 = tab[nr2].size() - s2.ST + 1, b2 = tab[nr2].size();
	if(!same(nr1,a1,a1,nr2,a2,a2)) return 0;
	int l = 0, r = min(s1.ST,s2.ST);
	while(l + 1 < r){
		int mid = (l+r)/2;
		if(same(nr1,a1,a1+mid,nr2,a2,a2+mid)) l = mid;
		else r = mid;
	}
	return l + 1;
}

struct cmp{
	bool operator()(pair<int,int> a, pair<int,int> b){
		int dl1 = tab[a.ND].size(), dl2 = tab[b.ND].size();
		int x = lcp(a,b);
		if(dl1 - a.ST + x == tab[a.ND].size()) return false;
		if(dl2 - b.ST + x == tab[b.ND].size()) return true;
		return tab[a.ND][dl1 - a.ST + x] <= tab[b.ND][dl2 - b.ST + x];
	}
};

int main() {
	ios::sync_with_stdio(false);
	ofstream fout ("standingout.out");
	ifstream fin ("standingout.in");

	pot[0] = 1,leftind[0] = -1, rightind[0] = -1;
	for(int i = 1; i < SIZE; i++) pot[i] = (pot[i-1] * BASE) % MOD, leftind[i] = -1, rightind[i] = -1;

	fin >> n;
	for(int i = 0; i < n; i++){
		string s; fin >> s;
		tab.push_back(s);
		res.push_back((ll)(s.size()) * (ll)(s.size() + 1) / 2);
		vector<ll> ha(s.size() + 1);
		for(int j = 1; j <= s.size(); j++){
			sufarr.push_back({j,i});
			ha[j] = (ha[j-1] + (ll)(s[j-1] - 'a' + 1) * pot[j]) % MOD;
			if(ha[j] < 0) ha[j] += MOD;
		}
		hasze.push_back(ha);
	}
	
	sort(sufarr.begin(),sufarr.end(),cmp());
	
	for(int i = 1; i < sufarr.size(); i++)
		if(sufarr[i-1].ND != sufarr[i].ND) leftind[i] = i - 1;
		else leftind[i] = leftind[i-1];
		
	for(int i = sufarr.size() - 2; i >= 0; i--)
		if(sufarr[i+1].ND != sufarr[i].ND) rightind[i] = i + 1;
		else rightind[i] = rightind[i+1];

	for(int i = 0; i < sufarr.size(); i++){
		int maks = 0;
		int xd = 0;
		if(leftind[i] != -1) maks = max(maks,lcp({sufarr[i].ST,sufarr[i].ND},{sufarr[leftind[i]].ST,sufarr[leftind[i]].ND}));
		if(rightind[i] != -1) maks = max(maks,lcp({sufarr[i].ST,sufarr[i].ND},{sufarr[rightind[i]].ST,sufarr[rightind[i]].ND}));
		if(i > 0 && sufarr[i-1].ND == sufarr[i].ND) {
			xd = lcp({sufarr[i-1].ST,sufarr[i-1].ND},{sufarr[i].ST,sufarr[i].ND});
			res[sufarr[i].ND] -= max(maks,xd);
		} else {
			res[sufarr[i].ND] -= maks;
		}
	}
	
	for(auto it : res) fout << it << "\n";
	
	return 0;
}
