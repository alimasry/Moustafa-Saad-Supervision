// Solution:
//
// have a mask of preferences in which each bit represent which rumor does the current rabbit preffer to spread first 
// and then we simulate each day and if he can take his first prefference and he hasen't spread it before he take it
// otherwise if he can take the second prefference and hasen't taken before he takes it
//
// the answer is then the minimum among all masks

#include <bits/stdc++.h>
 
using namespace std;
 
const int INF = 2e9;
 
class Rumor  {
    public:
    int getMinimum(string knowledge, vector <string> graph) {
   
        int n = (int) knowledge.size();
        vector<int> knows(n), G[n];
       
        for (int i = 0; i < n; ++i)
            if (knowledge[i] == 'Y')
                knows[i] = 3;
               
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (graph[i][j] == 'Y')
                    G[i].push_back(j);
       
        int best = INF;
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<vector<bool>> vis(2, vector<bool>(n));
            vector<int> knows(n);
            queue<pair<int, bool>> q;
            for (int i = 0; i < n; ++i)
                if (knowledge[i] == 'Y') {
                    knows[i] = 3;
                    vis[(mask & (1 << i)) != 0][i] = 1;
                    q.push({i, (mask & (1 << i)) != 0});
                }
               
             queue<int> nxt;
             int cnt = 0;
             while (!q.empty() || !nxt.empty()) {
                bool done = true;
               
                for (int i = 0; i < n; ++i)
                    if (knows[i] != 3)
                        done = false;
                       
                if (done) break;
               
                while (!q.empty()) {
                    auto r = q.front();
                    q.pop();
                    int u = r.first;
                    bool p = r.second;
                    nxt.push(u);
                    for (auto to : G[u]) {
                        knows[to] |= (1 << p);
                        nxt.push(to);
                    }
                 }
                 vector<bool> used(n);
                 while (!nxt.empty()) {
                    int u = nxt.front();
                    nxt.pop();
                    if (used[u])
                        continue;
                     used[u] = true;
                    bool want = (mask & (1 << u)) != 0;
                    if ((knows[u] & (1 << want)) != 0 && vis[want][u] == false) {
                        q.push({u, want});
                        vis[want][u] = true;
                    } else if ((knows[u] & (1 << (!want))) != 0 && vis[!want][u] == false) {
                        q.push({u, !want});
                        vis[!want][u] = true;
                    }
                 }
                ++cnt;
            }
            bool ok = true;
            for (int i = 0; i < n; ++i)
                ok &= (knows[i] == 3);
            if (ok)
                best = min(best, cnt);
        }
       
        return best == INF ? -1 : best;
    }
};
