#include<bits/stdc++.h>

#define ll long long
#define ld long double
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define all(a) a.begin(),a.end()
#define turbo ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define VPII vector<PII>
#define VPLL vector<PLL>
#define VI vector<int>
#define VLL vector<ll>
#define FOR(i, a, b) for(int i =(a); i <=(b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define len size()

const int MOD = 1e9 + 7;

template<class T> inline T fastExp(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

using namespace std;

const int SIZE = 30e4 + 1;
int parent[SIZE];

int find(int x) {
    if(parent[x]==x) return x;
    parent[x] =  find(parent[x]);
    return parent[x];
}

void unionn(int x, int y) {
    parent[find(x)] = find(y);
}

int main(){
	turbo;
}