#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e3 + 77;
const int DX[] = {-1,0,0,1};
const int DY[] = {0,-1,1,0};

int n,res;
int tab[SIZE][SIZE];
int pref[SIZE][SIZE];
int sweeppref[SIZE];
pair<int,int> start[SIZE*SIZE];
bool vis[SIZE][SIZE];
int minx,maxx,miny,maxy;
vector<pair<pair<int,int>,pair<int,int> > > events;

bool ok(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void dfs(int x, int y){
	vis[x][y] = 1;
	minx = min(minx,x), maxx = max(maxx,x), miny = min(miny,y), maxy = max(maxy,y);
	for(int i = 0; i < 4; i++){
		int xd = x + DX[i], yd = y + DY[i];
		if(ok(xd,yd) && tab[xd][yd] == tab[x][y] && !vis[xd][yd]) dfs(xd,yd);
	}
}

int main() {
	//ofstream fout ("art.out");
	//ifstream fin ("art.in");

	cin >> n;
	
	res = n * n;
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			cin >> tab[i][j];
			start[tab[i][j]] = {i,j};
		}
		
	int total = 0;
	
	for(int i = 1; i <= n * n; i++){
		if(start[i].ST == 0) continue;
		total++;
		minx = start[i].ND, maxx = start[i].ND, miny = start[i].ST, maxy = start[i].ST;
		dfs(start[i].ST,start[i].ND);
		events.push_back({{minx,1},{miny,maxy}});
		events.push_back({{maxx+1,-1},{miny,maxy}});
	}
	
	if(total == 1){
		cout << n * n - 1;
		return 0;
	}
	
	res = res - total;
	
	sort(events.begin(),events.end());
	int ind = 0;
	for(int i = 1; i <= n; i++){
		while(ind < events.size() && events[ind].ST.ST == i){
			if(events[ind].ST.ND == 1){
				sweeppref[events[ind].ND.ST]++;
				sweeppref[events[ind].ND.ND+1]--;
			} else {
				sweeppref[events[ind].ND.ST]--;
				sweeppref[events[ind].ND.ND+1]++;
			}
			ind++;
		}
		for(int j = 1; j <= n; j++) pref[j][i] = pref[j-1][i] + sweeppref[j];
	}
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++){
			if(tab[i][j] == 0) continue;
			if(pref[i][j] > 1) start[tab[i][j]] = {0,0};
		}
		
	for(int i = 1; i <= n * n; i++) if(start[i].ST != 0) res++;
	
	cout << res;
	
    return 0;
}
