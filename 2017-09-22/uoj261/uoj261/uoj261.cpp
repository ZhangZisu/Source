#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 700000
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; head[v] = tot++;
}
int n, m, u, v;
int w[MAXN], ans[MAXN], fa[MAXN][20], deep[MAXN];
void dfs(int x) {
	for (int i = head[x]; i != -1; i = next[i]) {
		if (to[i] == fa[x][0])continue;
		fa[to[i]][0] = x;
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
	}
}
inline int lca(int x, int y) {
	if (deep[x] < deep[y])std::swap(x, y);
	int delta = deep[x] - deep[y];
	for (int i = 19; i >= 0; i--) {
		if ((delta >> i) & 1)x = fa[x][i];
	}
	if (x == y)return x;
	for (int i = 19; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return x == y ? x : fa[x][0];
}
struct bkt {
	int head[MAXN], next[MAXN], to[MAXN], tot;
	bkt() { memset(head, -1, sizeof(head)); tot = 0; }
	inline void add(int x, int y) {
		next[tot] = head[x]; to[tot] = y; head[x] = tot++;
	}
}A, B, C, D;
int up[MAXN << 2], down[MAXN << 2];
void slove(int x) {
	int bak = up[deep[x] + w[x]] + down[deep[x] - w[x] + MAXN];
	for (int i = A.head[x]; ~i; i = A.next[i])up[A.to[i]]++;
	for (int i = C.head[x]; ~i; i = C.next[i])down[C.to[i] + MAXN]++;
	for (int i = head[x]; ~i; i = next[i])if (to[i] != fa[x][0])slove(to[i]);
	ans[x] = up[deep[x] + w[x]] + down[deep[x] - w[x] + MAXN] - bak;
	for (int i = B.head[x]; ~i; i = B.next[i])up[B.to[i]]--;
	for (int i = D.head[x]; ~i; i = D.next[i])down[D.to[i] + MAXN]--;
}
int s, t;
int main() {
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++)scanf("%d%d", &u, &v), addEdge(u - 1, v - 1);
	for (int i = 0; i < n; i++)scanf("%d", &w[i]);
	deep[0] = 1; dfs(0);
	for (int i = 1; i < 20; i++)
		for (int j = 0; j < n; j++)
			fa[j][i] = fa[fa[j][i - 1]][i - 1];
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &s, &t); s--; t--;
		int LCA = lca(s, t), len = deep[s] + deep[t] - 2 * deep[LCA];
		if (s == LCA) {
			C.add(t, deep[t] - len);
			D.add(s, deep[t] - len);
		}
		else if (t == LCA) {
			A.add(s, deep[s]);
			B.add(t, deep[s]);
		}
		else {
			A.add(s, deep[s]);
			B.add(LCA, deep[s]);
			C.add(t, deep[t] - len);
			for (int j = head[LCA]; ~j; j = next[j])if (to[j] != fa[LCA][0] && lca(to[j], t) == to[j]) {
				D.add(to[j], deep[t] - len);
				break;
			}
		}
	}
	slove(0);
	for (int i = 0; i < n; i++)printf("%d ", ans[i]);
	putchar(10);
	system("pause");
	return 0;
}