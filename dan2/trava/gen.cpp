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
	int q = to_int(argv[2]);
	int tip_niz = to_int(argv[3]);
	int tip_q = to_int(argv[4]);
	int l_k = to_int(argv[5]);
	int r_k = to_int(argv[6]);
	int max_val = to_int(argv[7]);
	int density = to_int(argv[8]);
	vi A(n);
	cout << n << " " << q << endl;
	
	if(tip_niz == 0) {
		for(int i = 0;i < n;i++)
			A[i] = rint(1, max_val);
	} else if(tip_niz == 1) {
		vi v;
		for(int i = 0;i < 5;i++) v.PB(rint(10, max_val));
		sort(v.begin(), v.end());
		for(int i = 1;i <= n;i++)
			A[i - 1] = v[__lg(i & -i) / 4] + rint(-3, 3);
	} else if(tip_niz == 2) {
		vi v;
		for(int i = 0;i < 15;i++) v.PB(rint(10, max_val));
		sort(v.begin(), v.end());
		for(int i = 1;i <= n;i++)
			A[i - 1] = v[__lg(((i + 32) >> 5) & -((i + 32) >> 5))] + rint(-3, 3);
	} else if(tip_niz == 3) {
		vi v;
		for(int i = 0;i < 15;i++) v.PB(rint(10, max_val));
		for(int i = 1;i <= n;i++)
			A[i - 1] = v[min((int)v.size() - 1, (i / (max(1, n / 225))))] + rint(-3, 3);
	}
	
	for (int i = 0;i < n;i++) cout << A[i] << (i == n - 1 ? "\n" : " ");
	
	if (tip_q == 0) {
		for(int i = 0;i < q;i++) {
			if(rint(0, 99) < density) {
				cout << "? " << rint(l_k, r_k) << endl;
			} else {
				cout << "+ " << rint(1, n) << endl;
			}
		}	
	} else if(tip_q == 1 || tip_q == 2) {
		int k = 0;
		for(int i = 0;i < q;i++) {
			if(rint(0, 99) < density) {
				cout << "? " << rint(l_k, r_k) << endl;
			} else {
				k = (k + rint(0, 2)) % n;
				cout << "+ " << ((tip_q == 1) ? (k + 1) : (n - k)) << endl;
			}
		}
	} else if(tip_q == 3) {
		vi v;
		for(int i = 0;i < 20;i++) v.PB(rint(1, n));
		for(int i = 0;i < q;i++) {
			if(rint(0, 99) < density) {
				cout << "? " << rint(l_k, r_k) << endl;
			} else {
				cout << "+ " << relement(v) << endl;
			}
		}
	} else if(tip_q == 4) {
		int t = 0;
		for(int i = 0;i < q;i++) {
			if(rint(0, 99) < density) {
				cout << "? " << rint(l_k, r_k) << endl;
			} else {
				t = (t + rint(0, 2)) % n;
				while(A[t] == 10) t = (t + rint(0, 2)) % n;
				A[t]++;
				cout << "+ " << t + 1 << endl;
			}
		}
	}
	return 0;
}
