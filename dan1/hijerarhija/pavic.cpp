#include <cstdio>
#include <vector>

using namespace std;

typedef vector<int> vi;

const int N = 5050;
const int INF = 0x3f3f3f3f;

int cur[2 * N], dp[N][N], n, k;
int p[N], c[N], par[N];
vi v[N];

void dfs(int x, int off) {
	for(int t = c[x];t <= k;t++) {
		dp[x][t] = cur[off + t - c[x]] + p[x];
	}
	cur[--off] = -INF;
	vi old(k + 1);
	for(int t = 0;t <= k;t++) {
		old[t] = cur[off + t];
		cur[off + t] = max(cur[off + t], dp[x][t]);	
	}
	for(int y : v[x]) {
		dfs(y, off);
	}
	for(int t = 0;t <= k;t++)
		cur[off + t] = old[t];
	off++;
	for(int t = 0;t <= k;t++) {
		dp[par[x]][t] = max(dp[par[x]][t], dp[x][t]);
		cur[off + t] = max(cur[off + t], dp[x][t]);
	}
}

int main() {
	scanf("%d%d", &n, &k);	
	for(int i = 1;i <= n;i++)
		for(int j = 0;j <= k;j++)
			dp[i][j] = -INF;
	for(int i = 2;i <= n;i++) scanf("%d", par + i), v[par[i]].push_back(i);
	for(int i = 1;i <= n;i++) scanf("%d", p + i);
	for(int i = 1;i <= n;i++) scanf("%d", c + i);
	for(int i = 0;i < 2 * N;i++) cur[i] = -INF;
	for(int i = 0;i <= k;i++) cur[n + i] = 0;
	dfs(1, n);
	printf("%d\n", dp[1][k]);
	return 0;
}
