#include<bits/stdc++.h>

using namespace std;

int SQR;
map<int,int> cnt;
int maxPoint;
vector<pair<pair<int,int>,int> > queries;
set<pair<int,int> > secik;
int tab[100000];

struct cmp{
	bool operator()(pair<pair<int,int>,int> x, pair<pair<int,int>,int> y) {
	int block_x = x.first.first / SQR;
   int block_y = y.first.first / SQR;
	if(block_x != block_y)
		return block_x < block_y;
    	
	return x.first.second < y.first.second;
	}
};

int main(){
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int n; cin >> n;
	SQR = ceil(sqrt(n));	

	for(int i = 1; i <= n; i++) cin >> tab[i];

	int q; cin >> q;
	for(int i = 1; i <= q; i++){
		int a,b; cin >> a >> b;
		queries.push_back({{a,b},i});
	}	
	
	sort(queries.begin(),queries.end(),cmp());

	vector<pair<int,int> > ans;
	
	int l = queries[0].first.first;
	int r = queries[0].first.second;
		
	for(int i = l; i <= r; i++){
		cnt[tab[i]]++;
		if(cnt[tab[i]] > cnt[maxPoint] || (cnt[tab[i]] == cnt[maxPoint] && maxPoint > tab[i]))
			maxPoint = tab[i];		

	}
	
	for(auto it : cnt)
		if(it.second != 0) secik.insert({it.second,-it.first});	

	ans.push_back({queries[0].second,maxPoint});


	for(int i = 1; i < queries.size(); i++){
		
		int l2 = queries[i].first.first;
		int r2 = queries[i].first.second;
		int ind = queries[i].second;

		if(l2 > l){
			for(int j = l; j < l2; j++){
				secik.erase({cnt[tab[j]],-tab[j]});				
				cnt[tab[j]]--;
				if(cnt[tab[j]] > 0) secik.insert({cnt[tab[j]],-tab[j]});
			}
		} else {
			for(int j = l-1; j >= l2; j--){
				secik.erase({cnt[tab[j]],-tab[j]});				
				cnt[tab[j]]++;
				if(cnt[tab[j]] > 0) secik.insert({cnt[tab[j]],-tab[j]});
			}
		}
	
		if(r2 > r){
			for(int j = r+1; j <= r2; j++){
				secik.erase({cnt[tab[j]],-tab[j]});
				cnt[tab[j]]++;
				if(cnt[tab[j]] > 0) secik.insert({cnt[tab[j]],-tab[j]});
			}
		} else {
			for(int j = r; j > r2; j--){
				secik.erase({cnt[tab[j]],-tab[j]});				
				cnt[tab[j]]--;
				if(cnt[tab[j]] > 0) secik.insert({cnt[tab[j]],-tab[j]});
			}
		}

		l = l2;
		r = r2;

		auto iter = secik.end();
		--iter;
		ans.push_back({ind,-1 * (*iter).second});		

	}
	sort(ans.begin(),ans.end());

	for(auto it : ans)
		cout << it.second << "\n";
	
}
