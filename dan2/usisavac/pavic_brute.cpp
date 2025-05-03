#include <bits/stdc++.h>

#define PB push_back
#define X first
#define Y second

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;

const int N = 16;
const int MSK = (1 << N);

int n, q, dist[N][N];
vector<pii> v[N];
int kad[MSK][N][N];

int main() {
	memset(kad, -1, sizeof(kad));
	scanf("%d%d", &n, &q);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++) 
			dist[i][j] = n - 1;
	for(int i = 0;i + 1 < n;i++) {
		int a, b; scanf("%d%d", &a, &b);
		v[a].PB({b, i});
		v[b].PB({a, i});
		dist[a][b] = 1; dist[b][a] = 1;
	}
	for(int i = 1;i <= n;i++) dist[i][i] = 0;
	for(int k = 1;k <= n;k++)
		for(int i = 1;i <= n;i++)
			for(int j = 1;j <= n;j++)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	for(int i = 0;i < q;i++) {
		int k; scanf("%d", &k);
		memset(kad, -1, sizeof(kad));
		queue<pair<int,pii>> Q;
		Q.push({0, pii(1, 1)});
		kad[0][1][1] = 0;
		for(;!Q.empty();) {
			int mask = Q.front().X;
			int cur = Q.front().Y.X;
			int usi = Q.front().Y.Y;
			Q.pop();
			if (mask == (1 << (n - 1)) - 1) {
				printf("%d ", kad[mask][cur][usi]);
				break;
			}
			assert(dist[cur][usi] <= k);
			for(auto &[nxt, brid] : v[cur]) {
				if (dist[nxt][usi] > k) continue;
				if (kad[mask | (1 << brid)][nxt][usi] == -1) {
					kad[mask | (1 << brid)][nxt][usi] = kad[mask][cur][usi] + 1;
					Q.push({mask | (1 << brid), pii(nxt, usi)});
				}
			}
			if(cur == usi) {
				for(auto &[nxt, brid] : v[cur]) {
					if (kad[mask][nxt][nxt] == -1) {
						kad[mask][nxt][nxt] = kad[mask][cur][cur] + 1;
						Q.push({mask, pii(nxt, nxt)});
					}
				}
			}
		}
	}
	printf("\n");
	return 0;
}
