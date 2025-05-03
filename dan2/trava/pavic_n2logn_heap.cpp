#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 7050;  // limit for array size

int A[N], n, q;


int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for(int i = 0;i < n;i++) {
		cin >> A[i];
	}
	for(;q--;) {
		char c; int x;
		cin >> c >> x;
		if(c == '+') {
			A[--x]++;
		} else {
			ll ans = 0;
			priority_queue<int> M;
			for(int i = 0;i + 1 < x;i++) M.push(A[i]);
			for(int i = 0;i + x <= n;i++) {
				M.push(A[i + x - 1]);
				ans += M.top();
				M.pop();
			}
			cout << ans << '\n';
		}
	}
	return 0;
}
