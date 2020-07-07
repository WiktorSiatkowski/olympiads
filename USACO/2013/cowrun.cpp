#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("cowrun.out");
	ifstream fin ("cowrun.in");
	
	long long n; fin >> n;
	vector<long long> nega, posi;
	
	for(int i = 0; i < n; i++){
		long long x; fin >> x;
		if(x < 0) nega.push_back(x);
		else posi.push_back(x);
	}
	
	if(!nega.empty()) sort(nega.rbegin(),nega.rend());
	if(!posi.empty()) sort(posi.begin(),posi.end());
	
	long long res = (long long)1e18 * (long long)3;	
	
	for(int i = 0; i <= (int)nega.size(); i++){
		long long prev = 0;
		long long ile = 0;
		long long locres = 0;
		for(int j = 0; j < i; j++){
			locres += (long long)abs(nega[j] - prev) * (n-ile);
			prev = nega[j];
			ile++;
		}
		for(int j = 0; j < (int)posi.size(); j++){
			locres += (long long)abs(posi[j] - prev) * (n-ile);
			prev = posi[j];
			ile++;
		}
		for(int j = i; j < (int)nega.size(); j++){
			locres += (long long)abs(nega[j] - prev) * (n-ile);
			prev = nega[j];
			ile++;
		}
		
		res = min(res,locres);
	}
	
	vector<long long> tmp = posi;
	posi = nega;
	nega = tmp;
	
	for(int i = 0; i <= (int)nega.size(); i++){
		long long prev = 0;
		long long ile = 0;
		long long locres = 0;
		for(int j = 0; j < i; j++){
			locres += (long long)abs(nega[j] - prev) * (n-ile);
			prev = nega[j];
			ile++;
		}
		for(int j = 0; j < (int)posi.size(); j++){
			locres += (long long)abs(posi[j] - prev) * (n-ile);
			prev = posi[j];
			ile++;
		}
		for(int j = i; j < (int)nega.size(); j++){
			locres += (long long)abs(nega[j] - prev) * (n-ile);
			prev = nega[j];
			ile++;
		}
		
		res = min(res,locres);
	}
	
	fout << res;
	
	
	return 0;
}
