#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MOD = 1e9 + 9;
const int SIZE = 1e3 + 3;

int n,m,k;
ll dp[SIZE][SIZE][11];
ll pref[SIZE][SIZE];
vector<ll> tab1,tab2;

ll addd(ll x, ll y){
	ll ans = (x + y) % MOD;
	if(ans < 0) return ans + MOD;
	return ans;
}

void updatepref(int x){
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			pref[i][j] = addd(addd(addd(pref[i-1][j],pref[i][j-1]), -pref[i-1][j-1]),dp[i][j][x]);
		}
}

int main() {
	ofstream fout ("team.out");
	ifstream fin ("team.in");

	fin >> n >> m >> k;
	tab1.push_back(-MOD);
	tab2.push_back(-MOD);
	for(int i = 0; i < n; i++){
		ll x; fin >> x;
		tab1.push_back(x);
	}	
	for(int i = 0; i < m; i++){
		ll x; fin >> x;
		tab2.push_back(x);
	}
	
	sort(tab1.begin(),tab1.end());
	sort(tab2.begin(),tab2.end());

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(tab1[i] > tab2[j]) dp[i][j][1] = 1;
	
	updatepref(1);
			
	for(int xd = 2; xd <= k; xd++){
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++)
				if(tab1[i] > tab2[j])
					dp[i][j][xd] = pref[i-1][j-1];
		updatepref(xd);
	}
	
	fout << pref[n][m];

    return 0;
    
}
