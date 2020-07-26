#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int n;

int main() {
	//ofstream fout ("cardgame.out");
	//ifstream fin ("cardgame.in");

	cin >> n;

	vector<int> tab(n+1);
	vector<bool> vis(2*n+1);

	for(int i = 1; i <= n; i++){
		cin >> tab[i];
		vis[tab[i]] = 1;
	}
	
	int res = 0;
	vector<int> tab2;
	
	for(int i = 1; i <= 2 * n; i++)
		if(!vis[i])
			tab2.push_back(i);
			
	sort(tab2.rbegin(),tab2.rend());
	
	set<int> secior;
	
	
	
    return 0;
}
