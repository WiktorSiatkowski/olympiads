#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 505;

ll tab[SIZE];
ll sum = 0;
ll n;

bool check(int ind){
	if((sum - tab[ind]) % 2 == 1) return false;
	if((sum - tab[ind]) > 2 * (n * (n-1))/2) return false;
	
	vector<ll> tmp;
	
	bool ok = true;

	for(int i = 1; i <= n + 1; i++){
		if(i == ind) continue;
		if(tab[i] == 0) continue;
		if(tab[i] >= n) return false;
		tmp.push_back(tab[i]);
	}
	
	sort(tmp.begin(),tmp.end());
	
	
	for(int i = (int)tmp.size() - 1; i >= 0; i--){
		if(tmp[i] == 0) break;
		//for(auto it : tmp) cout << it << " ";
		//cout << endl;
		if(tmp[i] > i || tmp[i-tmp[i]] == 0){
			ok = false;
			break;
		}
		int fajnie = tmp[i-tmp[i]];
		int licz = 0;
		for(int j = i - tmp[i]; j < i; j++)
			if(tmp[j] == fajnie) licz++;
			
		for(int j = 0; j < i; j++){
			if(tmp[j] == fajnie && licz){
				tmp[i]--;
				tmp[j]--;
				licz--;
			} else if(licz == 0 && tmp[j] > fajnie){
				tmp[i]--;
				tmp[j]--;			
			}
		}
		
		if(tmp[i] != 0) assert(false);
	}
	
	for(auto it : tmp) if(it != 0) ok = false;
	
	return ok;
}

int main() {
	ofstream fout ("fcount.out");
	ifstream fin ("fcount.in");

	fin >> n;
	
	for(int i = 1; i <= n + 1; i++){
		fin >> tab[i];
		sum += tab[i];
	}	
	
	vector<int> res;
	
	for(int i = 1; i <= n + 1; i++){
		if(check(i)) 
			res.push_back(i);
	}
	
	fout << res.size() << "\n";
	
	for(auto it : res) fout << it << "\n";

    return 0;
}
