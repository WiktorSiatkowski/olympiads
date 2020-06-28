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

struct cmp{
	bool operator()(PLL a, PLL b){
		return a.ND * b.ST - b.ND * a.ST < 0;
	}
};

ll n;
VPLL points;
PLL minP = {INF,INF};

int main(){
	turbo;
	cin >> n;
	FOR(i,1,n){
		ll x,y; cin >> x >> y;
		points.PB({x,y});
		if(y < minP.ND || (y == minP.ND && x < minP.ST)){
			minP.ST = x;
			minP.ND = y;
		}
	}
	for(auto it : points){
		it.ST -= minP.ST;
		it.ND -= minP.ND;
	}
	sort(all(points),cmp());
	for(auto it : points){
		it.ST += minP.ST;
		it.ND += minP.ND;
	}	
}