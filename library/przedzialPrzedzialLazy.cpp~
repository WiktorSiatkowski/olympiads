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

const int MAX = 1 << 20;

ll S[2*MAX];
ll M[2*MAX];

int n,q;

void update(int a,int b, int u, int lo, int hi, int v){
	if(a==lo && b==hi){
		M[u] = v;
		S[u] = (hi - lo) * M[u];
		return;
	}
	if(b<=a) return;
	int mid = (lo+hi)/2;
	if(M[u]!=-1){
		M[2*u] = M[u];
		M[2*u+1] = M[u];
		S[2*u] = (mid-lo) * M[u];
		S[2*u+1] = (hi - mid) * M[u];
		M[u] = -1;
	}
	update(a,min(b,mid),2*u,lo,mid,v);
	update(max(a,mid),b,2*u+1,mid,hi,v);
	S[u] = S[2*u] + S[2*u+1];
}

ll query(int a,int b, int u, int lo, int hi){
	if(a==lo && b==hi){
		return S[u];
	}
	if(b<=a) return 0;
	int mid = (lo+hi)/2;
	if(M[u]!=-1){
		M[2*u] = M[u];
		M[2*u+1] = M[u];
		S[2*u] = (mid-lo) * M[u];
		S[2*u+1] = (hi - mid) * M[u];
		M[u] = -1;
	}
	ll l = query(a,min(b,mid),2*u,lo,mid);
	ll r = query(max(a,mid),b,2*u+1,mid,hi);
	return l + r;
}

void init(){
	for(int i = MAX-1; i > 0; i--){
		M[i] = -1;
		S[i] = S[2*i] + S[2*i+1];
	}
	for(int i = MAX; i < 2 * MAX; i++)
		M[i] = -1;
}

int main(){
	turbo;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> S[i+MAX];
	init();
	cin >> q;
	while(q--){
		string s;
		cin >> s;
		if(s=="Update"){
			int x,y,z; cin >> x >> y >> z;
			update(x-1,y,1,0,MAX,z);
		} else {
			int x,y;
			cin >> x >> y;
			cout << query(x-1,y,1,0,MAX) << "\n";
		}
	} 

