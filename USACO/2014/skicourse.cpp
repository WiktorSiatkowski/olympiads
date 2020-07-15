#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 103;
int n,m;
char tab[SIZE][SIZE];
bool tmp[SIZE][SIZE];
int pref1[SIZE][SIZE], pref2[SIZE][SIZE];

bool covered(){
	return (pref1[n][m] + pref2[n][m] == 0);
}

bool pos(int x){
	bool same = true;
	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			tmp[i][j] = 0;
			pref1[i][j] = pref1[i-1][j] + pref1[i][j-1] - pref1[i-1][j-1];
			pref2[i][j] = pref2[i-1][j] + pref2[i][j-1] - pref2[i-1][j-1];
			if(!tmp[i][j]){
				if(tab[i][j] == 'R') pref1[i][j]++;
				else pref2[i][j]++;
			}
		}
	
	while(!covered()){
		pair<int,int> goo = {-1,-1};
		for(int i = 1; i + x - 1 <= n; i++){
			for(int j = 1; j + x - 1 <= m; j++){
				int a = pref1[i+x-1][j+x-1] - pref1[i+x-1][j-1] - pref1[i-1][j+x-1] + pref1[i-1][j-1];
				int b = pref2[i+x-1][j+x-1] - pref2[i+x-1][j-1] - pref2[i-1][j+x-1] + pref2[i-1][j-1];
				if(a == 0 && b == 0) continue;
				if(a == 0 || b == 0){
					goo = {i,j};
					break;					
				}
			}
		}
		
		if(goo == make_pair(-1,-1)){
			same = false;
			break;
		}
		
		for(int i = goo.ST; i <= goo.ST + x - 1; i++)
			for(int j = goo.ND; j <= goo.ND + x - 1; j++)
				tmp[i][j] = 1;
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++){
				pref1[i][j] = pref1[i-1][j] + pref1[i][j-1] - pref1[i-1][j-1];
				pref2[i][j] = pref2[i-1][j] + pref2[i][j-1] - pref2[i-1][j-1];
				if(!tmp[i][j]){
					if(tab[i][j] == 'R') pref1[i][j]++;
					else pref2[i][j]++;
				}
			}
		
	}
	return same;
}

int main() {
	ofstream fout ("skicourse.out");
	ifstream fin ("skicourse.in");

	fin >> n >> m;
	
	for(int i = 1; i <= n; i++){
		string s; fin >> s;
		for(int j = 1; j <= m; j++)
			tab[i][j] = s[j-1];
	}
		
	int l = 1, r = min(n,m)+1;
	while(l + 1 < r){
		int mid = (l+r)/2;
		if(pos(mid)) l = mid;
		else r = mid;
	}
	
	fout << l;
	
    return 0;
}
