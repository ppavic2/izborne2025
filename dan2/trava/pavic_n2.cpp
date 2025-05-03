#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 7050;  // limit for array size

struct M {
	deque<int> D;
	queue<int> Q;
	
	void push(int x) {
		Q.push(x);
		while(!D.empty() && D.back() < x) D.pop_back();
		D.push_back(x);
	}
	
	void pop() {
		if(Q.front() == D.front()) D.pop_front();
		Q.pop();
	}
	
	int maax() {
		return D.front();
	}
	
	void clear() {
		D.clear();
		for(;!Q.empty();Q.pop());
	}
};

int A[N], n, q;
M M;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> q;
	for(int i = 0;i < n;i++) {
		cin >> A[i];
	}
	for(;q--;) {
		char c; int x;
		cin >> c >> x;
		if(c == '+') {
			A[--x]++;
		} else {
			ll ans = 0;
			for(int i = 0;i + 1 < x;i++) M.push(A[i]);
			for(int i = 0;i + x <= n;i++) {
				M.push(A[i + x - 1]);
				ans += M.maax();
				M.pop();
			}
			M.clear();
			cout << ans << '\n';
		}
	}
	return 0;
}
