#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 18;

ll trmin[2*MAX], mindelta[2*MAX];
ll trsum[2*MAX], sumdelta[2*MAX];
int n,m;

void update(int a, int b, int u, ll lo, ll hi, ll x){
	if(a == lo && b == hi){
		mindelta[u]+=x;
		sumdelta[u] +=x;
		trmin[u]+=x;
		trsum[u] += x*(hi-lo);
		return;
	}
	if(b <= a) return;
	int mid = (lo + hi)/2;
	update(a,min(b,mid),2*u,lo,mid,x);
	update(max(a,mid),b,2*u+1,mid,hi,x);
	trsum[u] = trsum[2*u] + trsum[2*u+1] + sumdelta[u] * (hi-lo);
	trmin[u] = min(trmin[2*u],trmin[2*u+1]) + mindelta[u];
}

ll querymin(int a, int b, int u, int lo, int hi){
	if(a == lo && b == hi){
		return trmin[u];
	}
	if(b <= a) return (ll)1e18;
	int mid = (lo+hi)/2;
	ll l = querymin(a,min(b,mid),2*u,lo,mid);
	ll r = querymin(max(a,mid),b,2*u+1,mid,hi);
	return min(l,r) + mindelta[u];
}

ll querysum(ll a, ll b, ll u, ll lo, ll hi){
	if(a == lo && b == hi){
		return trsum[u];
	}
	if(b <= a) return 0;
	ll mid = (lo+hi)/2;
	if(sumdelta[u]){
		sumdelta[2*u] += sumdelta[u];
		sumdelta[2*u+1] += sumdelta[u];
		trsum[2*u] += sumdelta[u] * (mid - lo);	
		trsum[2*u+1] += sumdelta[u] * (hi - mid);
		sumdelta[u] = 0;	
	}
	ll l = querysum(a,min(b,mid),2*u,lo,mid);
	ll r = querysum(max(a,mid),b,2*u+1,mid,hi);
	return l + r;
}

void build(){
	for(int i = MAX - 1; i > 0; i--){
		trsum[i] = trsum[2*i] + trsum[2*i+1];
		trmin[i] = min(trmin[2*i],trmin[2*i+1]);
	}
}

int main() {
	ofstream fout ("haybales.out");
	ifstream fin ("haybales.in");

	fin >> n >> m;
	for(int i = 0; i < n; i++){
		fin >> trmin[i+MAX];
		trsum[i+MAX] = trmin[i+MAX];
	}
	
	build();
	
	while(m--){
		char c; fin >> c;
		if(c == 'M'){
			ll x,y; fin >> x >> y; x--;
			fout << querymin(x,y,1,0,MAX) << "\n";
		} else if(c == 'P'){
			ll x,y,z; fin >> x >> y >> z; x--;
			update(x,y,1,0,MAX,z);
		} else {
			ll x,y; fin >> x >> y; x--;
			fout << querysum(x,y,1,0,MAX) << "\n";
		}
	}

    return 0;
}
