#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 500010
int head[MAXN], next[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot = 0;
inline void addEdge(int u, int v, int w) {
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
long long f[MAXN], ans = 0;
void DFS(int x, int fa) {
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa)continue; DFS(to[i], x);
		f[x] = std::max(f[x], f[to[i]] + val[i]);
	}
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa)continue;
		ans += f[x] - f[to[i]] - val[i];
	}
}
int n, s, a, b, t;
int main() {
	scanf("%d%d", &n, &s); memset(head, -1, sizeof(head));
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &a, &b, &t);
		addEdge(a, b, t);
	}
	DFS(s, 0);
	printf("%lld\n", ans);
	system("pause");
	return 0;
}