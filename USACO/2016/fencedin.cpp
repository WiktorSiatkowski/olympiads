#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

ll A,B,n,m;

int main() {
	ofstream fout ("fencedin.out");
	ifstream fin ("fencedin.in");

	fin >> A >> B >> n >> m;
	vector<ll> tab1(n),tab2(m);
	
	for(int i = 0; i < n; i++) fin >> tab1[i];
	for(int i = 0; i < m; i++) fin >> tab2[i];
	
	sort(tab1.begin(),tab1.end());
	sort(tab2.begin(),tab2.end());
	
	ll musze = n*m + n + m;
	vector<pair<pair<ll,ll>,ll> > krawedzie;
	ll prev = 0;
	for(int i = 0; i < n; i++){
		krawedzie.push_back({{tab1[i] - prev,m},1});
		prev = tab1[i];
	}
	krawedzie.push_back({{A - prev,m},1});
	prev = 0;
	for(int i = 0; i < m; i++){
		krawedzie.push_back({{tab2[i] - prev,n},2});
		prev = tab2[i];
	}
	krawedzie.push_back({{B - prev,n},2});
	sort(krawedzie.begin(),krawedzie.end());

	ll piony = 0, poziomy = 0, res = 0;
	for(auto it : krawedzie){
		if(it.ND == 1){
			int odejmij = 0;
			if(piony) odejmij = max(0ll,poziomy-1);
			if(musze >= it.ST.ND - odejmij){
				res += (it.ST.ND - odejmij) * it.ST.ST;
				musze -= (it.ST.ND - odejmij);
			} else {
				res += it.ST.ST * musze;
				break;				
			}
			piony++;
		} else {
			int odejmij = 0;
			if(poziomy) odejmij = max(0ll,piony-1);
			if(musze >= it.ST.ND - odejmij){
				res += (it.ST.ND - odejmij) * it.ST.ST;
				musze -= (it.ST.ND - odejmij);
			} else {
				res += it.ST.ST * musze;
				break;				
			}
			poziomy++;
		}	
	}
	
	fout << res;

	return 0;

}
