#include <bits/stdc++.h>
#define all(a) begin(a), end(a)
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define sz(x) (int)size(x)
#define endl '\n'

using namespace std;
using ll=long long;
using vi=vector<int>;
using vll=vector<ll>;
using ld=long double;

list<int> tour;
vector<int> to;
vector<vi> out;
vi in;
vi nextOut;

bool dfs(int v, list<int>::iterator ins) {
	if (nextOut[v] != sz(out[v])) {
		int e = out[v][nextOut[v]++];
		tour.insert(ins, e);
		dfs(to[e], ins);
		return true;
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int n,m; cin >> n >> m;
	to.resize(m);
	out.resize(n);
	in.resize(n);
	nextOut.resize(n);

	rep(i,0,m){ 
		int a, b; cin >> a >> b;
		out[--a].push_back(i);
		to[i] = --b;
		in[b]++;
	}

	rep(i,0,n) {
		if (in[i] != sz(out[i])) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}

	dfs(0, tour.end());
	auto ne = tour.begin();
	for (auto prev = optional<list<int>::iterator>(); !prev.has_value() || prev.value()!= tour.end(); prev = optional(ne++)) {
		int v = prev.has_value() ? to[*prev.value()] : 0;
		dfs(v, ne);
		ne = prev.has_value() ? next(prev.value()) : tour.begin();
	}

	for (auto ei : tour) cout << ei+1 << " ";
	
	return 0;
}
