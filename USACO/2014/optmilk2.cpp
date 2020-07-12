#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 17;
int n,q;
ll tr[2*MAX][2][2];
ll res = 0;

void update(int x, int v){
	x += MAX;
	tr[x][1][1] = v;
	while(x /= 2){
		tr[x][0][1] = max(tr[2*x][0][0] + max({tr[2*x+1][1][1],tr[2*x+1][0][1],tr[2*x+1][0][0]}),
			tr[2*x][0][1] + max(tr[2*x+1][0][1],tr[2*x+1][0][0])); 
			 
		tr[x][0][0] = max(tr[2*x][0][0] + max(tr[2*x+1][1][0],tr[2*x+1][0][0]),tr[2*x][0][1] + tr[2*x+1][0][0]); 
		
		tr[x][1][0] = max(tr[2*x][1][0] + max({tr[2*x+1][1][0],tr[2*x+1][0][0]}),
			tr[2*x][0][0] + max(tr[2*x+1][1][0],tr[2*x+1][0][0])); 

		tr[x][1][0] = max(tr[x][1][0],max(tr[2*x][1][1] + tr[2*x+1][0][0], tr[2*x][0][1] + tr[2*x+1][0][0])); 

		tr[x][1][1] = max(tr[2*x][1][1] + max(tr[2*x+1][0][1],tr[2*x+1][0][0]),tr[2*x][1][0] 
			+ max({tr[2*x+1][1][0],tr[2*x+1][0][1],tr[2*x+1][1][1],tr[2*x+1][0][0]})); 		
			
		tr[x][1][1] = max(tr[x][1][1],max(tr[2*x][0][1] + max(tr[2*x+1][0][1],tr[2*x+1][0][0]),tr[2*x][0][0] 
			+ max({tr[2*x+1][1][0],tr[2*x+1][0][1],tr[2*x+1][1][1],tr[2*x+1][0][0]}))); 			
	}
	
	res += max({tr[1][0][0],tr[1][0][1],tr[1][1][0],tr[1][1][1]});
}

int main() {

	ofstream fout ("optmilk.out");
	ifstream fin ("optmilk.in");

	fin >> n >> q;
	
	for(int i = 0; i < n; i++){
		int x; fin >> x;
		update(i,x);
	}
	
	res = 0;
	
	while(q--){
		int a,b; fin >> a >> b;
		a--;
		update(a,b);
	}
	
	fout << res;
	
	
    return 0;
}
