#include<bits/stdc++.h>
#define ST first
#define ND second
using namespace std;

int n,k,x,res = 1e9;

vector<int> poziom, pion;

const int SIZE = 16;
 
int tab[SIZE][SIZE];
int dp[SIZE][SIZE];
int pref[SIZE][SIZE];

int check(int xd){
	int used = 0;
	int prev = 0;
	for(int i = 1; i <= n; i++){
		int maks = 0;
		int prev2 = 0;
		for(auto it : poziom){
			maks = max(maks,pref[it-1][i] - pref[prev2][i] - pref[it-1][prev] + pref[prev2][prev]);
			prev2 = it-1;
		}
		//cout << i << " " << maks << " " << prev << endl;
		if(maks > xd){
			if(i - 1 == prev){
				used = 1e9;
				break;
			} else {
				used++;
				prev = i-1;
			}
		}
		
		maks = 0;
		prev2 = 0;
		for(auto it : poziom){
			maks = max(maks,pref[it-1][i] - pref[prev2][i] - pref[it-1][prev] + pref[prev2][prev]);
			prev2 = it-1;
		}
		
		if(maks > xd){
			if(i - 1 <= prev){
				used = 1e9;
				break;
			}
		}
		
	}
	return used;
}

void gopion(){
	int l = -1, r = 15 * 15 * 1001;
	while(l + 1 < r){
		int mid = (l+r)/2;
		if(check(mid) <= k - x) r = mid;
		else l = mid;
	}
	//cout << r << endl;
	res = min(res,r);
}

void gopoziom(int prev, int ile){
	if(ile == 0){
		//for(auto it : poziom) cout << it << " ";
		//cout << endl;
		poziom.push_back(n+1);
		gopion();
		poziom.pop_back();
		return;
	}
	for(int i = prev + 1; i <= n; i++){
		poziom.push_back(i);
		gopoziom(i,ile-1);
		poziom.pop_back();
	} 
}


int main() {
	//cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("partition.out");
	ifstream fin ("partition.in");

	fin >> n >> k;

	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			fin >> tab[i][j];
			
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + tab[i][j];
	
	//poziom.push_back(4);
	//poziom.push_back(n+1);
	//x = 1;
	//cout << check(33) << endl;
	//gopion();
	
	//return 0;
	
	for(int i = 0; i <= min(k,n-1); i++){
		x = i;
		gopoziom(1,i);
	}
	
	fout << res;
	
	return 0;
}
