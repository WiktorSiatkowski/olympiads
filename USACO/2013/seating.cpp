#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 19;

int n,m;

int state[2*MAX], maxpref[2*MAX], maxsuf[2*MAX];
pair<int,int> wyn[2*MAX], lr[2*MAX];

void build(){
	for(int i = MAX; i < 2 * MAX; i++){
		maxpref[i] = 1;
		maxsuf[i] = 1;
		wyn[i] = {i - MAX,1};
		lr[i] = {i-MAX,i-MAX};	
	}
	for(int i = MAX - 1; i > 0; i--){
		maxpref[i] = maxpref[2 * i] * 2;
		maxsuf[i] = maxsuf[2 * i] * 2;
		wyn[i] = {wyn[2*i].ST,wyn[2*i].ND * 2};
		lr[i] = {lr[2*i].ST,lr[2*i+1].ND};
	}
}

void chujkurwa1(int u){
	state[u] = -1;
	wyn[u].ST = -1;
	wyn[u].ND = -1;
	maxpref[u] = -1;
	maxsuf[u] = -1;
}

void chujkurwa2(int u, int len){
	state[u] = 1;
	maxpref[u] = len;
	maxsuf[u] = len;
	wyn[u].ND = len;
	wyn[u].ST = lr[u].ST;
}

void update(int u, int lo, int hi){
	if(state[2*u] == 1){
		chujkurwa2(2*u,(hi-lo)/2);
	} else if(state[2*u+1] == 1){
		chujkurwa2(2*u+1,(hi-lo)/2);
	}
	if(state[2*u] == -1){
		wyn[u] = wyn[2*u+1];
		maxpref[u] = 0;
		maxsuf[u] = maxsuf[2*u+1];
	} else if(state[2*u+1] == -1){
		wyn[u] = wyn[2*u];
		maxpref[u] = maxpref[2*u];
		maxsuf[u] = 0;;
	} else {
		int x = maxsuf[2*u] + maxpref[2*u+1];
		int y = wyn[2*u].ND;
		int z = wyn[2*u+1].ND;
		
		if(x >= y && x >= z){
			int stpt = lr[2*u].ND - maxsuf[2*u] + 1;
			if(stpt < 0) assert(false);
			if(x == y) wyn[u] = {min(stpt,wyn[2*u].ST),x};
			else wyn[u] = {stpt,x};
		} else if(y >= x && y >= z){
			wyn[u] = wyn[2*u];		
		} else {
			wyn[u] = wyn[2*u+1];		
		}
		
		if(maxpref[2*u] == (hi-lo)/2){
			maxpref[u] = (hi-lo)/2 + maxpref[2*u+1];
		} else {
			maxpref[u] = maxpref[2*u];
		}
		
		if(maxsuf[2*u+1] == (hi-lo)/2){
			maxsuf[u] = (hi-lo)/2 + maxsuf[2*u];
		} else {
			maxsuf[u] = maxsuf[2*u+1];
		}
		
	}
}

int query(int u, int przlen, int len, int lo, int hi){
	//cout << u << endl;
	if(u >= MAX){
		return u - MAX;
	}
	if(state[u] == 1){
		state[u] = 0;
		chujkurwa2(2*u,len/2);
		chujkurwa2(2*u+1,len/2);
	}
	if(wyn[u].ND >= len){
		if(wyn[2*u].ND >= len){
			int tmp = query(2*u,przlen/2,len,lo,(lo+hi)/2);
			update(u,lo,hi);
			return tmp;
		} else {
			return wyn[u].ST;
		}
	} else {
		return -1;
	}
	
}

void blockit(int a, int b, int u, int lo, int hi){
	if(a == lo && b == hi){
		chujkurwa1(u);
		return;
	}
	if(b <= a) return;
	int mid = (lo + hi)/2;
	if(state[u] == 1){
		state[u] = 0;
		chujkurwa2(2*u,mid - lo);
		chujkurwa2(2*u+1,hi - mid);
	}
	blockit(a,min(b,mid),2*u,lo,mid);
	blockit(max(a,mid),b,2*u+1,mid,hi);
	update(u,lo,hi);
}

void unblockit(int a, int b, int u, int lo, int hi){
	if(a == lo && b == hi){
		chujkurwa2(u,hi - lo);
		return;
	}
	if(b <= a) return;
	if(state[u] == -1){
		state[u] = 0;
		chujkurwa1(2*u);
		chujkurwa1(2*u+1);
	}
	int mid = (lo + hi)/2;
	unblockit(a,min(b,mid),2*u,lo,mid);
	unblockit(max(a,mid),b,2*u+1,mid,hi);
	update(u,lo,hi);
}

int main() {
	//cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("seating.out");
	ifstream fin ("seating.in");
	
	int res = 0;

	build();
	
	cin >> n >> m;
    
    while(m--){
    	char c; cin >> c;
    	if(c == 'A'){
    		int x; cin >> x;
    		int qr = query(1,MAX,x,0,MAX);
    		if(qr == -1 || qr + x - 1 >= n) res++;
    		else blockit(qr,qr + x,1,0,MAX);
    		//cout << qr << endl;
    	} else {
    		int x,y; cin >> x >> y;
    		x--;
    		unblockit(x,y,1,0,MAX);
    	}
    }
    
   	/*for(int i = 1; i < 2 * MAX; i++){
		cout << i << "  :  " << state[i] << " " << maxpref[i] << " " << maxsuf[i] << " " << wyn[i].ST << " " << wyn[i].ND << endl;
	}*/

	cout << res << "\n";
	
	return 0;
}
