#include<bits/stdc++.h>
using namespace std;

int main(){
	ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
	string text2,pattern; cin >> pattern >> text2;
	string text = pattern;
	text += '#';
	text += text2;
	vector<int> pi(text.size());
	pi[0] = -1;
	for(int i = 1; i < text.size(); i++){

		pi[i] = pi[i-1];
		while(pi[i] != -1 && text[pi[i]+1] != text[i]) 
			pi[i] = pi[pi[i]];
		
		if(text[pi[i]+1] == text[i]) pi[i]++;
		
		if(pi[i] == pattern.size()-1){
			cout << i - pattern.size() << "\n";
		}

	}
}
