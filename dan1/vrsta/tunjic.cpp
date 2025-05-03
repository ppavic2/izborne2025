#include <cstdio>
#include <cstring>

#define DEB 0

using namespace std;

const int N = 520;

int ans[N][N], p[N];

int answer(int x, int y) { 
    int mx = 0, mx2 = 0, ind = 0, ind2 = 0;
    for(x; x <= y; ++x) { 
        if(p[x] > mx) { 
            ind2 = ind;
            ind = x;
            mx2 = mx;
            mx = p[x];
        } else if(p[x] > mx2) { 
            mx2 = p[x];
            ind2 = x;
        }
    }
    return ind2;
}

int query(int x, int y) { 
    if(ans[x][y] != -1) return ans[x][y]; 

    printf("? %d %d\n", x, y);
    fflush(stdout);

    if(DEB) { 
        return ans[x][y] = answer(x, y);
    }
    int a;
    scanf("%d", &a);
    ans[x][y] = a;
    return ans[x][y];
}

void init(int n) { 
    for(int i = 1; i <= n; ++i) scanf("%d", p + i);
}

int main() { 
    memset(ans, -1, sizeof(ans));

    int n;
    scanf("%d", &n);

    if(n == 2) { 
        printf("? 1 2\n"); fflush(stdout);
        int x;
        scanf("%d", &x);

        printf("!\n"); fflush(stdout);

        int q;
        scanf("%d", &q);
        for(; q--; ) { 
            printf("%d\n", x);
        }

        return 0;
    }

    if(DEB) init(n);
    
    for(int i = 2; i <= n; ++i) { 
        query(1, i);
    }
    for(int i = 1; i < n; ++i) { 
        query(i, n);
    }

    bool flag = query(2, 3) == 3;

    printf("!\n");
    fflush(stdout);

    int q;
    scanf("%d", &q);
    for(; q--; ) {
        int l, r;
        scanf("%d%d", &l, &r);

        int res = 0;
        if(ans[l][r] != -1) { res = ans[l][r]; }
        else { res = flag ? l + 1 : r - 1; }

        printf("%d\n", res);

        if(DEB && res != answer(l, r)) { printf("noooo\n"); }
    }
    return 0;
}
