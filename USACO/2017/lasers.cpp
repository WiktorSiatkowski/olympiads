#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 69;
int n,xs,ys,xe,ye;
vector<pair<int,int> > adj[2*SIZE];
vector<pair<pair<int,int>,int> > pts;
vector<int> enumy,enumx;
vector<pair<int,int> > dlax[SIZE],dlay[SIZE];
unordered_map<int,pair<int,int> > mapa;
map<pair<int,int>,int> mapa2;
bool vis[SIZE*2];

int getx(int x){
	return lower_bound(enumx.begin(),enumx.end(),x) - enumx.begin();
}

int gety(int y){
	return lower_bound(enumy.begin(),enumy.end(),y) - enumy.begin();
}

int main() {
	ofstream fout ("lasers.out");
	ifstream fin ("lasers.in");

	fin >> n >> xs >> ys >> xe >> ye;
	
	enumx.push_back(xs); enumx.push_back(xe);
	enumy.push_back(ys); enumy.push_back(ye);
	
	pts.push_back({{xs,ys},0});
	
	for(int i = 1; i <= n; i++){
		int x,y; fin >> x >> y;
		enumx.push_back(x);
		enumy.push_back(y);
		pts.push_back({{x,y},i});
	}
	
	pts.push_back({{xe,ye},n+1});
	
	sort(enumx.begin(),enumx.end());
	sort(enumy.begin(),enumy.end());
	
	for(auto iter : pts){
		mapa2[iter.ST] = iter.ND;
		mapa[iter.ND] = iter.ST;
		auto it = iter.ST;
		int nr1 = getx(it.ST), nr2 = gety(it.ND);
		dlax[nr1].push_back({it.ND,it.ST});
		dlay[nr2].push_back({it.ST,it.ND});
	}
	
	for(int i = 0; i < SIZE; i++){
		if(!dlax[i].empty()) sort(dlax[i].begin(),dlax[i].end());
		if(!dlay[i].empty()) sort(dlay[i].begin(),dlay[i].end());
	}
	
	int res = 1e9;
	
	deque<pair<int,int> > q;
	q.push_back({0,0});
	q.push_back({SIZE,0});
	vis[0] = 1, vis[SIZE] = 1;
	
	while(!q.empty()){
		auto it = q.front();
		q.pop_front();
		if(it.ST >= SIZE){
			if(it.ST == SIZE + n + 1) res = min(res,it.ND);
			pair<int,int> wsp = mapa[it.ST-SIZE];
			int nr = gety(wsp.ND);
			int xdd = lower_bound(dlay[nr].begin(),dlay[nr].end(),wsp) - dlay[nr].begin();
			if(xdd - 1 >= 0){
				pair<int,int> cos = dlay[nr][xdd-1];
				int ind = mapa2[cos] + SIZE;
				if(!vis[ind]){
					vis[ind] = 1;
					q.push_front({ind,it.ND});
				}
			}
			if(xdd + 1 < dlay[nr].size()){
				pair<int,int> cos = dlay[nr][xdd+1];
				int ind = mapa2[cos] + SIZE;
				if(!vis[ind]){
					vis[ind] = 1;
					q.push_front({ind,it.ND});
				}
			}
			if(!vis[it.ST - SIZE]){
				vis[it.ST - SIZE] = 1;
				q.push_back({it.ST-SIZE,it.ND+1});
			}
		} else {
			if(it.ST == n + 1) res = min(res,it.ND);
			pair<int,int> wsp = mapa[it.ST];
			int nr = getx(wsp.ST);
			int xdd = lower_bound(dlax[nr].begin(),dlax[nr].end(),make_pair(wsp.ND,wsp.ST)) - dlax[nr].begin();
			if(xdd - 1 >= 0){
				pair<int,int> cos = dlax[nr][xdd-1];
				swap(cos.ST,cos.ND);
				int ind = mapa2[cos];
				if(!vis[ind]){
					vis[ind] = 1;
					q.push_front({ind,it.ND});
				}
			}
			if(xdd + 1 < dlax[nr].size()){
				pair<int,int> cos = dlax[nr][xdd+1];
				swap(cos.ST,cos.ND);
				int ind = mapa2[cos];
				if(!vis[ind]){
					vis[ind] = 1;
					q.push_front({ind,it.ND});
				}
			}
			if(!vis[it.ST + SIZE]){
				vis[it.ST + SIZE] = 1;
				q.push_back({it.ST+SIZE,it.ND+1});
			}
		}
	}
	
	if(res == 1e9) fout << -1;
	else fout << res;
	
    return 0;
}
