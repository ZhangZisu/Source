#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 20000
#define INF 0x3F3F3F3F
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; head[v] = tot++;
}
int col[MAXN], f[MAXN][2], n;
void DP(int x, int fa) {
	if (x <= n) {
		f[x][col[x]] = 1;
		f[x][!col[x]] = INF;
		return;
	}
	f[x][0] = f[x][1] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa)continue;
		DP(to[i], x);
		f[x][0] += std::min(f[to[i]][0] - 1, f[to[i]][1]);
		f[x][1] += std::min(f[to[i]][0], f[to[i]][1] - 1);
	}
}
int m, a, b;
int main() {
	scanf("%d%d", &m, &n); memset(head, -1, sizeof(head));
	for (int i = 1; i <= n; i++)scanf("%d", &col[i]);
	for (int i = 1; i < m; i++) {
		scanf("%d%d", &a, &b);
		addEdge(a, b);
	}
	DP(m, -1); printf("%d\n", std::min(f[m][0], f[m][1]));
	system("pause");
	return 0;
}