#include<bits/stdc++.h>
#define ST first
#define ND second
#define ll long long
#define ld long double
using namespace std;

struct event{
	int x,y,type;
	event(int a = 0, int b = 0,int c = 69){
		x = a, y = b, type = c;
	}
};

struct segment{
	int x1,y1,x2,y2;
	segment(int a = 0,int b = 0,int c = 0,int d = 0){
		x1 = a, y1 = b, x2 = c, y2 = d;
	}
};

int curx;
map<pair<int,int> ,segment> mapa;
segment obecny;


struct cmp{
	bool operator()(const segment& l, const segment& r){
		ld dif11 = l.y2 - l.y1;
		ld dif12 = l.x2 - l.x1;
		ld dif13 = curx - l.x1;
		ld dif21 = r.y2 - r.y1;
		ld dif22 = r.x2 - r.x1;
		ld dif23 = curx - r.x1;
		return (dif11/dif12) * dif13 + (ll)l.y1 > (dif21/dif22) * dif23 + (ll)r.y1;
	}
};

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("hillwalk.out");
	ifstream fin ("hillwalk.in");
	
	
	int n; fin >> n;
	vector<segment> tab(n);
	vector<event> events;
	
	for(int i = 0; i < n; i++){
		fin >> tab[i].x1 >> tab[i].y1 >> tab[i].x2 >> tab[i].y2;
		pair<int,int> pa = {tab[i].x1,tab[i].y1};
		mapa[pa] = tab[i];
		pa = {tab[i].x2,tab[i].y2};
		mapa[pa] = tab[i];
		event tmp(tab[i].x1,tab[i].y1,1);
		events.push_back(tmp);
		tmp = event(tab[i].x2,tab[i].y2,-1);
		events.push_back(tmp);
	}

	sort(events.begin(),events.end(),[](const event& a, const event& b) {
		if(a.x != b.x) return a.x < b.x;
		else return a.y < b.y;
	});

	int res = 1;
	obecny = mapa[make_pair(0ll,0ll)];
	set<segment,cmp> secior;
	secior.insert(obecny);
	
	cmp kutas;
	
	for(int i = 1; i < events.size(); i++){
		auto it = events[i];
		if(it.type == 1){
			curx = it.x;
			segment tmp = mapa[make_pair(it.x,it.y)];
			if(kutas(obecny,tmp)) secior.insert(mapa[make_pair(it.x,it.y)]);
		} else {
			segment seg = mapa[make_pair(it.x,it.y)];
			secior.erase(seg);
			if(seg.x1 == obecny.x1 && seg.y1 == obecny.y1 && seg.y2 == obecny.y2 && seg.x2 == obecny.x2){
				if(secior.empty()) break;
				res++;
				obecny = *secior.begin();
			}
		}
	}

	fout << res;

	return 0;
}
