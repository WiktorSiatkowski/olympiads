#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 21;
ll dp[(int)(1 << SIZE)];
ll tab[SIZE][SIZE];

int main() {
	ofstream fout ("dec.out");
	ifstream fin ("dec.in");
	
	int n,b; fin >> n >> b;
	vector<vector<pair<ll,ll> > > extra(n+1);
	for(int i = 0; i < b; i++){
		ll x,y,z; fin >> x >> y >> z;
		extra[x].push_back({y,z});
	}
	
	for(int i = 1; i <= n; i++)
		if(!extra[i].empty()) sort(extra[i].begin(),extra[i].end());

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			fin >> tab[i][j];
			
	for(int i = 0; i < (1 << n); i++){
		int ile = __builtin_popcount(i);
		for(int j = 0; j < n; j++){
			if(i & (1 << j)){
				dp[i] = max(dp[i],dp[i ^ (1 << j)] + tab[j][ile-1]);
			}
		}
		for(auto it : extra[ile])
			if(dp[i] >= it.ST) dp[i] += it.ND;
			else break;
		//cout << i << " " << dp[i] << endl;
	}
	
	fout << dp[(1 << n)-1];

    return 0;
}
