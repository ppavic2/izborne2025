#include <bits/stdc++.h>

#define X first
#define Y second
#define PB push_back

using namespace std;

typedef vector<int> vi;

const int N = 3e5 + 500;

int n, q, naj_dub[N], dep[N];
int max_dep = 0, daleko[N];
vi v[N];

void dfs(int x, int lst) {
	naj_dub[x] = 0;
	for(int y : v[x]) {
		if(y == lst) continue;	
		dep[y] = dep[x] + 1;
		dfs(y, x);
		naj_dub[x] = max(naj_dub[y] + 1, naj_dub[x]);
	}
	max_dep = max(max_dep, dep[x]);
	daleko[naj_dub[x]]++;
}

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1;i < n;i++) {
		int a, b; scanf("%d%d", &a, &b);
		v[a].PB(b), v[b].PB(a);
	}
	dfs(1, 1);
	for(int i = n - 1;i >= 0;i--) daleko[i] += daleko[i + 1];
	for(;q--;) {
		int k; scanf("%d", &k);
		printf("%d ", 2 * (n - 1) + 2 * max(0, daleko[k] - 1) - max_dep);
	}
	printf("\n");
	return 0;
}
