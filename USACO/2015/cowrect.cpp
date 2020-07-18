#include<bits/stdc++.h>
#define ll long long
#define ST first
#define ND second
using namespace std;

int n;
const int SIZE = 1e3 + 3;

struct pt{
	ll x,y;
	char type;
	pt(ll a = 0, ll b = 0,ll c = '-'){
		x = a, y = b, type = c; 
	}
};

bool mam[SIZE];

int main() {
	ofstream fout ("cowrect.out");
	ifstream fin ("cowrect.in");

	int n; fin >> n;
	vector<pt> points(n);
	
	vector<ll> igreki;
	
	for(int i = 0; i < n; i++){
		ll a,b; fin >> a >> b;
		char c; fin >> c;
		points[i] = pt(a,b,c);
		if(!mam[b]){
			mam[b] = 1;
			igreki.push_back(b);
		}
	}
	
	sort(igreki.begin(),igreki.end());
	sort(points.begin(),points.end(),[](pt a, pt b){
		return a.x < b.x;
	});
	
	int res = 0;
	ll minarea = 1e9;
	ll leftx = -1;
	ll miny = 1e9;
	ll maxy = -1e9;
	ll cur = 0;
	
	for(int i = 0; i < (int)igreki.size(); i++){
		for(int j = i; j < (int)igreki.size(); j++){
			cur = 0;
			leftx = -1;
			miny = 1e9;
			maxy = -1e9;
			for(int k = 0; k < points.size(); k++){
				auto it = points[k];
				if(it.y < igreki[i] || it.y > igreki[j]) continue;
				vector<pt> tmp;
				tmp.push_back(it);
				while(k < points.size() && points[k+1].x == it.x){
					k++;
					if(points[k].y >= igreki[i] && points[k].y <= igreki[j]) tmp.push_back(points[k]);
				}
				bool ok = true;
				for(auto iter : tmp) if(iter.type == 'G') ok = false;
				if(ok){
					for(auto iter : tmp){
						if(leftx == -1) leftx = iter.x;
						miny = min(miny,iter.y);
						maxy = max(maxy,iter.y);
						cur++;
						ll curarea = (iter.x - leftx) * (maxy - miny);
						if(cur > res){
							res = cur;
							minarea = curarea;
						} else if(cur == res && curarea < minarea){
							minarea = curarea;
						}
					}
				} else {
					cur = 0;
					leftx = -1;
					miny = 1e9;
					maxy = -1e9;
				}
			}			
		}
	}
	
	if(res == 1) minarea = 0;
	
	fout << res << "\n";
	fout << minarea << "\n";
	

    return 0;
}
