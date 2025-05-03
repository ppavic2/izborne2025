#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 3e5 + 5;

vector < int > ms[maxn];
int a[maxn], sol[maxn];
int maxd[maxn];

int dfs(int x, int prosl) {
  int maksi = -1;
  for(int y : ms[x]) {
    if(y != prosl) {
      maksi = max(dfs(y, x), maksi);
    }
  }
  return maxd[x] = maksi + 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  int x, y;
  for(int i = 0; i < n - 1; i++) {
    cin >> x >> y;
    x--; y--;
    ms[x].push_back(y);
    ms[y].push_back(x);
  }
  dfs(0, 0);
  sort(maxd, maxd + n);
  int pos = 0;
  for(int i = 1; i <= n; i++) {
    while(pos < n - 1 && maxd[pos] < i) {
      pos++;
    }
    sol[i] = pos * 2 + (n - 1 - pos) * 4 - maxd[n - 1];
  }
  for(int i = 0; i < q; i++) {
    cin >> x;
    cout << sol[x] << ' ';
  }
  cout << '\n';
  return 0;
}

