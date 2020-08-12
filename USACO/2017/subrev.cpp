#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ST first
#define ND second
using namespace std;

const int SIZE = 51;
const int INF = 1e9 + 69;

int tab[SIZE];
int dp[SIZE][SIZE][SIZE][SIZE];

int main() {
	ofstream fout ("subrev.out");
	ifstream fin ("subrev.in");

	for(int a = 0; a < SIZE; a++)
		for(int b = 0; b < SIZE; b++)
			for(int c = 0; c < SIZE; c++)
				for(int d = 0; d < SIZE; d++)
					if(a > b)
						dp[a][b][c][d] = -INF;
					else
						dp[a][b][c][d] = 0;

	int n; fin >> n;
	for(int i = 1; i <= n; i++){
		fin >> tab[i];
		dp[i][i][tab[i]][tab[i]] = 1;
	}
	
	int ans = 0;
	
	for(int length = 1; length <= n - 1; length++){
		for(int i = 1; i + length <= n; i++){
			int j = i + length;
			for(int k = 1; k < SIZE; k++){
				for(int l = k; l < SIZE; l++){
					dp[i][j][k][l] = max(dp[i+1][j][k][l],dp[i][j-1][k][l]);
					
					// running time amortizes to O(n^4) :)
					
					// dont swap
					if(tab[i] == k && tab[j] == l){
						dp[i][j][k][l] = max(dp[i][j][k][l],2);
						for(int m1 = k; m1 <= l; m1++)
							for(int m2 = m1; m2 <= l; m2++)
								dp[i][j][k][l] = max(dp[i][j][k][l], 2 + dp[i+1][j-1][m1][m2]);
					} else if(tab[i] == k){
						dp[i][j][k][l] = max(dp[i][j][k][l],1);
						for(int m = k; m <= l; m++) dp[i][j][k][l] = max(dp[i][j][k][l],1 + dp[i+1][j][m][l]);
					} else if(tab[j] == l){
						dp[i][j][k][l] = max(dp[i][j][k][l],1);
						for(int m = k; m <= l; m++) dp[i][j][k][l] = max(dp[i][j][k][l],1 + dp[i][j-1][k][m]);
					}
					
					// swap
					if(tab[j] == k && tab[i] == l){
						dp[i][j][k][l] = max(dp[i][j][k][l],2);
						for(int m1 = k; m1 <= l; m1++)
							for(int m2 = m1; m2 <= l; m2++)
								dp[i][j][k][l] = max(dp[i][j][k][l], 2 + dp[i+1][j-1][m1][m2]);
					} else if(tab[j] == k){
						dp[i][j][k][l] = max(dp[i][j][k][l],1);
						for(int m = k; m <= l; m++) dp[i][j][k][l] = max(dp[i][j][k][l],1 + dp[i+1][j-1][m][l]);
					} else if(tab[i] == l){
						dp[i][j][k][l] = max(dp[i][j][k][l],1);
						for(int m = k; m <= l; m++) dp[i][j][k][l] = max(dp[i][j][k][l],1 + dp[i+1][j-1][k][m]);
					}
					
					ans = max(ans,dp[i][j][k][l]);
				}
			}
		}
	}	
	
	fout << ans;
		
    return 0;
}
