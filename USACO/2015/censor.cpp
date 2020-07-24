#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int kutas = 0;

struct ahocorasick {
	vector<vector<int>> next;
	vector<int> fail,cnt;
	map<pair<int,int>,int> mapa;
	
	ahocorasick () {
		next.push_back(vector<int>(26));
		cnt.push_back(0);
	}
	void insert (string &s) {
		int u = 0;
		for (int i = 0; i < s.size(); ++i) {
			int c = s[i] - 'a';
			if (!next[u][c]) {
				next[u][c] = next.size();
				next.push_back(vector<int>(26));
				cnt.push_back(0);
			}
			u = next[u][c];
		}
		cnt[u] = s.size();
	}
	int get_fail (int pfail, int c) {
		int tmp = pfail;
		if(mapa.find({pfail,c}) == mapa.end()){
			while (!next[pfail][c] && pfail != 0)
				pfail = fail[pfail];
			mapa[{tmp,c}] = next[pfail][c];
		}
		return mapa[{tmp,c}];
	}
	void buildf () {
		queue<int> q;
		fail.assign(next.size(), 0);
		for (int i = 0; i < 26; ++i)
			if(next[0][i]) q.push(next[0][i]);
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (int i = 0; i < 26; ++i) {
				int v = next[u][i];
				if (v) {
					fail[v] = get_fail(fail[u], i);
					q.push(v);
				}
			}
		}
	}
	string match (string &s) {
		int cur = 0;
		vector<int> states;
		string res = "";
		for (int i = 0; i < s.size(); ++i) {
			res += s[i];
			int c = s[i] - 'a';
			if (next[cur][c]) cur = next[cur][c];
            else cur = get_fail(fail[cur], c);
			states.push_back(cur);
			if(cnt[cur]){
				int xd = cnt[cur];
				for(int j = 1; j <= xd; j++){
					res.pop_back();
					states.pop_back();
				}
			}
			cur = states.back();
		}
		return res;
	}
};




int main() {
	ofstream fout ("censor.out");
	ifstream fin ("censor.in");

	ahocorasick aho;
	string text; fin >> text;
	int t; fin >> t;
	while(t--){
		string s; fin >> s;
		aho.insert(s);
	}
	aho.buildf();
	fout << aho.match(text);
	
    return 0;
}
