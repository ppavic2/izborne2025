#include <algorithm>
#include <iostream>
#include <vector>

#define PB push_back

using namespace std;

typedef vector<int> vi;

int n, p, q;
vi G;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0); cin >> n >> p >> q;
	string pq;
	int cnt = 0;
	while((int)G.size() <= n){
		p <<= 1;
		if(p >= q) {
			G.PB(cnt);
			p -= q;
			cnt = 0;
			pq.PB('1');
		} else {
			cnt++;
			pq.PB('0');
		}
	}
	string cur;
	int pos = 1;
	for(int i = 0;i < n;i++) pos &= pq[G[0] + i] == '1';
	for(int i = 0;i < n;i++) {
		cur = string(G[0], '0') + "1" + cur;
		if(i == n - 1 && pos) {
			cur.erase(cur.begin());
			break;
		}
		cout << cur << " " << pq << endl;
		while(cur < pq) {
			cout << cur << " " << pq << endl;
			int ind = 0;
			while(ind < (int)cur.size() && cur[ind] == pq[ind]) ind++;
			if(ind == (int)cur.size()) {
				ind--;
				while(cur[ind] == '1') ind--;
				cur.erase(cur.begin() + ind);
			} else {
				cur.erase(cur.begin() + ind);
			}
		}
	}
	reverse(cur.begin(), cur.end());
	cur.PB('0');
	cout << cur << endl;
	return 0;
}
