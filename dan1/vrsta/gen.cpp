#include <bits/stdc++.h>
#include <unistd.h>

#define PB push_back

using namespace std;

typedef vector<int> vi;

vi p;

void cartesian_tree(int a, int b, int max, int step) {
	if(a > b) return;
	int mid = (a + b) / 2;
	p[mid] = max;
	cartesian_tree(a, mid - 1, max - step, 2 * step);
	cartesian_tree(mid + 1, b, max - 2 * step, 2 * step);
}


int main() {
	srand(time(NULL) * getpid());
	int n = 511, k = 4 * n, Q = 2048;
	cout << n << " " << k << " " << Q << endl;
	int tip = 2;
	if(tip == 1) {
		vi tmp(n);
		for(int i = 0;i < n;i++) tmp[i] = i + 1;
		random_shuffle(tmp.begin(), tmp.begin() + n / 2);
		random_shuffle(tmp.begin() + n / 2, tmp.end());
		for(int i = 0;i < n;i++) {
			if(i & 1) p.PB(p[i >> 1]);
			else tmp.PB(p[n / 2 + (i >> 1)]);
		}
	} else if(tip == 1) {
		p = vi(n);
		cartesian_tree(0, n - 1, n, 1);
	} else if(tip == 2) {
		for(int i = n - 1;i >= 2;i--) p.PB(i);
		p.PB(n); p.PB(1);
	} else if(tip == 3) { // dolje pa gore
		vi L, R;
		for(int i = 1;i <= n;i++) {
			if(rand() % 2 == 0) L.push_back(i);
			else R.push_back(i);
		}
		reverse(L.begin(), L.end());
		p.insert(p.end(), L.begin(), L.end());
		p.insert(p.end(), R.begin(), R.end());
	} else if(tip == 4) { // gore pa dolje
		vi L, R;
		for(int i = 1;i <= n;i++) {
			if(rand() % 2 == 0) L.push_back(i);
			else R.push_back(i);
		}
		reverse(R.begin(), R.end());
		p.insert(p.end(), L.begin(), L.end());
		p.insert(p.end(), R.begin(), R.end());
	}
	for(int i = 0;i < n;i++) cout << p[i] << (i == n - 1 ? "\n" : " ");
	for(int i = 0;i < Q;i++) {
		int a = rand() % n, b = rand() % (n - 1);
		if(a == b) b++;
		cout << min(a, b) + 1 << " " << max(a, b) + 1 << endl;
	}
	return 0;
}
