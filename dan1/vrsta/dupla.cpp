#include <bits/stdc++.h>

#define f first
#define s second

using namespace std;

typedef pair<int, int> pii;

const int MAXN = 520;

int n, q;

int memo[MAXN][MAXN];
int k = 0;
int query(int l, int r){
    //k++;
    //if(k >= 2048) exit(1);
    if(r <= l) return -1;
    if(memo[l][r]) return memo[l][r];

    cout << "? " << l << ' ' << r << endl;
    cin >> memo[l][r];
    return memo[l][r];
}

pii maxis[MAXN][MAXN];
int lt[MAXN][MAXN], rt[MAXN][MAXN];

void build(int l, int r, int d){
    if(r - l <= 1) return;

    int x = maxis[l][r].f, y = maxis[l][r].s;
    if(x > y) swap(x, y);

    if(x >= l + 2){
        maxis[l][x - 1].f = query(l, x);
        maxis[l][x - 1].s = query(l, x - 1);
        build(l, x - 1, d + 1);
    }
    if(y <= r - 2){
        maxis[y + 1][r].f = query(y, r);
        maxis[y + 1][r].s = query(y + 1, r);
        build(y + 1, r, d + 1);
    }
    if(y - x >= 3){
        maxis[x + 1][y - 1].f = query(x, y - 1);
        maxis[x + 1][y - 1].s = query(x + 1, y - 1);
        build(x + 1, y - 1, d + 1);
    }

    int pl = x - 1;
    lt[d][x] = x;
    for(int i = x + 1; i < y; i++){
        while(pl >= l && query(pl, i) > x) pl--;
        lt[d][i] = pl;
    }

    int pr = y + 1;
    rt[d][y] = y;
    for(int i = y - 1; i > x; i--){
        while(pr <= r && query(i, pr) < y) pr++;
        rt[d][i] = pr;
    }

    //cout << l << ' ' << r << ": " << maxis[l][r].f << ' ' << maxis[l][r].s << "\n";
    //for(int i = x + 1; i < y; i++){
        //printf("%d: (%d, %d)\n", i, lt[d][i], rt[d][i]);
    //}
}

pii sol(int lq, int rq, int l = 1, int r = n, int d = 0){
    //cout << lq << ' ' << rq << ' ' << l << ' ' << r << '\n';
    if(rq <= lq || r <= l) return {lq, lq};

    int x = maxis[l][r].f, y = maxis[l][r].s;
    if(x > y) swap(x, y);

    if(lq <= x && rq >= y) return maxis[l][r];
    if(rq < x) return sol(lq, rq, l, x - 1, d + 1);
    if(lq > y) return sol(lq, rq, y + 1, r, d + 1);
    if(lq > x && rq < y) return sol(lq, rq, x + 1, y - 1, d + 1);

    if(lq <= x){
        if(lq <= lt[d][rq]) return {x, sol(lq, x - 1, l, x - 1, d + 1).f};
        return {x, sol(x + 1, rq, x + 1, y - 1, d + 1).f};
    }

    //rq >= y
    if(rq >= rt[d][lq]) return {y, sol(y + 1, rq, y + 1, r, d + 1).f};
    return {y, sol(lq, y - 1, x + 1, y - 1, d + 1).f};
}

int main(){
    cin >> n;

    int x = query(1, n);
    if(query(1, x) == x){
        int l = 1, r = x - 1;
        while(r > l){
            int m = (l + r + 1) / 2;
            if(query(m, x) == x) l = m;
            else r = m - 1;
        }
        maxis[1][n].f = l;
        maxis[1][n].s = x;
    }
    else{
        int l = x + 1, r = n;
        while(r > l){
            int m = (l + r) / 2;
            if(query(x, m) == x) r = m;
            else l = m + 1;
        }
        maxis[1][n].f = l;
        maxis[1][n].s = x;
    }
	cerr << x << endl;
    build(1, n, 0);
    cout << '!' << endl;

    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;

        cout << sol(l, r).s << '\n';
    }
    cout << endl;

    return 0;
}
