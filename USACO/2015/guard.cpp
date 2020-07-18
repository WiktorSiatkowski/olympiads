#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 20;

ll dp[MAX];

int main() {
	ofstream fout ("guard.out");
	ifstream fin ("guard.in");

	ll n,h; fin >> n >> h;
	vector<pair<pair<ll,ll>,ll> > tab(n);
	for(int i = 0; i < n; i++)
		fin >> tab[i].ST.ST >> tab[i].ST.ND >> tab[i].ND;
	
	dp[0] = 1e18;
	
	ll res = -1e18;
	
	for(int i = 1; i < (1 << n); i++){
		dp[i] = -1e18;
		ll sumh = 0;
		for(int j = 0; j < n; j++){
			if((i & (1 << j)) && dp[i ^ (1 << j)] >= tab[j].ST.ND){
				dp[i] = max(dp[i],min(dp[i ^ (1 << j)] - tab[j].ST.ND,tab[j].ND));
				sumh += tab[j].ST.ST;
			} else if(i & (1 << j)){
				sumh += tab[j].ST.ST;
			}
		}
		if(dp[i] >= 0 && sumh >= h) res = max(res,dp[i]);
	}
	
	if(res == -1e18) fout << "Mark is too tall\n";
	else fout << res;

















    return 0;
}
