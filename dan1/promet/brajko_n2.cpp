#include <bits/stdc++.h>
using namespace std;

int MOD = 998244353;
const int N = 5005;

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
int dp_con[N], dp_reach[N][N], dp_all[N][N];
int A[N][N], B[N][N], C[N];

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

	cin >> n >> MOD;

	A[1][0] = 1;
	A[1][1] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j < i) A[i][j] = mul(A[i - 1][j], p[i - j - 1]);
			if (j) A[i][j] = add(A[i][j], mul(A[i - 1][j - 1], p[i - j]));
		}
	}

	for (int i = n - 1; i > 0; --i) {
		for (int j = 0; j < i; ++j) {
			A[i][j] = mul(A[i - 1][j], sub(p[i - j - 1], 1));
		}
		A[i][i] = 0;
	}
	A[1][0] = 1;

	B[1][0] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			B[i][j] = B[i - 1][j];
			if (j) B[i][j] = add(B[i][j], mul(B[i - 1][j - 1], sub(p[i - j], 1)));
		}
	}
	for (int i = n; i > 1; --i) {
		for (int j = 0; j < i; ++j) {
			B[i][j] = mul(B[i - 1][j], sub(p[i - j - 1], 1));
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j & 1) C[i] = sub(C[i], A[i][j]);
			else C[i] = add(C[i], A[i][j]);
		}
	}

	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (j & 1) {
				dp_con[i] = sub(dp_con[i], mul(B[i][j], C[i - j - 1]));
			} else {
				dp_con[i] = add(dp_con[i], mul(B[i][j], C[i - j - 1]));
			}
		}
	}

	dp_reach[1][0] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			dp_reach[i][j] = dp_reach[i - 1][j];
			if (j) dp_reach[i][j] = add(dp_reach[i][j], mul(dp_reach[i - 1][j - 1], sub(p[i - 1], 1)));
		}
	}

	dp_all[1][0] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			dp_all[i][j] = mul(dp_all[i - 1][j], p[j]);
			if (j) dp_all[i][j] = add(dp_all[i][j], mul(dp_all[i - 1][j - 1], p[j - 1]));
		}
	}

	for (int i = 2; i <= n; ++i) {
		for (int j = 0; i + j <= n; ++j) {
			int k = n - i - j;
			int count = mul(dp_con[i], dp_reach[i + j - 1][j]);
			count = mul(count, dp_all[n - 1][k]);
			count = mul(count, p[k]);

			ans[i] = add(ans[i], count);
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
