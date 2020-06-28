#include<bits/stdc++.h>

using namespace std;

const int SIZE = 3e5 + 5;
const int MAX = 1 << 18;
int n,k;
int tab[SIZE], tr[2*MAX];
vector<int> enumerate;
set<int> secior;
int maks = 0;

void update(int x, int val){
	x += MAX;
	tr[x] += val;
	while(x /= 2)
		tr[x] = max(tr[2*x],tr[2*x+1]);
}

int getind(int x){
	return lower_bound(enumerate.begin(),enumerate.end(),x) - enumerate.begin();
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("lineup.out");
	ifstream fin ("lineup.in");

	fin >> n >> k;
    
    for(int i = 0; i < n; i++){
    	fin >> tab[i];
    	enumerate.push_back(tab[i]);
    }
    
    sort(enumerate.begin(),enumerate.end());
    
    for(int i = 0; i < n; i++)
    	tab[i] = getind(tab[i]);

	int l = 0, r = 0;
	while(l != n || r != n){
		while(r < n && (int)secior.size() - 1 <= k){
			secior.insert(tab[r]);
			update(tab[r],1);
			maks = max(maks,tr[1]);
			r++;
		}
		if(tr[tab[l] + MAX] == 1) secior.erase(tab[l]);
		update(tab[l],-1);
		l++;
	}
	
	fout << maks;
    return 0;
}
