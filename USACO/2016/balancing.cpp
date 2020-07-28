#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 20;
int n,res;
vector<pair<int,int> > pts;
int trl[2*MAX],trr[2*MAX];

void updl(int x, int v){
	x += MAX;
	trl[x] += v;
	while(x /= 2)
		trl[x] += v;
}	

void updr(int x, int v){
	x += MAX;
	trr[x] += v;
	while(x /= 2)
		trr[x] += v;
}

int queryl(int x, int y){
	int res = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res += trl[x++];
		if(y&1) res += trl[--y];
	}
	return res;
}

int queryr(int x, int y){
	int res = 0;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res += trr[x++];
		if(y&1) res += trr[--y];
	}
	return res;
}

void updateres(){
	int alll = queryl(0,MAX);
	int allr = queryr(0,MAX);
	int maks = 1e9;
	int l = -1, r = MAX;
	while(l + 1 < r){
		int mid = (l+r)/2;
		int xd1 = queryl(0,mid);
		int xd2 = queryr(0,mid);
		maks = min(maks,max({xd1,xd2,alll - xd1, allr - xd2}));
		if(max(xd1,xd2) >= max(alll - xd1,allr - xd2)) r = mid;
		else l = mid;
	}
	res = min(res,maks);
}

int main() {
	ofstream fout ("balancing.out");
	ifstream fin ("balancing.in");

	fin >> n;
	res = n;
	for(int i = 0; i < n; i++){
		int x,y; fin >> x >> y;
		pts.push_back({x,y});
		updr(y,1);
	}
	
	sort(pts.begin(),pts.end());
	
	updateres();
	
	for(auto it : pts){
		updl(it.ND,1);
		updr(it.ND,-1);
		updateres();
	}
	
	fout << res;

    return 0;
}
