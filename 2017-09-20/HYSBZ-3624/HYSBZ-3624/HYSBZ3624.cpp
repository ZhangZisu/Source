#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXN 40000
#define MAXE 200000
int p[MAXN];
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
int ans[MAXN][3], cans = 0;
struct EDGE {
	int to[MAXE], from[MAXE], lt[MAXE], tot, cnt, kind;
	EDGE(int kind) :kind(kind) {}
	inline void addEdge(int u, int v) {
		to[tot] = v; from[tot] = u; tot++;
	}
	inline void kruskal(bool print = false, int lim = 0x3FFFFFFF) {
		for (int i = 0; i < tot; i++) {
			if (cnt >= lim)break;
			int U = find(from[i]), V = find(to[i]);
			if (U == V)continue;
			cnt++; lt[i] = true; p[U] = V;
			if (print) { ans[cans][0] = from[i]; ans[cans][1] = to[i]; ans[cans][2] = kind; cans++; }
		}
	}
	inline void pre_kruskal() {
		for (int i = 0; i < tot; i++) {
			if (lt[i]) {
				int U = find(from[i]), V = find(to[i]);
				if (U == V)continue;
				cnt++; p[U] = V;
				ans[cans][0] = from[i]; ans[cans][1] = to[i]; ans[cans][2] = kind; cans++;
			}
		}
	}
}A(1), B(0);
int n, m, k, a, b, c;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	B.cnt = 0; A.cnt = 0;
	B.tot = 0; A.tot = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &a, &b, &c);
		if (c) {
			A.addEdge(a, b);
		}
		else {
			B.addEdge(a, b);
		}
	}
	for (int i = 1; i <= n; i++)p[i] = i;
	A.kruskal(); B.kruskal();
	if (A.cnt + B.cnt != n - 1 || B.cnt > k) {
		printf("no solution\n");
		return 0;
	}
	for (int i = 1; i <= n; i++)p[i] = i;
	B.cnt = 0; A.cnt = 0;
	B.pre_kruskal(); B.kruskal(1, k); A.kruskal(1);
	if (B.cnt < k) {
		printf("no solution\n");
		return 0;
	}
	for (int i = 0; i < cans; i++)printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	system("pause");
	return 0;
}