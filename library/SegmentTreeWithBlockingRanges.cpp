const int MAX = 1 << 21;

int blokady[2*MAX];
int ilezab[2*MAX];

void blokuj(int a, int b, int u, int lo, int hi, int v){
	if(a == lo && b == hi){
		blokady[u] += v;
		return;
	}
	if(b <= a) return;
	int mid = (lo+hi)/2;
	blokuj(a,min(b,mid),2*u,lo,mid,v);
	blokuj(max(a,mid),b,2*u+1,mid,hi,v);

	ilezab[u] = 0;	
	
	if(blokady[2*u] != 0) ilezab[u] += mid - lo;
	else ilezab[u] += ilezab[2*u];
	
	if(blokady[2*u+1] != 0) ilezab[u] += mid - lo;
	else ilezab[u] += ilezab[2*u+1];
}

int query(int a, int b, int u, int lo, int hi){
	if(a == lo && b == hi){
		if(blokady[u] != 0) return (hi-lo);
		else return ilezab[u];
	}
	if(b <= a) return 0;
	int mid = (lo + hi)/2;
	intl = query(a,min(b,mid),2*u,lo,mid);
	intr = query(max(a,mid),b,2*u+1,mid,hi);
	return l + r;
}
