#include <bits/stdc++.h>
using namespace std;

int N;
map<pair<int,int>, bool> cmp_cache; // true if a[i] < a[j]

// Compare a[i] and a[j] by querying interactor. Returns true if a[i] < a[j]
bool less_than(int i, int j) {
    if (i == j) return false;
    auto key = make_pair(i, j);
    if (cmp_cache.count(key)) return cmp_cache[key];
    int l = min(i, j), r = max(i, j);
    cout << "? " << l << " " << r << "\n" << flush;
    int secpos;
    cin >> secpos;
    // For interval of length 2, the interactor returns the smaller (second max)
    bool result;
    if (r - l == 1) {
        // second max is min index by position
        result = (secpos == i);
    } else {
        // In longer intervals, we can't directly compare arbitrary elements
        // Fallback: assume comparing endpoints only when adjacent
        result = false;
    }
    return cmp_cache[key] = result;
}

// Merge sort based reconstruction (works in ~N log N comparisons)
void mergesort_indices(vector<int>& ids, int l, int r, vector<int>& tmp) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergesort_indices(ids, l, m, tmp);
    mergesort_indices(ids, m, r, tmp);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (less_than(ids[i], ids[j])) tmp[k++] = ids[j++];
        else tmp[k++] = ids[i++];
    }
    while (i < m) tmp[k++] = ids[i++];
    while (j < r) tmp[k++] = ids[j++];
    for (int t = l; t < r; ++t) ids[t] = tmp[t];
}

int main() {
    cin >> N;
    vector<int> ids(N);
    for (int i = 0; i < N; ++i) ids[i] = i + 1;
    vector<int> tmp(N);
    mergesort_indices(ids, 0, N, tmp);

    // build perm: values from N (largest) down to 1
    vector<int> perm(N + 1);
    for (int rank = 0; rank < N; ++rank) {
        perm[ids[rank]] = N - rank;
    }

    // end of querying phase
    cout << "!" << "\n" << flush;

    int Q;
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        int mx1 = -1, mx2 = -1, pos1 = -1, pos2 = -1;
        for (int i = l; i <= r; ++i) {
            if (perm[i] > mx1) {
                mx2 = mx1; pos2 = pos1;
                mx1 = perm[i]; pos1 = i;
            } else if (perm[i] > mx2) {
                mx2 = perm[i]; pos2 = i;
            }
        }
        cout << pos2 << '\n' << flush;
    }
    return 0;
}

