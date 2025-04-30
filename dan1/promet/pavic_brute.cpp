#include <cstdio>
#include <cstring>

using namespace std;

const int N = 55;

int n, MOD;

inline int add(int A, int B) {
	if(A + B >= MOD) return A + B - MOD;
	return A + B;
}

inline int sub(int A, int B) {
	if(A - B < 0) return A - B + MOD;
	return A - B;
}

inline int mul(int A, int B) {
	return A * 1ll * B % MOD;
}

inline int pot(int A, int B) {
	int ret = 1;
	for(; B ; B >>= 1) {
		if(B&1) ret = mul(ret, A);
		A = mul(A, A);
	}
	return ret;
}

int ans[N], edg[N][N], L[N], R[N];

int main() {
	//scanf("%d%d", &n, &MOD);
	scanf("%d", &n); MOD = 998244353;
	int E = n * (n - 1) / 2;
	for(int msk = 0;msk < (1 << E);msk++) {
		int tmp = msk;
		for(int i = 0;i < n;i++)
			for(int j = i + 1;j < n;j++, tmp >>= 1)
				edg[i][j] = tmp & 1;
		L[0] = 1, R[n - 1] = 1;
		for(int i = 1;i < n;i++) {
			L[i] = 0;
			for(int j = 0;j < i;j++)
				L[i] |= edg[j][i] & L[j];
		}
		for(int i = n - 2;i >= 0;i--) {
			R[i] = 0;
			for(int j = i + 1;j < n;j++)
				R[i] |= edg[i][j] & R[j];
		}
		int cnt = 0;
		for(int i = 0;i < n;i++)
			cnt += L[i] & R[i];
		ans[cnt]++;
	}
	for(int i = 0;i <= n;i++) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
