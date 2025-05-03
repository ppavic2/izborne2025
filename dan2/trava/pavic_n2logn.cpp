#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 7050;  // limit for array size
int n, q;  // array size
int t[2 * N];

void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, t[l++]);
    if (r&1) res = max(res, t[--r]);
  }
  return res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for(int i = 0;i < n;i++) {
		cin >> t[n + i];
	}
	build();
	for(;q--;) {
		char c; int x;
		cin >> c >> x;
		if(c == '+') {
			x--;
			modify(x, t[n + x] + 1);
		} else {
			ll ans = 0;
			for(int i = 0;i + x <= n;i++)
				ans += query(i, i + x);		
			cout << ans << '\n';
		}
	}
	return 0;
}
