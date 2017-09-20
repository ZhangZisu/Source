#include<cstdio>
#include<cstdlib>
#include<cstring>
#define __max(a,b) ((a)>(b)?(a):(b))
#define __min(a,b) ((a)<(b)?(a):(b))
#include<set>
using std::set;
#include<queue>
using std::priority_queue;
#define MAXN 500000
int _head_[MAXN], _next_[MAXN], _to_[MAXN], _tot_ = 0;
inline void _addEdge(int u, int v) {
	_next_[_tot_] = _head_[u]; _to_[_tot_] = v; _head_[u] = _tot_++;
}
int dfn[MAXN], low[MAXN], scc[MAXN], ins[MAXN], stk[MAXN], top = 0, cnt = 0, idx = 1;
void Tarjin(int x) {
	dfn[x] = low[x] = idx++;
	stk[top++] = x; ins[x] = 1;
	for (int i = _head_[x]; ~i; i = _next_[i]) {
		if (dfn[_to_[i]]) {
			if (ins[_to_[i]])low[x] = __min(low[x], dfn[_to_[i]]);
		}
		else {
			Tarjin(_to_[i]);
			low[x] = __min(low[x], low[_to_[i]]);
		}
	}
	if (low[x] == dfn[x]) {
		int t;
		do {
			t = stk[--top];
			scc[t] = cnt;
			ins[t] = 0;
		} while (t != x);
		cnt++;
	}
}
int head[MAXN], next[MAXN], to[MAXN], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
}
int n, m, u, v, s, p;
int val[MAXN], ak[MAXN], max[MAXN], ans;
struct node {
	int x, val;
	inline friend bool operator < (const node &a, const node &b) {
		return a.val < b.val;
	}
	node() {}
	node(int x, int val) :x(x), val(val) {}
};
priority_queue<node> Q;
inline void dijkstra(int s) {
	Q.push(node(s, max[s] = val[s]));
	while (!Q.empty()) {
		node top = Q.top(); Q.pop();
		if (ak[top.x])ans = __max(ans, top.val);
		for (int i = head[top.x]; ~i; i = next[i]) {
			if (top.val + val[to[i]] > max[to[i]])Q.push(node(to[i], max[to[i]] = top.val + val[to[i]]));
		}
	}
}
set<int> S;
int main() {
	scanf("%d%d", &n, &m);
	memset(_head_, -1, sizeof(_head_));
	memset(head, -1, sizeof(head));
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		_addEdge(u - 1, v - 1);
	}
	for (int i = 0; i < n; i++)if (!dfn[i])Tarjin(i);
	for (int i = 0; i < n; i++) {
		scanf("%d", &u);
		val[scc[i]] += u;
	}
	scanf("%d%d", &s, &p);
	for (int i = 0; i < p; i++) {
		scanf("%d", &u);
		ak[scc[u - 1]] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int I = _head_[i]; ~I; I = _next_[I]) {
			if (scc[i] == scc[_to_[I]])continue;
			int hash = ((long long)scc[i] * MAXN + scc[_to_[I]]) % 1000000007;
			if (!S.count(hash)) {
				S.insert(hash);
				addEdge(scc[i], scc[_to_[I]]);
			}
		}
	}
	dijkstra(scc[s - 1]);
	printf("%d\n", ans);
	return 0;
}