#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int N = 505;

inline int add(int a, int b) {
	return (a + b >= MOD) ? a + b - MOD : a + b;
}
inline int sub(int a, int b) {
	return (a - b < 0) ? a - b + MOD : a - b;
}
inline int mul(int a, int b) {
	return (long long) a * b % MOD;
}

int n, p[N * N], choose[N][N], ans[N];
int dp_0[N][N], dp[N][N][N];

void precompute() {
	p[0] = 1;
	for (int i = 1; i < N * N; ++i) {
		p[i] = mul(p[i - 1], 2);
	}
	choose[0][0] = 1;
	for (int i = 1; i < N; ++i) {
		for (int j = 1; j <= i; ++j) {
			choose[i][j] = add(choose[i - 1][j], choose[i - 1][j - 1]);
		}
		choose[i][0] = 1;
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	precompute();

	cin >> n;

	if (n == 1) {
		cout << "1 0\n";
		return 0;
	}

	for (int i = 1; i < n; ++i) dp_0[1][i] = 1;
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; i + j <= n; ++j) {
			for (int k = 0; k <= j; ++k) {
				int count = mul(p[j - k], choose[j][k]);
				if (k == 0) count = sub(p[j], 1);
				if (j == 0) count = 1;
				dp_0[i][j] = add(dp_0[i][j], mul(dp_0[i - 1][j + 1 - k], count));
			}
		}
	}

	dp[1][0][0] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			for (int k = 0; k < i - j; ++k) {
				dp[i][j][k] = mul(dp[i - 1][j][k], p[k]);
				if (j) {
					int count = mul(sub(p[i - 1 - k], 1), p[k]);
					dp[i][j][k] = add(dp[i][j][k], mul(dp[i - 1][j - 1][k], count));
				}
				if (k) {
					dp[i][j][k] = add(dp[i][j][k], mul(dp[i - 1][j][k - 1], p[k - 1]));
				}
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i; ++j) {
			int val = mul(dp[n - 1][i][j], p[j]), k = n - i - j;
			val = mul(val, dp_0[k][0]);
			ans[k] = add(ans[k], val);
		}
	}

	ans[0] = p[n * (n - 1) / 2];
	for (int i = 2; i <= n; ++i) {
		ans[0] = sub(ans[0], ans[i]);
	}

	for (int i = 0; i <= n; ++i) {
		cout << ans[i] << ' ';
	}
	cout << '\n';

	return 0;
}
