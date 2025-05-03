#include <bits/stdc++.h>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int N = 2e5 + 500;
const int OFF = (1 << 18);

int L[N], R[N], lft[N], rht[N], par[N], value[N], priority[N];

void rotate(int x) {
	printf("rotate %d\n", x);
	int p = par[x];
	if(x < p) {
		L[p] = R[x]; lft[p] = p;
		R[x] = p;
		rht[x] = rht[p];
		if(L[p] != -1) {
			par[L[p]] = p;
		    lft[p] = lft[L[p]];
		}
	} else {
		R[p] = L[x]; rht[p] = p;
		L[x] = p;
		lft[x] = lft[p];
		if(R[p] != -1) {
			par[R[p]] = p;
			rht[p] = rht[R[p]];
		}
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
ll ans[N];

int query(int i, int a, int b, int lo, int hi) {
	if(lo <= a && b <= hi) return T[i];
	if(a > hi || b < lo) return n;
	return maax(query(2 * i, a, (a + b) / 2, lo, hi), query(2 * i + 1, (a + b) / 2 + 1, b, lo, hi));
}


void dodaj(int L, int R, int x = 1) {
	for(int i = 1;i <= R + L + 1;i++)
		ans[i] += x * min(min(R + L + 2 - i, i), min(R, L) + 1);
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
		priority[i] = rand(), T[OFF + i] = i;
		scanf("%d", value + i);
	}
	for(int i = OFF - 1; i ; i--) 
		T[i] = maax(T[2 * i], T[2 * i + 1]);
	par[build_cartesian_tree(0, n - 1)] = -1;
	for(;q--;) {
		char ty; scanf(" %c", &ty);
		if(ty == '?') {
			int k; scanf("%d", &k);
			printf("%lld\n", ans[k]);
		} else {
			for(int i = 0;i < n;i++) printf("%2d ", value[i]);
			printf("\n");
			for(int i = 0;i < n;i++) printf("%2d ", i);
			printf("\n");
			for(int i = 0;i < n;i++) printf("%2d ", par[i]);
			printf("\n");
			for(int i = 0;i < n;i++) printf("%2d ", L[i]);
			printf("\n");
			for(int i = 0;i < n;i++) printf("%2d ", R[i]);
			printf("\n");
			int x; scanf("%d", &x); x--;
			printf("value[ %d ] ( = %d ) += 1\n", x + 1, value[x]);
			pii interval = increment(x);
			printf("%d %d\n", interval.X + 1, interval.Y + 1);
			dodaj(x - interval.X, interval.Y - x);
		}
	}
	return 0;
}
