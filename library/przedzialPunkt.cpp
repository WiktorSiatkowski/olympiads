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

const int MAX = 1 << 17;

void update(int x, int v){
	for(x+=MAX; x > 0; x >>= 1){
		t[x] += v;
	}
}

long long query(int x, int y){
	long long sum = 0;
	for(x+=MAX,y+=MAX; x < y; x>>=1,y>>=1){
		if(x&1) sum += t[x++];
		if(y&1) sum += t[--y];
	}
	return sum;
}

void build(){
	for(int i = MAX - 1; i > 0; i--)
		t[x] = t[2*x] + t[2*x+1];
}

int main(){
	turbo;
	
}