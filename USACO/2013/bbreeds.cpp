#include<bits/stdc++.h>

using namespace std;

const int MOD = 2012;

int n;

string s;

int balance[MOD];
int dp[MOD][MOD]; // # of ways to choose bracket sequence having balance j from prefix i

bool ok(int x, int j){
	return x >= 0 && balance[x] - j >= 0 && j >= 0;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("bbreeds.out");
	ifstream fin ("bbreeds.in");
	
	fin >> s;

	n = s.size();

	bool cor = true;
	
	for(int i = 1; i <= n; i++){
		balance[i] = balance[i-1];
		if(s[i-1] == '(') balance[i]++;
		else balance[i]--;
		if(balance[i] < 0) cor = false;
	}
	
	if(balance[n] != 0) cor = false;
	
	if(!cor){
		fout << 0 << "\n";
		return 0;
	}
	
	dp[0][0] = 1;
	
	for(int i = 1; i <= n; i++){
		for(int j = 0; j <= n; j++){
			if(s[i-1] == '('){
				if(ok(i-1,j-1)) dp[i][j] += dp[i-1][j-1];
				if(ok(i-1,j)) dp[i][j] += dp[i-1][j];
				dp[i][j] = dp[i][j] % MOD;
			} else {
				if(ok(i-1,j+1)) dp[i][j] += dp[i-1][j+1];
				if(ok(i-1,j)) dp[i][j] += dp[i-1][j];
				dp[i][j] = dp[i][j] % MOD;
			}
		}
	}
	
	int ans = dp[n][0] % MOD;
	
	if(ans < 0) ans += MOD;
	
	fout << ans;
    
    return 0;
}
