#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("nochange.out");
	ifstream fin ("nochange.in");

	int k,n; fin >> k >> n;
	vector<ll> nom(k);
	for(int i = 0; i < k; i++) fin >> nom[i];
	
	vector<ll> tab(n);
	for(int i = 0; i < n; i++) fin >> tab[i];
	for(int i = 1; i < n; i++) tab[i] = tab[i-1] + tab[i];
	
	vector<int> dp((1 << k)); // maximum index of tab that can be covered with mask of coins
	dp[0] = -1;
	
	ll res = -1;
	
	for(int i = 1; i < (1 << k); i++){
		dp[i] = -1;
		ll tmpres = 0;
		for(int j = 0; j < k; j++){
			int val = (1 << j);
			if(!(i & val)){
				tmpres += nom[j];
				continue;
			}
			int ind = dp[i^val];
			ll tmpsum = nom[j];
			if(ind != -1) tmpsum += tab[ind]; 
			dp[i] = max(dp[i],(int)(upper_bound(tab.begin(),tab.end(),tmpsum) - tab.begin() - 1));
		}	
		if(dp[i] == (int)tab.size() - 1) res = max(res,tmpres);
	}
	
	fout << res;
	
    return 0;
}
