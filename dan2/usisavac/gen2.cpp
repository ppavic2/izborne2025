#include <cstdio>
#include <chrono>
#include <iostream>
#include <random>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

#define sz(x) (int)x.size()
#define X first
#define Y second
#define PB push_back

using namespace std;

typedef pair < int, int > pii;
typedef vector<int> vi;
typedef long long ll;

mt19937 rng;

int rint(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

int relement(vector<int> &v) {
	return v[rint(0, (int)v.size() - 1)];
}

/**

TREE TYPES
	- SHALLOW
	- DEEP
	- SQRT
	- CHAIN
	
CACTUS TYPES
	- SMALL_CYCLES
	- LARGE_CYCLES
	- LARGE_CYCLES_WITH_SPACE
	- ONE_LARGE_CYCLE
	- SUN TYPES
	| - SMALL_SUN
	| - LARGE_SUN
	| - SIMPLE_SUN

**/

int pr(int x, vi &par) {
	if(x == par[x]) return x;
	return par[x] = pr(par[x], par);
}

struct G {
	int n;
	vector<vi> v;
	G() {}
	G(int n) : n(n), v(n) {}
	
	void add_edge(int a, int b) {
		v[a].PB(b), v[b].PB(a);
	}
	
	void bfs(int start, vi &dist) {
		dist = vi(n, -1);
		dist[start] = 0;
		queue<int> Q; Q.push(start);
		for(;!Q.empty();Q.pop()) {
			int cur = Q.front();
			for(int nxt : v[cur]) {
				if(dist[nxt] == -1) {
					dist[nxt] = dist[cur] + 1;
					Q.push(nxt);
				}
			}
		}
	}
	
	bool find_path(int current, int last, int start, int target, vi &save) {
		if(current == target) {
			save.PB(current);
			return true;
		}
		for(int next : v[current]) {
			if(next == last || ((current == start && next == target) || (current == target && next == start))) continue;
			if(find_path(next, current, start, target, save)) {
				save.PB(current);
				return true;
			}
		}
		return false;
	}
	
	vi find_cycle() {
		vi par(n);
		for(int i = 0;i < n;i++) par[i] = i;
		int a = -1, b = -1;
		for(int i = 0;i < n && a == -1;i++) {
			for(int j : v[i]) {
				if(j < i) {
					int ii = pr(i, par), jj = pr(j, par);
					if(ii == jj) {
						a = i, b = j;
						break;
					} else {
						par[ii] = jj;
					}
				}
			}
		}
		vi ret;
		find_path(a, a, a, b, ret);
		return ret;
	}

	pii count_pair(int a, int b) {
		vi dist_a, dist_b;
		bfs(a, dist_a);
		bfs(b, dist_b);
		int cnt_a = 0, cnt_b = 0;
		for(int i = 0;i < n;i++) {
			assert(dist_a[i] >= 0 && dist_b[i] >= 0);
			if(dist_a[i] < dist_b[i]) cnt_a++;
			if(dist_b[i] < dist_a[i]) cnt_b++;
		}
		return {cnt_a, cnt_b};
	}

	vector<pii> get_edges() {
		vector<pii> edges;
		for(int i = 0;i < n;i++) {
			for(int j : v[i]) {
				if(i < j) edges.PB({i, j});
			}
		}
		shuffle(edges.begin(), edges.end(), rng);
		for (auto &[a, b] : edges) if(rint(0, 1)) swap(a, b);
		return edges;
	}
};

G gen_tree(int n, string T) {
	G ret(n);
	if(T == "SHALLOW") { 
		for(int i = 1;i < n;i++)
			ret.add_edge(i, rint(0, i - 1));
	} else if(T == "DEEP") {
		for(int i = 1;i < n;i++)
			ret.add_edge(i, rint(max(0, i - 20), i - 1));
	} else if(T == "SQRT") {
		vi pruf(n), kol(n);
		set<int> S;
		for(int i = 0;i < n - 2;i++) {
			pruf[i] = rint(0, n - 1);
			kol[pruf[i]]++;
		}
		for(int i = 0;i < n;i++) {
			if(!kol[i]) S.insert(i);
		}
		for(int i = 0;i < n - 2;i++){
			int j = *S.begin();
			S.erase(S.begin());
			kol[pruf[i]]--;
			ret.add_edge(j, pruf[i]);
			if(!kol[pruf[i]])
			    S.insert(pruf[i]);
		}
		int x = *S.begin(), y = *S.rbegin();
		ret.add_edge(x, y);
	} else if(T == "CHAIN") {
		for(int i = 1;i < (2 * n) / 3;i++)
			ret.add_edge(i, i - 1);
		for(int i = (2 * n) / 3;i < n;i++)
			ret.add_edge(rint(0, i - 1), i);
	}
	return ret;
}

void finish_output(G &graph) {
	int n = graph.n;
	vector<pii> edges = graph.get_edges();
	vi p(n);
	for(int i = 0;i < n;i++) p[i] = i + 1;
	//shuffle(p.begin(), p.end(), rng);
	for(auto &[a, b] : edges) cout << p[a] << " " << p[b] << "\n";
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

	if (argc < 4) {
		cerr << "Usage: ./gen2 <n> <q> <TREE_TYPE>\n";
		return 1;
	}

	int n = atoi(argv[1]);
	int q = atoi(argv[2]);
	string T = argv[3];

	G graph = gen_tree(n, T);

	cout << n << " " << q << "\n";
	finish_output(graph);
  if(q == 1) {
    if(T == "CHAIN" || T == "DEEP") {
      cout << rint(1, n / 10) << '\n';
    }
    else if(T == "SHALLOW") {
      cout << rint(1, 10) << '\n';
    }
    else {
      cout << rint(1, sqrt(n)) << '\n';
    }
    return 0;
  }
  vector < int > v;
  for(int i = 1; i <= n; i++) {
    v.push_back(i);
  }
  random_shuffle(v.begin(), v.end());
	for (int i = 1; i < q; i++) cout << v[i - 1] << " ";
	cout << v[q - 1] << "\n";
  return 0;
}

