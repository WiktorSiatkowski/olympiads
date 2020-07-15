#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

const int MAX = 1 << 19;
int tr[2*MAX];
int n,m;

void build(){
	for(int i = MAX - 1; i > 0; i--)
		tr[i] = min(tr[2*i],tr[2*i+1]);
}

int query(int x, int y){
	if(x >= y) return 1e9;
	y = min(y,m);
	x = min(x,m-1);
	int res = 1e9;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res = min(res,tr[x++]);
		if(y&1) res = min(res,tr[--y]);
	}
	return res;
}

map<pair<int,int>,bool> vis;

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("photo.out");
	ifstream fin ("photo.in");

	fin >> n >> m;
	
	vector<pair<int,int> > tab(m);
	
	vector<int> pomocniczy;

	vector<pair<int,int> > events;
	
	for(int i = 0; i < m; i++){
		fin >> tab[i].ST >> tab[i].ND;
		pomocniczy.push_back(tab[i].ST);
		events.push_back({tab[i].ST,tab[i].ND});
		events.push_back({tab[i].ND,tab[i].ST});
	}
	
	sort(tab.begin(),tab.end());
	sort(pomocniczy.begin(),pomocniczy.end());
	
	for(int i = 0; i < m; i++) tr[i+MAX] = tab[i].ND;
	build();
	
	sort(events.begin(),events.end());
	int res = 0;

	multiset<int> endings;
	
	int iter = 0;
	
	bool pos = true;
	
	//for(auto it : pomocniczy) cout << it << " ";
	//cout << endl;
	
	vector<pair<int,int> > wszystko;
	
	for(int i = 1; i <= n; i++){
		vector<pair<int,int> > tmpeve;
		while(iter < events.size() && events[iter].ST == i){
			auto it = events[iter];
			//cout << it.ST << " " << it.ND << " " << vis[make_pair(it.ND,it.ST)] << "\n";
			if(it.ST >= it.ND && vis[make_pair(it.ND,it.ST)]){
				iter++;
				continue;
			}
			tmpeve.push_back(it);
			iter++;
		}
		
		//for(auto it : tmpeve)
			//cout << it.ST << " " << it.ND << endl;
			
		//cout << endl << endl;
		
		bool musze = false;
		bool moge = false;
		for(auto it : tmpeve){
			if(it.ST <= it.ND){
				endings.insert(it.ND);
				wszystko.push_back({it.ST,it.ND});
			} else {
				musze = true;
			}
		}
		
		if(endings.empty() && musze) assert(false);
		if(endings.empty()) continue;
		auto iter = endings.end(); --iter;
		int maks = *iter;
		int indeks1 = (upper_bound(pomocniczy.begin(),pomocniczy.end(),i) - pomocniczy.begin());
		int indeks2 = (upper_bound(pomocniczy.begin(),pomocniczy.end(),maks) - pomocniczy.begin());
		int pytaj = query(indeks1,indeks2);
		if(pytaj > maks) moge = true;
		//cout << i << " " << maks << " " << indeks1 << " " << indeks2 << " " << pytaj <<  " " << moge << " " << musze << endl;
		if(moge){
			res++;
			endings.clear();
			for(auto it : wszystko){
//				cout << it.ST << " " << it.ND << " ]\n";
				vis[make_pair(it.ST,it.ND)] = 1;	
			}
			wszystko.clear();
		} else if(musze){
			pos = false;
			break;
		}
		//cout << i << " " << maks << " " << indeks1 << " " << indeks2 << " " << pytaj << endl;
		if(endings.count(i)) assert(false);
		endings.erase(i);
	}

	//cout << vis[make_pair(4,1)] << endl;

	if(pos) fout << res;
	else fout << -1;
	
    return 0;
}
