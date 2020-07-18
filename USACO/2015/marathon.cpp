#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
const int MAX = 1 << 17;
int n,q;

struct node1{
	ll x1,y1,x2,y2,odl;

	node1(ll a = 0, ll b = 0, ll c = 0, ll d = 0, ll e = -MAX){
		x1 = a, y1 = b, x2 = c, y2 = d, odl = e;
	}

};

node1 tr1[2*MAX];
ll tr2[2*MAX];

ll roz(ll x, ll y){
	return abs(tr1[x+MAX].x1 - tr1[y+MAX].x1) + abs(tr1[x+MAX].y1 - tr1[y+MAX].y1);
}

void update2(ll x){
	if(x <= 0 || x >= n-1) return;
	tr2[x+MAX] = roz(x-1,x) + roz(x,x+1) - roz(x-1,x+1);
	x += MAX;
	while(x /= 2){
		tr2[x] = max(tr2[2*x],tr2[2*x+1]);
	}
}

ll query2(ll x, ll y){
	ll res = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res = max(res,tr2[x++]);
		if(y&1) res = max(res,tr2[--y]);
	}
	return res;
}

void build(){
	for(int i = 1; i + 1 < n; i++)
		tr2[i+MAX] = roz(i-1,i) + roz(i,i+1) - roz(i-1,i+1);
		
	for(int i = MAX - 1; i > 0; i--){
		ll x1 = tr1[2*i].x1;
		ll y1 = tr1[2*i].y1;
		ll x2 = tr1[2*i+1].x2;
		ll y2 = tr1[2*i+1].y2;
		
		ll x3 = tr1[2*i].x2;
		ll y3 = tr1[2*i].y2;
		ll x4 = tr1[2*i+1].x1;
		ll y4 = tr1[2*i+1].y1;
		
		tr1[i] = node1(x1,y1,x2,y2,tr1[2*i].odl + tr1[2*i+1].odl + abs(x3-x4) + abs(y3-y4));
		tr2[i] = max(tr2[2*i],tr2[2*i+1]);
	}
		
}

node1 dis(ll a, ll b, ll u, ll lo, ll hi){
	if(a == lo && b == hi){
		return tr1[u];
	} 
	
	if(b <= a) return node1();
	
	ll mid = (lo+hi)/2;
	
	node1 l = dis(a,min(b,mid),2*u,lo,mid);
	node1 r = dis(max(a,mid),b,2*u+1,mid,hi);
	
	if(l.odl == -MAX){
		return r;
	} else if(r.odl == -MAX){
		return l;
	} else {
		ll x1 = l.x1;
		ll y1 = l.y1;
		ll x2 = r.x2;
		ll y2 = r.y2;
		ll x3 = l.x2;
		ll y3 = l.y2;
		ll x4 = r.x1;
		ll y4 = r.y1;
		return node1(x1,y1,x2,y2,l.odl + r.odl + abs(x3-x4) + abs(y3-y4));
	}
}

void update(ll x, ll a, ll b){
	x += MAX;
	tr1[x] = node1(a,b,a,b,0);
	while(x /= 2){
		ll x1 = tr1[2*x].x1;
		ll y1 = tr1[2*x].y1;
		ll x2 = tr1[2*x+1].x2;
		ll y2 = tr1[2*x+1].y2;
		
		ll x3 = tr1[2*x].x2;
		ll y3 = tr1[2*x].y2;
		ll x4 = tr1[2*x+1].x1;
		ll y4 = tr1[2*x+1].y1;
		
		tr1[x] = node1(x1,y1,x2,y2,tr1[2*x].odl + tr1[2*x+1].odl + abs(x3-x4) + abs(y3-y4));
	}
}

int main() {
	ofstream fout ("marathon.out");
	ifstream fin ("marathon.in");

	fin >> n >> q;
	
	for(int i = 0; i < n; i++){
		ll a,b; fin >> a >> b;
		tr1[i+MAX] = node1(a,b,a,b,0);
	}
	
	build();
		
	while(q--){
		char c; fin >> c;	
		if(c == 'Q'){
			ll x,y; fin >> x >> y;
			x--,y--;
			fout << dis(x,y+1,1,0,MAX).odl - query2(x+1,y) << "\n";
		} else {
			ll ind,x,y; fin >> ind >> x >> y;
			update(ind-1,x,y);
			update2(ind-2);
			update2(ind-1);
			update2(ind);
		}
	}

    return 0;
}
