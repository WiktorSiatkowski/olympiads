#include<bits/stdc++.h>

using namespace std;

const int SIZE = 6e4 + 4;
const int MAX = 1 << 17;
int n,k;

int dp[SIZE]; // how many consecutive concurrent brackets eding at i
int tree[10][2*MAX];
string tab[10];
map<vector<int>,int> mapa;

int query(int ind, int x, int y){
	int res = 1e9;
	for(x += MAX, y += MAX; x < y; x >>= 1, y >>= 1){
		if(x&1) res = min(res,tree[ind][x++]);
		if(y&1) res = min(res,tree[ind][--y]);
	}
	return res;
}

int wezsobie(int x){
	if(x < 0) return 0;
	return dp[x];
}

int getit(vector<int>& x){
	auto it = mapa.find(x);
	if(it == mapa.end()) return -1;
	return (*it).second;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("cbs.out");
	ifstream fin ("cbs.in");
	
	fin >> k >> n;
	
	for(int i = 0; i < k; i++)
		fin >> tab[i];
		
	long long res = 0;
	
	for(int i = 0; i < k; i++){
		
		if(tab[i][0] == '(') tree[i][MAX] = 1;
		else tree[i][MAX] = -1;
		
		for(int j = 1; j < n; j++){
			tree[i][j + MAX] = max(tree[i][j + MAX - 1],0);
			if(tab[i][j] == '(') tree[i][j + MAX]++;
			else tree[i][j + MAX]--;	
		}
		
		for(int j = 0; j < n; j++){
			if(tree[i][j + MAX] < 0) tree[i][j + MAX] = -1e9;
		}
		
		for(int j = MAX - 1; j > 0; j--)
			tree[i][j] = min(tree[i][2*j],tree[i][2*j+1]);
	
	}
	
	for(int i = 0; i < n; i++){
		bool allending = true;
		bool allbegin = true;
		bool allok = true;
		vector<int> tmp(k);
		for(int j = 0; j < k; j++){
			if(tab[j][i] == '(') allending = false;
			else allbegin = false;
			tmp[j] = tree[j][i + MAX];
		}
		for(auto it : tmp) if(it == -1e9) allok = false;
		
		if(allbegin){
			mapa[tmp] = i;
		} else if(allok){
			for(int j = 0; j < k; j++)
				tmp[j]++;
			int index = getit(tmp);
			if(index != -1){
				//cout << i << " " << index << " ";
				for(int j = 0; j < k; j++)
					if(query(j,index,i) < tree[j][i+MAX]) allok = false;
				if(allok){
					dp[i] = wezsobie(index-1) + 1;
					res += dp[i]; 
					//cout << dp[i];
				}
				//cout << endl;
			}
		}
	}	
	
	fout << res;	
    
    return 0;
}
