#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 3e5;
int n,res;
int tab[SIZE];
vector<int> tabelka;

void solve(vector<int>& wiktor, int x){
	if(x > 60) return;
	//cout << endl;
	//cout << wiktor.size() << " " << x << endl;
	//for(auto it : wiktor) cout << it << " ";
	//cout << endl << endl;
	for(auto it : wiktor) res = max(res,it);
	if(wiktor.size() <= 1) return;
	vector<int> tmp;
	vector<pair<int,int> > storage;
	int co = -1, ile = 0;
	storage.push_back({-1,0});
	for(int i = 0; i < wiktor.size(); i++){
		if(wiktor[i] != co){
			if(co == x && ile % 2 == 1) storage.push_back({i - ile, ile});
			co = wiktor[i];
			ile = 1;
		} else {
			ile++;
		}
	}
	if(co == x && ile % 2 == 1) storage.push_back({wiktor.size() - ile, ile});
	storage.push_back({wiktor.size(),0});
	for(int i = 0; i + 1 < storage.size(); i++){
		for(int j = 1; j <= storage[i].ND/2; j++) tmp.push_back(x+1);
		for(int j = storage[i].ST + max(storage[i].ND,1); j <= storage[i+1].ST - 1; j++){
			if(wiktor[j] != x){
				//if(wiktor[j] == 0) cout << "XD " << j << endl;
				tmp.push_back(wiktor[j]);
			} else {
				j++;
				tmp.push_back(x+1);
			}
		}
		for(int j = 1; j <= storage[i+1].ND/2; j++) tmp.push_back(x+1);
		solve(tmp,x+1);
		tmp.clear();
	}
}

int main() {
	ofstream fout ("262144.out");
	ifstream fin ("262144.in");

	fin >> n;
	for(int i = 1; i <= n; i++) fin >> tab[i];

	for(int i = 1; i <= n; i++) tabelka.push_back(tab[i]);

	solve(tabelka,1);

	fout << res;



    return 0;
}
