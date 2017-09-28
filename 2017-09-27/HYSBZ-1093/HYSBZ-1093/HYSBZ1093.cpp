#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<set>
using std::set;
#define MAXN 110000
#define MAXE 1100000
struct EDGE {
	int head[MAXN], to[MAXE], next[MAXE], tot;
	EDGE() {
		memset(head, -1, sizeof(head)); tot = 0;
	}
	inline void addEdge(int u, int v) { next[tot] = head[u]; to[tot] = v; head[u] = tot++; }
}A, B;
int dfn[MAXN], low[MAXN], stk[MAXN], ins[MAXN], top = 0, cnt = 0, scc[MAXN], sum[MAXN], _index = 0;
void Tarjan(int x) {
	dfn[x] = low[x] = ++_index; stk[++top] = x; ins[x] = 1;
	for (int i = A.head[x]; ~i; i = A.next[i]) {
		if (dfn[A.to[i]]) {
			if (ins[A.to[i]])low[x] = std::min(low[x], dfn[A.to[i]]);
		}
		else {
			Tarjan(A.to[i]); low[x] = std::min(low[x], low[A.to[i]]);
		}
	}
	if (dfn[x] == low[x]) {
		int t;
		do {
			t = stk[top--]; scc[t] = cnt; sum[cnt]++; ins[t] = 0;
		} while (t != x);
		cnt++;
	}
}
int f[MAXN], in[MAXN], Q[MAXN], head, tail, n, m, u, v, ans = 0;
long long g[MAXN], mod, res = 0;
inline void DP() {
	head = 0; tail = 0;
	for (int i = 0; i < cnt; i++) {
		if (!in[i])Q[tail++] = i;
		g[i] = 1, f[i] = sum[i];
	}
	while (head < tail) {
		int now = Q[head++];
		for (int i = B.head[now]; ~i; i = B.next[i]) {
			if (sum[B.to[i]] + f[now] > f[B.to[i]]) {
				g[B.to[i]] = g[now]; f[B.to[i]] = sum[B.to[i]] + f[now];
			}
			else if (sum[B.to[i]] + f[now] == f[B.to[i]]) {
				g[B.to[i]] += g[now]; g[B.to[i]] %= mod;
			}
			if (!--in[B.to[i]])Q[tail++] = B.to[i];
		}
	}
}
set<int> S;
int main() {
	scanf("%d%d%lld", &n, &m, &mod);
	memset(scc, -1, sizeof(scc));
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v); A.addEdge(u - 1, v - 1);
	}
	for (int i = 0; i < n; i++)if (!dfn[i])Tarjan(i);
	for (int i = 0; i < n; i++)
		for (int j = A.head[i]; ~j; j = A.next[j]) {
			if (S.count(scc[i] * cnt + scc[A.to[j]]))continue; S.insert(scc[i] * cnt + scc[A.to[j]]);
			if (scc[i] != scc[A.to[j]])B.addEdge(scc[i], scc[A.to[j]]), in[scc[A.to[j]]]++;
		}
	DP();
	for (int i = 0; i < cnt; i++)ans = std::max(ans, f[i]);
	for (int i = 0; i < cnt; i++)if (f[i] == ans)res = (res + g[i]) % mod;
	printf("%d\n%lld\n", ans, res);
	system("pause");
	return 0;
}