#include<bits/stdc++.h>

using namespace std;

const int SIZE = 5e4 + 4;
const int MAX = 1 << 16;
int n,k;

int dp[SIZE]; // how many consecutive concurrent brackets eding at i
int tree[10][2*MAX];
string tab[10];

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

bool cor(int ind, int x, int y){
	if(tab[ind][x] != '(') return false;
	if(query(ind,x,y + 1) - tree[ind][x + MAX] + 1 < 0) return false;
	if(tree[ind][y + MAX] + 1 != tree[ind][x + MAX]) return false;
	return true;
}

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	    
	ofstream fout ("cbs.out");
	ifstream fin ("cbs.in");
	
	fin >> k >> n;
	
	for(int i = 0; i < k; i++)
		fin >> tab[i];
		
	vector<stack<int> > stacks(k);
	
	long long res = 0;
	
	for(int i = 0; i < k; i++){
		if(tab[i][0] == '(') tree[i][MAX] = 1;
		else tree[i][MAX] = -1;
		for(int j = 1; j < n; j++){
			tree[i][j + MAX] = tree[i][j + MAX - 1];
			if(tab[i][j] == '(') tree[i][j + MAX]++;
			else tree[i][j + MAX]--;	
		}
		for(int j = MAX - 1; j > 0; j--)
			tree[i][j] = min(tree[i][2*j],tree[i][2*j+1]);
	}
	
	for(int i = 0; i < n; i++){
		
		bool allending = true;
		bool allcorrect = true;
		int index = 1e9;
		
		for(int j = 0; j < k; j++){
			if(tab[j][i] == '('){
				allending = false;
				stacks[j].push(i);
			} else {
				if(stacks[j].empty()) allcorrect = false;
			 	else {
					index = min(index,stacks[j].top());
					stacks[j].pop();			
				}
			}
			
		}
		
		if(allending && allcorrect){

			bool spokoloko = true;
		
			for(int j = 0; j < k; j++)
				if(!cor(j,index,i))
					spokoloko = false;
					
			if(spokoloko){
				dp[i] = wezsobie(index-1) + 1;
				res += dp[i];		
			}
			
		}
		
	}	
	
	fout << res;	
    
    return 0;
}
