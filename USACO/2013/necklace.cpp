#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

string s,pat;

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("necklace.out");
	ifstream fin ("necklace.in");

	fin >> s >> pat;
	
	string pom = pat + '#' + s;
	
	vector<string> parts;
	
	string cur = string(1,pat[0]);
	for(int i = 1; i < (int)pat.size(); i++){
		if(pat[i] != cur.back()){
			parts.push_back(cur);
			cur = string(1,pat[i]);
		} else {
			cur.push_back(pat[i]);
		}
	}
	
	parts.push_back(cur);
	
	//cout << parts.size() << "\n";
	//for(auto it : parts) cout << it << "\n";
	
	if(parts.size() == 1){
		assert(false);
	} else if(parts.size() == 2){
		assert(false);
	} else {
		vector<int> pi((int)pom.size());
		pi[0] = -1;
		
		vector<pair<int,int> > events;
		
		for(int i = 1; i < pom.size(); i++){
			pi[i] = pi[i-1];
			while(pi[i] != -1 && pom[i] != pom[pi[i]+1]) pi[i] = pi[pi[i]];
			if(pom[i] == pom[pi[i]+1]) pi[i]++;
			if(pi[i] + 1 == (int)pat.size()){
				events.push_back({i - 2 * (int)pat.size(),1});
				events.push_back({i - (int)pat.size(),-1});
			}	
		}
		
		sort(events.begin(),events.end());
		
		int ind = 0, licz = 0, res = 0, licz2 = 0;
		
		vector<int> status((int)s.size());
		
		for(int i = 0; i < (int)s.size(); i++){
			while(ind < (int)events.size() && events[ind].ST == i){
				licz += events[ind].ND;
				ind++;
			} 
			if(licz > 0){
				licz2++;		
			} else {
				res += licz2 / (int)pat.size();
				licz2 = 0;
			}
		}
		
		res += licz2 / (int)pat.size();
		
		fout << res;
	
	}
		
	return 0;
}
