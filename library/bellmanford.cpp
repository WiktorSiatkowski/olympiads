#include<bits/stdc++.h>

#define ld long double
#define ll long long
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define all(a) a.begin(),a.end()
#define turbo ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define VI vector<int>
#define VLL vector<ll>
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define VPLL vector<PLL>
#define VPII vector<PII>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)

const int MOD = 1e9 + 7;
const long long INF = 10e18;

template<class T> inline T fastExp(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

using namespace std;
const int SIZE = 600;
vector<pair<pair<int,int>,int> > edg;
long long dis[SIZE];
int n,m,s;
int main(){
	turbo;
	cin >> n >> m >> s;
	FOR(i,1,m){
		int a,b,c; cin >> a >> b >> c;
		edg.PB({{a,b},c});
	}
	FOR(i,0,n)
		dis[i] = INF;
	dis[s] = 0;
	for(int i = 1; i <= INF; i++){
		bool b = false;
		if(i >= n){
			cout << "NIE";
			return 0;
		}
		for(auto it : edg){
			if(dis[it.ST.ST] != INF && dis[it.ST.ST] + it.ND < dis[it.ST.ND]){
				b = true;
				dis[it.ST.ND] = dis[it.ST.ST] + it.ND;
			}
		}
		if(!b)
			break;
	}
	FOR(i,0,n)
		if(dis[i] != INF && i != s)
			cout << i << " " << dis[i] << "\n";
}