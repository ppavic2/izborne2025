#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define PB push_back

using namespace std;

const int N = 515;

int L[N], LL[N], R[N], RR[N], n, k, q;

vector<int> valley_L[N], valley_R[N];
map<int,int> save[N];

int ask_query(int a, int b) {
	//if(save[a].count(b)) return save[a][b];
	cout << "? " << a << " " << b << endl;
	int x; cin >> x;
	return save[a][b] = x;
}

int find_max(int a, int b) {
	if(a == b) return a;
	int mid = ask_query(a, b);
	if(a == mid) return find_max(a + 1, b);
	if(b == mid) return find_max(a, b - 1);
	if(ask_query(a, mid) == mid)
		return find_max(a, mid - 1);
	else
		return find_max(mid + 1, b);
}

void build_tree(int a, int b, int GL, int GR) {
	if(a > b) return;
	int maax = -1;
	if(a == b) {
		maax = a;
	} else if(GL && GL == a - 1) {
		maax = ask_query(a - 1, b);
	} else {
		maax = ask_query(a, b + 1);
	}
	L[maax] = GL, R[maax] = GR;
	build_tree(a, maax - 1, GL, maax);
	build_tree(maax + 1, b, maax, GR);
}

void build_skips() {
	for (int i = 0;i < n;i++) {
		if(1 <= L[i] && L[i] <= n) {
			valley_R[L[i]].PB(i);
		}
		if(1 <= R[i] && R[i] <= n) {
			valley_L[R[i]].PB(i);
		}
	}
	int cnt = 0;
	for(int i = 1;i <= n;i++) {
		reverse(valley_L[i].begin(), valley_L[i].end());
		int zad_L = L[i], zad_R = R[i];
		while(!valley_L[i].empty() && !valley_R[i].empty()) {
			int x = valley_L[i].back(), y = valley_R[i].back();
			int xy = ask_query(x, y);
			cnt++;
			if(xy == x) {
				RR[x] = zad_R;
				zad_L = x;
				valley_L[i].pop_back();
			} else {
				LL[y] = zad_L;
				zad_R = y;
				valley_R[i].pop_back();
			}
		}
		for(int x : valley_L[i]) RR[x] = zad_R;
		for(int y : valley_R[i]) LL[y] = zad_L;
	}
}

int second_max(int l, int r) {
	for(int i = l;i <= r;i++) {
		int cnt = 0;
		cnt += (l <= L[i] && L[i] <= r);
		cnt += (l <= LL[i] && LL[i] <= r);
		cnt += (l <= R[i] && R[i] <= r);
		cnt += (l <= RR[i] && RR[i] <= r);
		if(cnt == 1) return i;
	}
	assert(false);
	return -1;
}

int main() {
	cin >> n >> k;
	int max_pos = find_max(1, n);
	build_tree(1, max_pos - 1, 0, max_pos);
	build_tree(max_pos + 1, n, max_pos, n + 1);
	build_skips();
	cout << "!" << endl;
	cin >> q;
	for(;q--;) {
		int l, r; cin >> l >> r;
		cout << second_max(l, r) << endl;
	}
	return 0;
}
