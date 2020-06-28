#include<iostream>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<map>

using namespace std;
using namespace __gnu_pbds;

typedef tree<pair<int, int>, null_type, greater<pair<int, int> >, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set secik;
map<int, int> m;
int queries, x,t=0;

int main() {
	cin.tie(0);
	cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin >> queries;
    for(int i = 0; i < queries; i++) {
        string s; 
        cin >> s; 
        cin >> x;
        if(s == "add") 
            secik.insert({x, t++});
          else if(s == "remove") 
            secik.erase(secik.lower_bound({x,-1}));
          else if(s == "query")
            cout << (*secik.find_by_order(x)).first << "\n";
        
    }
	cout << (*secik.find_by_order(0)).first;
}
