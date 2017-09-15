#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 100000
#define MAXM 200000
int head[MAXN], to[MAXM << 1], next[MAXM << 1], tot = 0, cnt = 0, n, m, u, v;
long long val[MAXM << 1], _xor[MAXN], __xor[MAXM << 1], ans, w, lb[70];
bool vst[MAXN];
inline void addEdge(int u, int v, long long w) {
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
inline void dfs(int x) {
	vst[x] = true;
	for (int i = head[x]; ~i; i = next[i]) {
		if (vst[to[i]]) { __xor[cnt++] = _xor[x] ^ val[i] ^ _xor[to[i]]; }
		else { _xor[to[i]] = val[i] ^ _xor[x];	dfs(to[i]); }
	}
}
inline void insert_lb(long long x) {
	for (int i = 63; i >= 0; i--) {
		if ((x >> i) & 1) {
			if (lb[i]) { x = x ^ lb[i]; }
			else { lb[i] = x; break; }
		}
	}
}
int main() {
	scanf("%d%d", &n, &m); memset(head, -1, sizeof(head));
	while (m--) {
		scanf("%d%d%lld", &u, &v, &w);
		addEdge(u - 1, v - 1, w);
	}
	dfs(0); ans = _xor[n - 1];
	for (int i = 0; i < cnt; i++)insert_lb(__xor[i]);
	for (int i = 63; i >= 0; i--)if ((ans ^ lb[i]) > ans)ans = ans ^ lb[i];
	printf("%lld\n", ans);
	system("pause");
	return 0;
}