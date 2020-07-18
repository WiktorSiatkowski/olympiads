#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int n,k;

struct event{
	int x = -68, y = -68, type = -68, val = -68;
	event(int a, int b, int c, int d){
		x = a, y = b, type = c, val = d;
	}
};

int main() {
	//ofstream fout ("lazy.out");
	//ifstream fin ("lazy.in");

	cin >> n >> k;

	set<int> en;
	vector<event> events; // 1 dodaj punt, -1 odejmij punkt
	for(int i = 0; i < n; i++){
		int g,x,y; cin >> g >> x >> y;
		events.push_back(event(x-y,x+y,1,g));
		events.push_back(event(x+k+1-y,x+k+1+y,-1,-g));
	}

	sort(events.begin(),events.end(),[](event a, event b){
		return a.x < b.x;
	});
	
	for(auto it : events)
		cout << it.x << endl;

    return 0;
}
