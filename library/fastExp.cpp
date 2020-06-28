#include<bits/stdc++.h>
using namespace std;
long long fastExp(long long a, long long b){
	if(!b) return 1;
	if(b % 2) return (a * fastExp(a,b-1))%MOD;
	long long x = fastExp(a,b/2);
	return (x*x)%MOD;
}

int main(){
	
}
