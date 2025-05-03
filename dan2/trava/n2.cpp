#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5;

int n, q, a[N];
ll ans[N];

void upd_contr(int i, int val) {
	int L = i - 1, R = i;
	while (L >= 0 && a[L] < a[i]) --L;
	while (R < n && a[R] <= a[i]) ++R;
	
	int l = L - i, r = R - i;
	for (int i = 1; i <= l + r - 1; ++i) {
		int count = min({i, l, r});
		ans[i] += (ll)count * val;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> q;

	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
	for (int i = 0; i < n; ++i) {
		upd_contr(i, a[i]);
	}
	
	while (q--) {
		int t, k;
		cin >> t >> k;
		if (t == 1) {
			--k;
			upd_contr(k, -1);
			a[k] += 1;
			upd_contr(k, 1);
		} else {
			cout << ans[k] << '\n';
		}
	}
	
	return 0;
}
