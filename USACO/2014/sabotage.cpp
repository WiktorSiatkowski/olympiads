#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

const int SIZE = 1e5 + 4;

int n;
double tab[SIZE];
double sum = 0;

double rd3(double x){
	int tmp = x * 1000;
	if((int)(x * 10000) % 10 >= 5){
		tmp++;
	}
	return (double)tmp/(double)1000;
}

bool check(double x){
	sum -= x * n;
	for(int i = 0; i < n; i++) tab[i] -= x;
	double suma = 0;
	double res = -1e5;
	int startt = -1;
	for(int i = 1; i + 1 < n; i++){
		suma += tab[i];
		res = max(res,suma);
		if(suma < 0){
			suma = 0;
		}
	}
	if(sum - res <= 0){
		sum += x * n;
		for(int i = 0; i < n; i++) tab[i] += x;
		return false;	
	} else {
		sum += x * n;
		for(int i = 0; i < n; i++) tab[i] += x;
		return true;
	}
}

int main() {
	ofstream fout ("sabotage.out");
	ifstream fin ("sabotage.in");

	fin >> n;
	
	for(int i = 0; i < n; i++){
		fin >> tab[i];
		sum += tab[i];
	}
	
	double l = 1, r = 10002;
	while(l + 0.00001 < r){
		double mid = (l+r)/2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	
	fout << fixed << setprecision(3) << rd3(l);

    return 0;
}
