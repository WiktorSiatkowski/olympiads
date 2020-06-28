#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int SIZE = 7100;
const ll INF = 10e12;

ll n,m;
vector<pair<int,int> > adj[SIZE];
priority_queue<pair<ll,int> > q;
ll dis[SIZE];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i <= n; i++)
        dis[i] = INF;
    for(int i = 0; i < m; i++){
        int x,y,z; cin >> x >> y >> z;
        adj[x].push_back(make_pair(y,z));
    }
    dis[1] = 0;
    q.push(make_pair(0,1));
    while(!q.empty()){
        auto p = q.top();
        p.first = -p.first;
        q.pop();
        if(p.first > dis[p.second])
        	continue;
        for(auto it : adj[p.second]){
            if(p.first + it.second < dis[it.first]){
                dis[it.first] = p.first + it.second;
                q.push(make_pair(-dis[it.first],it.first));
            }
        }
    }
    
}
