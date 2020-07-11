#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 3e6 + 6;

ll n,k;
bool vis[SIZE];

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("empty.out");
	ifstream fin ("empty.in");

	fin >> n >> k;
	
	vector<pair<int,int> > events;
	
	for(int i = 0; i < k; i++){
		ll x,y,a,b; fin >> x >> y >> a >> b;
		for(ll j = 1; j <= y; j++){
			ll val = (a*j+b)%n;
			if(val < 0) val += n;
			events.push_back({val,x});
		}
	}
	
	sort(events.begin(),events.end());
	
	//for(auto it : events) cout << it.ST << " " << it.ND << endl;
	
	queue<int> q;
	int ind = 0;
	for(int i = 0; i < n; i++){
		while(ind < events.size() && events[ind].ST == i){
			q.push(events[ind].ND);
			ind++;
		}
		if(!q.empty()){
			vis[i] = 1;
			q.front()--;
			if(q.front() == 0){
				q.pop();
			}
		}
		//cout << i << " " << vis[i] << endl;
	}
	
	
	for(int i = 0; i < n; i++){
		if(!q.empty() && !vis[i]){
			vis[i] = 1;
			q.front()--;
			if(q.front() == 0){
				q.pop();
			}
		}
	}

	
	for(int i = 0; i < n; i++) 
		if(!vis[i]) {
			fout << i;
			return 0;
		}
	
    return 0;
}
