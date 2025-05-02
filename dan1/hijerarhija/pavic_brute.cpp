#include <cstdio>
#include <vector>

#define X first
#define Y second

using namespace std;

typedef vector<int> vi;

const int N = 5050;

int uzeo[N], cookie = 1, n, k;
int par[N], p[N], c[N]; 

int main() {
	scanf("%d%d", &n, &k);	
	for(int i = 2;i <= n;i++) scanf("%d", par + i);
	for(int i = 1;i <= n;i++) scanf("%d", p + i);
	for(int i = 1;i <= n;i++) scanf("%d", c + i);
	int ans = 0;
	for(int msk = 0;msk < (1 << n);msk++) {
		int cur = 0, treba = 0; cookie++;
		for(int i = 1;i <= n;i++) {
			if((msk>>(i - 1)) & 1) {
				cur += p[i];
				treba += c[i] - 1;
				int tmp = i;
				while(uzeo[tmp] != cookie) {
					uzeo[tmp] = cookie;
					tmp = par[tmp];
				}
			}
		}
		for(int i = 1;i <= n;i++) 
			treba += uzeo[i] == cookie;
		if(treba <= k) ans = max(ans, cur);
	}
	printf("%d\n", ans);
	return 0;
}
