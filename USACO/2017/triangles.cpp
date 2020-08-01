#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 303;
int n;
vector<pair<ll,ll> > tab;
ll underline[SIZE][SIZE];
ll underline2[SIZE][SIZE];
ll res[SIZE];

int position(int a, int b, int c){
	ll difx = tab[b].ST - tab[a].ST;
	ll dify = tab[b].ND - tab[a].ND;
	if(tab[c].ST < tab[a].ST || tab[c].ST > tab[b].ST) return 0;
	if(tab[c].ND * difx > tab[a].ND * difx + (tab[c].ST - tab[a].ST) * dify) return 2;
	return 1;
}

int main() {
	ofstream fout ("triangles.out");
	ifstream fin ("triangles.in");

	fin >> n;
	tab = vector<pair<ll,ll> >(n);
	for(int i = 0; i < n; i++){
		fin >> tab[i].ST >> tab[i].ND;	
	}
	
	sort(tab.begin(),tab.end());
	
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			for(int k = 0; k < n; k++){
				if(k == i || k == j || tab[i].ST == tab[j].ST) continue;
				if(position(i,j,k) == 1) underline[i][j]++;
			}
		}
	}
	
	int chuj = 0;
	
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			for(int k = i + 1; k < j; k++){
				if(k == i || k == j || tab[i].ST == tab[j].ST) continue;
				int xd = position(i,j,k);
				if(xd == 1){
					chuj++;
					int co = underline[i][j];
					co -= underline[i][k];
					co -= underline[k][j];
					co--;
					if(co < 0) cout << underline[i][j] << " " << underline[i][k] << " " << underline[k][j] << endl;
					else res[co]++;
				}
				if(xd == 2){
					chuj++;
					int co = underline[i][j];
					co -= underline[i][k];
					co -= underline[k][j];
					co = -co;
					//if(co < 0) cout << underline[i][j] << " " << underline[i][k] << " " << underline[k][j] << endl;
					//else res[co]++;
				}
			}
		}
	}
	
	for(int i = 0; i <= n - 3; i++)
		fout << res[i] << "\n";
	
    return 0;
    
}
