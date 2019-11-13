#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;

#define endl "\n"

const ll INF = 1e15;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;
const double PI = acos(-1.0);

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

ll t, n, k;
string s;

vector<bool> get_bin(ll x) {
    vector<bool> ret;
    for (int i = 0; i < k; ++i) {
        ret.push_back(x & 1);
        x >>= 1;
    }
    return x ? vector<bool>() : ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> t;

    while (t--) {
        cin >> k >> s >> n;
        reverse(s.begin(), s.end());
        if (n < 0) {
            n = -n;
            for (int i = 0; i < k; ++i)
                s[i] = s[i] == 'p' ? 'n' : 'p';
        }

        vector<bool> bn = get_bin(n);

        if (bn.empty()) {
            cout << "Impossible" << endl;
            continue;
        }


        bool valid = true;
        string ans;
        for (int i = 0; i < k; ++i) {
            if (!bn[i]) {
                ans += '0';
                continue;
            }
            ans += '1';
            if (s[i] == 'n') {
                valid = false;
                for (int j = i; j < k; ++j) { // update all ones to 0s until the next 0
                    bn[j] = !bn[j];
                    if (bn[j]) {
                        valid = true;
                        break;
                    }
                }
                if (!valid)
                    break;
            }
        }

        reverse(ans.begin(), ans.end());
        if (valid)
            cout << ans << endl;
        else
            cout << "Impossible" << endl;
    }
}
