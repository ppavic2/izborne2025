#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5;

int n, q, a[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> q;

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	while (q--) {
		int t, k;
		cin >> t >> k;
		if (t == 1) {
			--k;
			a[k] += 1;
		} else {
			multiset<int> ms;
			for (int i = 0; i < k; ++i) ms.insert(a[i]);
			ll ans = *--ms.end();
			for (int i = k; i < n; ++i) {
				ms.erase(ms.find(a[i - k]));
				ms.insert(a[i]);
				ans += *--ms.end();
			}
			cout << ans << '\n';
		}
	}
	
	return 0;
}
