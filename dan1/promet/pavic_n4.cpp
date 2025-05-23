#include <cstdio>
#include <cstring>

using namespace std;

const int N = 105;

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

int dp[N][N][N][N];
int dp2[N][N][N];


int pot2[N * N], fak[N], ch[N][N];

void precompute() {
	pot2[0] = 1;
	for(int i = 1;i < N * N;i++) pot2[i] = add(pot2[i - 1], pot2[i - 1]);
	for(int n = 0;n < N;n++) ch[n][0] = ch[n][n] = 1;
	for(int n = 1;n < N;n++) {
		for(int k = 1;k < n;k++)
			ch[n][k] = add(ch[n - 1][k - 1], ch[n - 1][k]);
	}
}

int f(int cvor, int PLJ_L,
				int J_LJ,
				int J_C) {
	if(cvor == n - 1) return J_LJ == 1 && J_C == 0;
	int ZC_L = cvor - PLJ_L;
	int ret = 0;
	ret = add(ret, mul(f(cvor + 1, PLJ_L + 1, J_LJ, J_C), mul(pot2[ZC_L], sub(pot2[PLJ_L], 1))));
	if(J_C > 0)
		ret = add(ret, mul(f(cvor + 1, PLJ_L, J_LJ, J_C - 1), sub(pot2[J_LJ + J_C - 1], 1)));
	ret = add(ret, mul(f(cvor + 1, PLJ_L, J_LJ, J_C), pot2[ZC_L]));
	if(J_LJ > 1)
		ret = add(ret, f(cvor + 1, PLJ_L + 1, J_LJ - 1, J_C));
	return ret;
}

int f2(int cvor, int zadnji, int nula) {
	if(cvor == zadnji) return pot2[cvor - nula];
	int poz = cvor - nula, ret = 0;
	for(int k = 0;k <= nula;k++) {
		ret = add(ret, mul(f2(cvor + 1, zadnji, nula - k + 1), mul(ch[nula][k], sub(pot2[poz], !k))));
	}
	return ret;
}

int ans[N];

int main() {
	scanf("%d%d", &n, &MOD);
	precompute();
	
	for(int PLJ_L = 1;PLJ_L <= n;PLJ_L++) dp[n - 1][PLJ_L][1][0] = 1;
	
	for(int zadnji = 1;zadnji <= n;zadnji++) {
		for(int cvor = zadnji;cvor >= 1;cvor--) {
			for(int nula = 0;nula <= cvor;nula++) {
				int &ret = dp2[cvor][zadnji][nula];
				if(cvor == zadnji) ret = pot2[cvor - nula];
				else {
					int poz = cvor - nula;
					for(int k = 0;k <= nula;k++) {
						ret = add(ret, mul(dp2[cvor + 1][zadnji][nula - k + 1], mul(ch[nula][k], sub(pot2[poz], !k))));
					}
				}
			}
		}
	}
	
	for(int cvor = n - 2;cvor >= 1;cvor--) {
		for(int J_LJ = 1;J_LJ <= n - cvor;J_LJ++) {
			for(int J_C = 0;J_C <= n - cvor - 1;J_C++) {
				for(int PLJ_L = 1;PLJ_L <= cvor;PLJ_L++) {
					int ZC_L = cvor - PLJ_L, &ret = dp[cvor][PLJ_L][J_LJ][J_C];
					ret = add(ret, mul(dp[cvor + 1][PLJ_L + 1][J_LJ][J_C], mul(pot2[ZC_L], sub(pot2[PLJ_L], 1))));
					ret = add(ret, mul(dp[cvor + 1][PLJ_L][J_LJ][J_C], pot2[ZC_L]));
					if(J_C > 0)
						ret = add(ret, mul(dp[cvor + 1][PLJ_L][J_LJ][J_C - 1], sub(pot2[J_LJ + J_C - 1], 1)));
					ret = add(ret, dp[cvor + 1][PLJ_L + 1][J_LJ - 1][J_C]);
				}
			}
		}
	}
	
	int sve = pot2[n * (n - 1) / 2];
	for(int i = 2;i <= n;i++) {
		for(int c = 0;c + i <= n;c++) {
			ans[i] = add(ans[i], dp[1][1][i - 1][c]);
		}
		ans[i] = mul(ans[i], dp2[1][i - 1][1]);
		sve = sub(sve, ans[i]);
	}
	printf("%d %d ", sve, 0);
	for(int i = 2;i <= n;i++) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
