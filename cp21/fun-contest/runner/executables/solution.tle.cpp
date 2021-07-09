#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using Graph = vector<queue<pair<int, int>>>;
using ll = long long;

struct edge {
    int id, a, b;
};

void check_edge_bounds(int x, int m) {
    if (x >= 1 && x <= m) {
        return;
    } else {
        throw range_error("A value is not in the range 1 to m");
    }
}

bool validate_cycle(int m, vector<int>& circle, vector<edge>& edges) {
    // each edge is visited exactly once
    // the we use only edges that are actually outgoing edges of the current node
    // the end node is the start node

    if (circle.size() != edges.size())
        return false;

    vector<bool> visited(m);

    try {
        int start_edge = circle[0];
        check_edge_bounds(start_edge, m);

        visited[(size_t)start_edge-1] = true;
        int cur_node = edges[(size_t)start_edge-1].b;

        for (size_t i = 1; i < circle.size(); i++) {
            int cur_edge = circle[i];
            check_edge_bounds(cur_edge, m);

            // visit all edges
            visited[(size_t)cur_edge-1] = true;

            // path must be valid
            if (edges[(size_t)cur_edge-1].a != cur_node)
                return false;

            cur_node = edges[(size_t)cur_edge-1].b;
        }

        // end node must be start node
        int start_node = edges[(size_t)start_edge-1].a;
        if (start_node != cur_node)
            return false;

        // all edges visited
        for (bool v : visited) {
            if (!v) return false;
        }
    } catch (const range_error& e) {
        throw;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read everything
    int n, m; cin >> n >> m;
    Graph G(n);
    vector<int> in(n, 0), out(n, 0);
    vector<int> p(m);
    vector<edge> edges(m);
    rep(i, m) {
        p[i] = m - i;
        int a, b;
        cin >> a >> b;
        edges[i] = {i+1, a, b};
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

    int i = 0;
    do {
        if (validate_cycle(m, p, edges)) break;
        i++;
    } while (next_permutation(all(p)) && i < 1000000000000);

    for (int e : p) {
        cout << e << " ";
    }
    cout << endl;
}