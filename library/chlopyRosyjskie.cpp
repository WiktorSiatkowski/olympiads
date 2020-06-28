long long chlopyRosyjskie(long long a,long long b){
	ll res = 0ll;
	while(b){
		if(b % 2 == 1ll)
	      res = (res + a) % M;
	    b /= 2ll;
	    a = (2ll * a) % M;
 	}
 	return res;
}
