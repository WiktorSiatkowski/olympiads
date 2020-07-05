#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

long long n,m;

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("taxi.out");
	ifstream fin ("taxi.in");
	
	vector<pair<long long,long long> > events;

	fin >> m >> n;
	
	events.push_back({0,-1});
	events.push_back({n,1});

	long long res = 0;
	
	for(int i = 0; i < m; i++){
		long long a,b; fin >> a >> b;
		if(a == b) continue;
		res += abs(a-b);
		events.push_back({a,1});
		events.push_back({b,-1});
	}
	
	sort(events.begin(),events.end());
	
	long long licznik = events[0].ND;
	
	for(int i = 1; i < events.size(); i++){
		res += abs((events[i].ST - events[i-1].ST) * licznik);
		licznik += events[i].ND;
	}
	
	fout << res;
	
	return 0;
}
