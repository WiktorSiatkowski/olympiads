#include<bits/stdc++.h>

#define ll long long
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define all(a) a.begin(),a.end()
#define turbo ios::sync_with_stdio(false)
#define VI vector<int>
#define VLL vector<ll>
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)

const int MOD = 1e9 + 7;

template<class T> inline T fastExp(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

using namespace std;

const int SIZE = 10e3;

int dp[SIZE][SIZE];

int lcsLength(string s1, string s2){
	for(int i = 0; i < s1.size(); i++){
		for(int j = 0; j < s2.size(); j++){
			int x = i + 1;
			int y = j + 1;
			if(s1[i] == s2[j])
				dp[x][y] = dp[x-1][y-1] + 1;
			else 
				d	p[x][y] = max(dp[x-1][y],dp[x][y-1]);
		}
	}
	return dp[s1.size()][s2.size()];
}

void lcs(string s1, string s2){
	string result = "";
	for(int i = s1.size() - 1; i >= 0;)
		for(int j = s2.size() - 1; j >= 0;){
			if(s1[i] == s2[j]){
				j--;
				i--;
				result += s1[i];
			} else {
				if(dp[i+1][j] > dp[i][j+1]){
					j--;
				} else {
					i--;
				}
			}
		}
	reverse(all(result));
	cout << result;
}

int main(){
	turbo;
	int x,y;
	string s1,s2;
	cin >> x >> s1 >> y >> s2;
	cout << x + y - 2 * lcsLength(s1,s2);
	lcs(s1,s2);
}
