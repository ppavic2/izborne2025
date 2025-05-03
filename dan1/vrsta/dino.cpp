#include <bits/stdc++.h>

#define F first
#define S second
#define pb push_back
#define all(x) x.begin(), x.end()

using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

const int N = 512;

const int test = 0;

int n, q;
int d[N], c[N][2];
vector <int> g[N];

int a[N];


int check(int x, int y) {
	vector <pii> v;
	for (int i = x; i <= y; i++) v.pb({a[i], i});
	sort(all(v));
	return v[v.size()-2].S;
}


int ask(int x, int y) {
	cout << "? " << x+1 << " " << y+1 << endl;
	if (test) {
		int o = check(x, y);
		cout << "-> " << o+1 << endl;
		return o;
	}
	int o; cin >> o;
	return o-1;
}

int lar(int l, int r) {
	int p = l;
	for (int i = l+1; i <= r; i++) if (d[p] > d[i]) p = i;
	return p;
}

int f(int l, int r, int le, int ri, int de) {
	int x = ask(l-le, r+ri);
	d[x] = de;
	if (l < x) c[x][0] = f(l, x-1, 0, 1, de+1);
	if (r > x) c[x][1] = f(x+1, r, 1, 0, de+1);
	return x;
}

int main() {
	cin >> n;
	
	if (test) {
		for (int i = 0; i < n; i++) cin >> a[i];
	}
	
	int p = 0;
	for (int i = 1; i < n; i++) {
		if (ask(p, i) == p) p = i;
	}
	
	memset(c, -1, sizeof c);
	
	if (p) c[p][0] = f(0, p-1, 0, 1, 1);
	if (p < n-1) c[p][1] = f(p+1, n-1, 1, 0, 1);
	
	for (int i = 0; i < n; i++) {
		int x = c[i][0], y = c[i][1];
		while (x != -1 && y != -1) {
			int o = (ask(x, y) == y);
			g[i].pb(o);
			if (!o) x = c[x][1];
			else y = c[y][0];
		}
	}
	
	cout << "!" << endl;
	
	cin >> q;
	while (q--) {
		int l, r; cin >> l >> r; l--; r--;
		int x = lar(l, r);
		int y = c[x][0], z = c[x][1];
		int ix = 0, no = -1;
		while (y != -1 && z != -1) {
			if (g[x][ix]) {
				if (z <= r) {
					no = z;
					break;
				}
				z = c[z][0];
			}
			else {
				if (y >= l) {
					no = y;
					break;
				}
				y = c[y][1];
			}
			ix++;
		}
		if (no != -1) {
			cout << no+1 << endl;
			continue;
		}
		if (z == -1) {
			cout << lar(l, x-1)+1 << endl;
			continue;
		}
		if (y == -1) {
			cout << lar(x+1, r)+1 << endl;
		}
	}
	
	return 0;
}
