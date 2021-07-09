#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<queue<pair<int, int>>>;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read everything
    int n, m; cin >> n >> m;
    Graph G(n);
    vector<int> in(n, 0), out(n, 0);
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        G[a-1].push({b-1, i});
        out[a-1]++;
        in[b-1]++;
    }

    // check if in[a] == out[a] for each node a
    rep(i, n) {
        if (in[i] != out[i]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    // calculate the route
    vector<int> cycle(m);
    vector<int> in_edge(n, -1);
    queue<int> q;
    
    q.push(0);
    while (!q.empty()) {
        int start = q.front();
        q.pop();
        if (G[start].size() == 0) {
            continue;
        }

        auto [cur, first_edge_id] = G[start].front();
        G[start].pop();
        if (G[start].size() > 0) q.push(start);
    
        int last_edge_id = first_edge_id;
        do {
            in_edge[cur] = last_edge_id;
            auto [t, id] = G[cur].front();
            G[cur].pop();
            if (G[cur].size() > 0) q.push(cur);
            cycle[last_edge_id] = id;
            last_edge_id = id;
            cur = t;
        } while (cur != start);

        if (in_edge[start] > -1) {
            // insert into existing circle
            int edge_before_circle = in_edge[start];
            int edge_after_circle = cycle[edge_before_circle];

            cycle[edge_before_circle] = first_edge_id;
            cycle[last_edge_id] = edge_after_circle;
        } else {
            // close the circle
            in_edge[start] = last_edge_id;
            cycle[last_edge_id] = first_edge_id;
        }
    }

    int start = 2 % m;
    int cur = start;
    do {
        cout << cur + 1 << " ";
        cur = cycle[cur];
    } while (cur != start);
    cout << endl;
    return 0;
}