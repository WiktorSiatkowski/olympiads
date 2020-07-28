#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e3 + 3;
const ll LINF = (ll)1e18;
int n,k;
ll res = LINF;
ll dp[SIZE][8]; 
ll tab[SIZE];
ll cost[SIZE];
ll tab2[SIZE];
ll pref[SIZE];

ll koszt(ll x, ll y){
	if(x > y) return 0;
	ll ans = cost[y] - cost[x-1];
	ans -= (x-1) * (pref[y] - pref[x-1]);
	return ans;
}

void calcdp(int l, int r, int optl, int optr, int xd){
	if(l > r) return;
	int mid = (l+r)/2;
	int tmpopt = optl;
	for(int i = optl; i <= min(mid-1,optr); i++){
		if(dp[i][xd-1] + koszt(i+2,mid) < dp[mid][xd]){
			tmpopt = i;
			dp[mid][xd] = dp[i][xd-1] + koszt(i+2,mid);
		}
	}
	calcdp(l,mid-1,optl,tmpopt,xd);
	calcdp(mid+1,r,tmpopt,optr,xd);
}

void cleardp(){
	for(int j = 1; j <= n; j++)
		for(int l = 0; l <= min(7,k); l++)
			dp[j][l] = LINF;
}

int main() {
	ofstream fout ("cbarn.out");
	ifstream fin ("cbarn.in");

	fin >> n >> k;
	k = min(k,n);

	for(int i = 1; i <= n; i++)
		fin >> tab[i];
		
	k--;
	for(int i = 1; i <= n; i++){
		cleardp();
		int ind = 1;
		for(int j = i + 1; j <= n; j++){
			tab2[ind] = tab[j];
			ind++;
		}
		for(int j = 1; j < i; j++){
			tab2[ind] = tab[j];
			ind++;
		}
		cost[0] = 0;
		pref[0] = 0;
		pref[1] = tab2[1];
		cost[1] = tab2[1];
		dp[1][0] = cost[1];
		
		for(ll j = 2; j < n; j++){
			cost[j] = cost[j-1] + j * tab2[j];
			pref[j] = pref[j-1] + tab2[j];
			dp[j][0] = cost[j];
		}	
		
		for(int j = 1; j <= k; j++){
			calcdp(1,n-1,1,n-1,j);	
		}
		
		res = min(res,dp[n-1][k]);
		
	}

	fout << res;



    return 0;
}
