#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define endl "\n"

const ll INF = 1e15;
const int MOD = 1e9 + 7;
const double EPS = 1e-7;
const double PI = acos(-1.0);

struct SegmentTree {
    vector<ll> tree;
    vector<ll> lazy, l, r;
 
    SegmentTree(int size) : tree(4 * size), lazy(4 * size), l(4 * size), r(4 * size) {
        init(1, 0, size - 1);
    }
     
    // Functions to update when query changes =============================
 
    ll best(ll lCalc, ll rCalc) {
        return min(lCalc, rCalc);
    }
 
    void upd(int i) {
        tree[i] = best(tree[i << 1] + lazy[i << 1], tree[i << 1 | 1] + lazy[i << 1 | 1]);
    }
 
    void prob(int i) {
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
        lazy[i] = 0;
    }
 
    // ====================================================================
     
    void inc(int s, int e, ll v, int i = 1) {
        if(s > r[i] || e < l[i])
            return;
 
        if(s <= l[i] && e >= r[i]) {
            lazy[i] += v;
            return;
        }
     
        prob(i);
     
        inc(s, e, v, i << 1);
        inc(s, e, v, i << 1 | 1);
     
        upd(i);
    }
 
    ll qry(int s, int e, int i = 1) {
        if(s > r[i] || e < l[i]) // change the return value depending on the query
            return INF;
 
        if(s <= l[i] && e >= r[i]) // may change if the query change
            return tree[i] + lazy[i];
     
        prob(i);
     
        auto lCalc = qry(s, e, i << 1);
        auto rCalc = qry(s, e, i << 1 | 1);
     
        upd(i);
     
        return best(lCalc, rCalc);
    }
     
    void init(int i, int s, int e) {
        l[i] = s;
        r[i] = e;
 
        if(s == e) {
            return;
        }
     
        int m = s + ((e - s) >> 1);
 
        init(i << 1, s, m);
        init(i << 1 | 1, m + 1, e);
 
        upd(i);
    }
};

const int N = 1e6 + 5;

ll n, a[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) 
            cin >> a[i];

        SegmentTree st(n);

        ll sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += a[i];
            st.inc(i, i, sum);
        }

        ll ans = 0;
        for (int i = n - 1; ~i; --i) {
            if (st.qry(0, n - 1) >= 0)
                ++ans;
            st.inc(0, n - 1, a[i]);
            st.inc(i, i, a[i] - st.qry(i, i));
        }

        cout << ans << endl;
    }
}

