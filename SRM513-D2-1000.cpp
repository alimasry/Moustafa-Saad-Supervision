#include <bits/stdc++.h>

using namespace std;

int n, m;

vector<string> G;

int solve(vector<int> pre, int value, int row = 0) {
	if (row == n) {
		for (auto x : pre)
			value += x;
		return value;
	}
	int ret = value;
	for (int mask = 0; mask < (1 << m); ++mask) {
		int curValue = value, tmp = 0;
		vector<int> nxt = pre;
		for (int i = 0; i < m; ++i) {
			if (mask & (1 << i)) {
				curValue += nxt[i];
				tmp = tmp * 10 + (G[row][i] - '0');
				nxt[i] = 0;
			} else {
				curValue += tmp;
				tmp = 0;
				nxt[i] = nxt[i] * 10 + (G[row][i] - '0');
			}
		}
		curValue += tmp;
		ret = max(ret, solve(nxt, curValue, row + 1));		
	}
	return ret;
}

class CutTheNumbers {
	public:
	int maximumSum(vector <string> board) {
		n = (int) board.size();
		m = (int) board[0].size();
		G = board;
		vector<int> cur(m);
		return solve(cur, 0);
	}
};
