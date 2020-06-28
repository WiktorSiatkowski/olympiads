#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define turbo ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
const int MOD = 1e9 + 7;

ll a,b,m,k1,k2,n;

void multiply(ll a[3][3], ll b[3][3]) { 
    ll mul[3][3]; 
    for (int i = 0; i < 3; i++){ 
        for (int j = 0; j < 3; j++){ 
            mul[i][j] = 0; 
            for (int k = 0; k < 3; k++) 
                mul[i][j] = (mul[i][j] + a[i][k]*b[k][j])%MOD; 
        } 
    } 
    for (int i=0; i<3; i++) 
        for (int j=0; j<3; j++) 
            a[i][j] = mul[i][j];
} 

void power(ll n, ll M1[3][3], ll M2[3][3]) { 
    if (n==1) 
        return ; 
    power(n/2,M1,M2); 
    multiply(M1, M1); 
    if (n%2 != 0) 
        multiply(M1, M2); 
} 

int main(){
	turbo;
	cin >> n >> a >> b >> m >> k1 >> k2;
	ll M1[3][3] = { {m, -1, -1}, {0, k1, k2, 0}, {0, 1, 0, 0}, {0, 0, 1, 1} };
	ll M2[3][3] = { {m, -1, -1, -1}, {0, k1, k2, 0}, {0, 1, 0, 0}, {0, 0, 1, 1} };
	power(n,M1,M2);
	ll ans = ((M1[0][0]*a)%MOD + (M1[0][1]*b)%MOD)%MOD;
	cout << (ans+MOD)%MOD;;
}
