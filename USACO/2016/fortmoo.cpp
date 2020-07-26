#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;
const int SIZE = 202;
int n,m;
char tab[SIZE][SIZE];
int pref1[SIZE][SIZE],pref2[SIZE][SIZE];

inline bool check(int x1, int y1, int x2, int y2){
	int trzeba1 = x2 - x1 + 1;
	int trzeba2 = y2 - y1 + 1;
	return (pref1[y1][x2] - pref1[y1][x1-1] == trzeba1 && pref1[y2][x2] - pref1[y2][x1-1] == trzeba1 && 
		pref2[y2][x1] - pref2[y1-1][x1] == trzeba2 && pref2[y2][x2] - pref2[y1-1][x2] == trzeba2);
}	

int main() {
	ofstream fout ("fortmoo.out");
	ifstream fin ("fortmoo.in");

	fin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			fin >> tab[i][j];

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			pref1[i][j] = pref1[i][j-1];
			if(tab[i][j] == '.') pref1[i][j]++;
		}
	}
	
	for(int j = 1; j <= m; j++){
		for(int i = 1; i <= n; i++){
			pref2[i][j] = pref2[i-1][j];
			if(tab[i][j] == '.') pref2[i][j]++;
		}
	}
	
	int res = 0;
	
	for(int dl = 1; dl <= m; dl++){
		for(int x1 = 1; x1 + dl - 1 <= m; x1++){
			int last = 1e9;
			for(int y1 = 1; y1 <= n; y1++){
				if(pref1[y1][x1+dl-1] - pref1[y1][x1-1] == dl){
					res = max(res,dl);
					if(last != 1e9){
						if(check(x1,last,x1+dl-1,y1)) res = max(res,(y1 - last + 1) * dl);
						else last = y1;
					} else {
						last = y1;
					}
				}
			}
		}
	}
	
	fout << res;

    return 0;
}
