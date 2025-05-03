#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ld long double
#define fi first
#define se second
#define pii pair<int, int>

const int MAX = 1e3 + 30;
int n, q;
int x, y;
int drugi;
int lt, rt;
vector <int> veci[MAX];
vector <int> v;

map <pii, int> bio;
int upit(int a, int b) {
    if (b < a) swap(a, b);

    if (bio[{a, b}]) return bio[{a, b}];

    cout << "? " << a << " " << b << endl;
    int ret; cin >> ret;
    bio[{a, b}] = ret;

    return ret;
}

int bs() {
    while (lt < rt) {
        int mid = (lt + rt) / 2;
        if (lt < drugi) mid = (lt + rt + 1) / 2;

        int x = upit(mid, drugi);
        if (x == drugi) {
            if (lt < drugi) lt = mid;
            else rt = mid;
        }
        else {
            if (lt < drugi) rt = mid - 1;
            else lt = mid + 1;
        }
    }

    return lt;
}

void push() {
    vector <int> v2;

    int last = 0;
    for (int i = 0; i < v.size(); i++) {
        x = v[i];

        if (last + 1 == x) {
            last = x;
            continue;
        }

        y = upit(last + 1, x);

        v2.push_back(y);

        last = x;
    }

    if (v.back() != n) {
        x = v.back();
        y = upit(x, n);

        v2.push_back(y);
    }

    for (auto e : v2) {
        for (auto e2 : v) {
            veci[e].push_back(e2);
        }
    }

    for (int i = 0; i < v2.size() - 1; i++) {
        x = v2[i];
        y = v2[i + 1];

        int a = upit(x, y);

        if (a == x) veci[y].push_back(x);
        if (a == y) veci[x].push_back(y);
    }

    for (auto e : v2) v.push_back(e);
    sort(v.begin(), v.end());
}

void debug() {
    cout << "v -> "; for (auto e : v) cout << e << " "; cout << "\n";
}

int f(int lt, int rt) {
    for (int i = lt; i <= rt; i++) {
        int cnt = 0;

        for (auto e : veci[i]) if (lt <= e && e <= rt) cnt++;

        if (cnt != 1) continue;
        return i;
    }
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    cin >> n;

    drugi = upit(1, n);
    x = upit(1, drugi);

    if (x == drugi) {
        lt = 1;
        rt = drugi - 1;
    }
    else {
        lt = drugi + 1;
        rt = n;
    }

    x = bs();
    veci[drugi].push_back(x);

    v.push_back(x);
    v.push_back(drugi);
    sort(v.begin(), v.end());

    while (v.size() != n) {
//        debug();
        push();
    }
//    debug();

//    for (int i = 1; i <= n; i++) {
//        cout << i << " -> ";
//        for (auto e : veci[i]) cout << e << " ";
//        cout << "\n";
//    }

    cout << "!" << endl;

    cin >> q;
    while (q--) {
        cin >> x >> y;
        cout << f(x, y) << endl;
    }

    return 0;
}
