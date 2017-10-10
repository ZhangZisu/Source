#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0, MOD;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; head[v] = tot++;
}
int p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int n, m, x, y;
int main() {
	scanf("%d%d%d", &n, &m, &MOD);
	for (int i = 1; i <= n; i++)p[i] = i;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		addEdge(x, y);
		x = find(x); y = find(y);
		if (x != y)p[x] = y;
	}
	x = find(1);
	for (int i = 2; i <= n; i++)if (find(i) != x) {
		puts("-1"); puts("-1");
		return 0;
	}
	system("pause");
	return 0;
}