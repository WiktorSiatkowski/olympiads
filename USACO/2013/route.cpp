#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 5;
int a,b,m;
int values1[SIZE], values2[SIZE];
vector<int> adj1[SIZE]. adj2[SIZE];
long long dp1[SIZE], dp2[SIZE];

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("route.out");
	ifstream fin ("route.in");
	
	cin >> a >> b >> m;
	for(int i = 1; i <= a; i++) cin >> values1[i];
	for(int i = 1; i <= b; i++) cin >> values2[i];
	
	for(int i = 1; i <= m; i++){
		int x,y; cin >> x >> y;
		adj1[x].push_back(y);
		adj2[y].push_back(x);
	}	
	
	for(int i = 1; i <= a; i++) dp1[i] = values1[i];
	for(int i = 1; i <= b; i++) dp2[i] = values2[i];
	
	for(int i = 1; i <= min(a,b); i++){
		bool ok = false;
		long long maks1 = 0, maks2 = 0;
		for(auto it : adj1[i]){
			if(it == i) ok = true;
			else maks1 = max(maks1,dp2[it]);
		}
		for(auto it : adj2[i]){
			if(it == i) ok = true;
			else maks2 = max(maks2,dp1[it]);
		}
		if(ok){
		
		} else {
			
		}
	}
	
	for(int i = min(a,b) + 1; i <= max(a,b); i++){
	
	}
	
	return 0;
}
