#include <bits/stdc++.h>
using namespace std;

const int N = 20;

int n, k, c[N], p[N], par[N];
int ans, cnt[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		cin >> par[i], --par[i];
	}
	for (int i = 0; i < n; ++i) cin >> p[i];
	for (int i = 0; i < n; ++i) cin >> c[i];
	
	for (int i = 0; i < (1 << n); ++i) {
		int cost = 0, value = 0;

		for (int j = 0; j < n; ++j) cnt[j] = 0;

		for (int j = n - 1; j >= 0; --j) {
			if (i & 1 << j) {
				++cnt[j];
				cost += c[j];
				value += p[j];
			} else if (cnt[j]) {
				++cost;
			}

			cnt[par[j]] += cnt[j];
		}
		
		if (cost <= k) ans = max(ans, value);
	}
	
	cout << ans << '\n';
	
	return 0;
}
