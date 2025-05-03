#include <bits/stdc++.h>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N = 5e5 + 500;
const int OFF = (1 << 19);

int L[N], R[N], lft[N], rht[N], par[N], value[N], priority[N];

void rotate(int x) {
	int p = par[x];
	if(x < p) {
		L[p] = R[x]; lft[p] = p;
		R[x] = p;
		rht[x] = rht[p];
		if(L[p] != -1) par[L[p]] = p, lft[p] = lft[L[p]];
	} else {
		R[p] = L[x]; rht[p] = p;
		L[x] = p;
		lft[x] = lft[p];
		if(R[p] != -1) par[R[p]] = p, rht[p] = rht[R[p]];
	}
	par[x] = par[p];
	if(x < par[x]) L[par[x]] = x;
	else 		   R[par[x]] = x;
	par[p] = x;
}

pii increment(int x) {
	pii ret;
	while(par[x] != -1 
	   && value[x] == value[par[x]]) 
		rotate(x);
	ret = {lft[x], rht[x]};
	value[x]++;
	while(par[x] != -1 
	   && value[x] == value[par[x]] 
	   && priority[par[x]] < priority[x]) 
		rotate(x);
	return ret;
}

int n, q;

int maax(int A, int B) {
	if(A == n || B == n) return A == n ? B : A;
	return pii(value[A], priority[A]) > pii(value[B], priority[B]) ? A : B;
}

int T[2 * OFF];
ll ans[2 * OFF], prop[2 * OFF];

int query(int i, int a, int b, int lo, int hi) {
	if(lo <= a && b <= hi) return T[i];
	if(a > hi || b < lo) return n;
	return maax(query(2 * i, a, (a + b) / 2, lo, hi), query(2 * i + 1, (a + b) / 2 + 1, b, lo, hi));
}

void refresh(int x, int len) {
	if(!prop[x]) return;
	ans[x] += prop[x] * len;
	if(x < OFF) {
		prop[2 * x] += prop[x];
		prop[2 * x + 1] += prop[x];
	}
	prop[x] = 0;
} 

void update(int i, int a, int b, int lo, int hi, int x) {
	if(lo <= a && b <= hi) {
		prop[i] += x;
		refresh(i, b - a + 1);	
		return;
	}
	refresh(i, b - a + 1);
	if(a > hi || b < lo) return;
	update(2 * i, a, (a + b) / 2, lo, hi, x);
	update(2 * i + 1, (a + b) / 2 + 1, b, lo, hi, x);
	ans[i] = ans[2 * i] + ans[2 * i + 1]; 
}

ll query2(int i, int a, int b, int lo, int hi) {
	refresh(i, b - a + 1);
	if(lo <= a && b <= hi) return ans[i];
	if(a > hi || b < lo) return 0LL;
	return query2(2 * i, a, (a + b) / 2, lo, hi) + query2(2 * i + 1, (a + b) / 2 + 1, b, lo, hi);
}

void dodaj(int L, int R, int x = 1) {
	update(1, 0, OFF - 1, 1, min(R, L) + 1, x);
	update(1, 0, OFF - 1, (R + L + 2) - min(R, L), R + L + 2, -x);	
}

int build_cartesian_tree(int l, int r) {
	if(r < l) return -1;
	int mid = query(1, 0, OFF - 1, l, r);
	L[mid] = build_cartesian_tree(l, mid - 1);
	R[mid] = build_cartesian_tree(mid + 1, r);
	lft[mid] = rht[mid] = mid;
	if(L[mid] != -1) {
		par[L[mid]] = mid;
		lft[mid] = lft[L[mid]];
	}
	if(R[mid] != -1) {
		par[R[mid]] = mid;
		rht[mid] = rht[R[mid]];
	}
	dodaj(mid - lft[mid], rht[mid] - mid, value[mid]);
	return mid;
}


int main() {
	scanf("%d%d", &n, &q);
	for(int i = 0;i < n;i++) {
		//priority[i] = rand();
		T[OFF + i] = i;
		scanf("%d", value + i);
	}
	for(int i = OFF - 1; i ; i--) 
		T[i] = maax(T[2 * i], T[2 * i + 1]);
	par[build_cartesian_tree(0, n - 1)] = -1;
	for(;q--;) {
		char ty; scanf(" %c", &ty);
		if(ty == '?') {
			int k; scanf("%d", &k);
			printf("%lld\n", query2(1, 0, OFF - 1, 0, k));
		} else {
			int x; scanf("%d", &x); x--;
			pii interval = increment(x);
			dodaj(x - interval.X, interval.Y - x);
		}
	}
	return 0;
}
