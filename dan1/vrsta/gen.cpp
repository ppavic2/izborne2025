#include <bits/stdc++.h>
#include <unistd.h>

#define PB push_back

using namespace std;

typedef vector<int> vi;

mt19937 rng;

int rint(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int relement(vector<int> &v) {
	return v[rint(0, (int)v.size() - 1)];
}

vi p;

void cartesian_tree(int a, int b, int max, int step) {
	if(a > b) return;
	int mid = (a + b) / 2;
	p[mid] = max;
	cartesian_tree(a, mid - 1, max - step, 2 * step);
	cartesian_tree(mid + 1, b, max - 2 * step, 2 * step);
}

int to_int(char *s){
    int ret = 0, k = strlen(s);
    for(int i = 0;i < k;i++) {
        ret = 10 * ret + s[i] - '0';
    }
   	return ret;
}


int main(int argc, char** argv){
	ios_base::sync_with_stdio(false); cin.tie(0);
	rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
	
	int n = to_int(argv[1]);
	int tip = to_int(argv[2]);
	int augment = to_int(argv[3]);
	
	
	int Q = 2048;
	if(tip == 0) { // permutacija s puno dolova i gora
		vi tmp(n);
		for(int i = 0;i < n;i++) tmp[i] = i + 1;
		shuffle(tmp.begin(), tmp.begin() + n / 2, rng);
		shuffle(tmp.begin() + n / 2, tmp.end(), rng);
		for(int i = 0;i < n;i++) {
			if(i & 1) p.PB(tmp[i >> 1]);
			else p.PB(tmp[n / 2 + (i >> 1)]);
		}
	} else if(tip == 1) { // kartezijevo stablo
		p = vi(n);
		cartesian_tree(0, n - 1, n, 1);
		int k = to_int(argv[4]);
		for(int i = 0;i < k;i++) 
			swap(p[rint(0, n - 1)], p[rint(0, n - 1)]);
	} else if(tip == 2) { // poseban primjer za veliki broj kverija
		for(int i = n - 1;i >= 2;i--) p.PB(i);
		p.PB(n); p.PB(1);
		int flag = to_int(argv[3]);
		if(flag) reverse(p.begin(), p.end());
	} else if(tip == 3) {
		for(int i = n - 1;i >= 1;i--) p.PB(i);
		p.PB(n);
		int flag = to_int(argv[4]);
		if(flag) reverse(p.begin(), p.end());
	} else if(tip == 4) {
		for(int i = 1;i <= n;i++) p.PB(i);
		int flag = to_int(argv[4]);
		if(flag) reverse(p.begin(), p.end());
	} else if(tip == 5) { // dolje pa gore
		vi L, R;
		for(int i = 1;i <= n;i++) {
			if(rint(0, 1) == 0) L.push_back(i);
			else R.push_back(i);
		}
		reverse(L.begin(), L.end());
		p.insert(p.end(), L.begin(), L.end());
		p.insert(p.end(), R.begin(), R.end());
	} else if(tip == 6) { // gore pa dolje
		vi L, R;
		for(int i = 1;i <= n;i++) {
			if(rint(0, 1) == 0) L.push_back(i);
			else R.push_back(i);
		}
		reverse(R.begin(), R.end());
		p.insert(p.end(), L.begin(), L.end());
		p.insert(p.end(), R.begin(), R.end());
	} else {
		assert(false);
	}
	
	
	
	if(augment) {
		p.erase(find(p.begin(), p.end(), n));
		p.insert(p.begin(), n);
	}	

	
	cout << n << " " << Q << endl;
	for(int i = 0;i < n;i++) 
		cout << p[i] << (i == n - 1 ? "\n" : " ");
	for(int i = 0;i < Q / 3;i++) {
		int a = rint(0, n - 1), b = rint(0, n - 2);
		if(a == b) b++;
		cout << min(a, b) + 1 << " " << max(a, b) + 1 << endl;
	}
	for(int i = Q / 3;i < 2 * Q / 3;i++) {
		int len = rint(2, max(2, n / 10)), a = rint(0, n - len);
		cout << a + 1 << " " << a + len << endl;
	}
	for(int i = 2 * Q / 3;i + 5 < Q;i++) {
		int len = rint(2, 7), a = rint(0, n - len);
		cout << a + 1 << " " << a + len << endl;
	}
	cout << 1 << " " << n << endl;
	cout << 1 << " " << 2 << endl;
	cout << n - 1 << " " << n << endl;
	cout << 1 << " " << n - 1 << endl;
	cout << 2 << " " << n << endl;
	return 0;
}
