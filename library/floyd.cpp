#include<bits/stdc++.h>
#define ST first
#define ND second
#define PB push_back
using namespace std;

int dist[200][200];

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n; cin >> n;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) dist[i][j] = 1e9;
	for(int i = 1; i <= n; i++) {
		string s; cin >> s;
		dist[i][i] = 0;
		for(int j = 1; j <= n; j++)
			if(s[j-1] == '1')
				dist[i][j] = 1;
	}
	
	for(int k = 1; k <= n; k++) 
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++) 
				dist[i][j] = min(dist[i][j],dist[i][k] + dist[k][j]);

	while(true){
		int x,y; cin >> x >> y;
		cout << dist[x][y] << endl;
	}

	

}
