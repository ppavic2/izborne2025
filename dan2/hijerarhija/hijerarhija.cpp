#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int n, k, c[N], p[N], dp[N][N];
vector<int> adj[N];

void dfs(int node) {
	for (int x : adj[node]) {
		for (int i = 0; i < k; ++i) {
			dp[x][i] = dp[node][i + 1];
			if (i + c[x] < k) {
				dp[x][i] = max(dp[node][i + 1], dp[node][i + c[x]] + p[x]);
			}
		}
		dfs(x);
		for (int i = 0; i < k; ++i) {
			dp[node][i] = max(dp[node][i], dp[x][i]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int par;
		cin >> par, --par;
		adj[par].push_back(i);
	}
	for (int i = 0; i < n; ++i) cin >> p[i];
	for (int i = 0; i < n; ++i) cin >> c[i];

	for (int i = 0; i < n; ++i) dp[i][k] = -1e9;
	for (int i = 0; i <= k - c[0]; ++i) dp[0][i] = p[0];

	dfs(0);

	cout << dp[0][0] << '\n';

	return 0;
}
