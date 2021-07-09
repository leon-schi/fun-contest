#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;

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

int main(int argc, char* argv[]) {
    setName("describe your validator here");
    registerTestlibCmd(argc, argv);

    // Use inf (.in file), ouf (submission output) and ans (.ans file)
    // Use quit(_wa, message) or quitf(_wa, format_string, args...) to report wrong answers
    // Exchange _wa by _pe if the format is wrong (should mostly be taken care of by the
    // input functions of ouf)

    if (inf.seekEof()) {
        quit(_pe, "No input");
    }

    int n, m;
    n = inf.readInt();
    m = inf.readInt();

    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges[i] = {i+1, a, b};
    }
    
    if (ans.seekEof()) {
        quit(_pe, "No input");
    }
    string s = ans.readToken();
    
    if (s == "IMPOSSIBLE") {
        if (ouf.seekEof()) {
            quit(_pe, "No input");
        }

        string t = ouf.readString();
        if (s == t) {
            quit(_ok, "Well done!");
        } else {
            quit(_wa, "Graph has no eulerian cycle");
        }
    } else {
        // use validator function to check whether user output is a eulerian cycle
        if (ouf.seekEof()) {
            quit(_pe, "No input");
        }

        vector<int> circle;
        for (int i = 0; i < m; i++) {
            int id = ouf.readInt();
            circle.push_back(id);
        }
        if (!ouf.seekEof()) {
            quit(_pe, "You outputted more than m values");
        }

        try {
            if (validate_cycle(m, circle, edges)) {
                quit(_ok, "Well done!");
            } else {
                quit(_wa, "Your ourput is not a eulerian cycle");
            }
        } catch (const range_error& e) {
            quit(_pe, "You probably outputted a value that is not in the range 1 ... m");
        }
    }
    
    quit(_ok, "The program should terminate before this point. But apparently it didn't.");
}