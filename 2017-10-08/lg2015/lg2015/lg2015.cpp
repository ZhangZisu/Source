#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot = 0;
inline void addEdge(int u, int v, int w) {
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
int L[MAXN], R[MAXN], V[MAXN];
void Build(int x, int fa) {
	bool first = 1; L[x] = R[x] = 0;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa)continue;
		if (first)L[x] = to[i], V[L[x]] += val[i], Build(L[x], x), first = 0;
		else R[x] = to[i], V[R[x]] += val[i], Build(R[x], x);
	}
}
int f[MAXN][MAXN];
int DP(int x, int q) {
	if (~f[x][q])return f[x][q];
	if (q == 0)return f[x][q] = 0;
	if (!L[x] && !R[x])return f[x][q] = V[x];
	f[x][q] = 0;
	for (int i = 0; i < q; i++)
		f[x][q] = std::max(f[x][q], DP(L[x], i) + DP(R[x], q - i - 1) + V[x]);
	return f[x][q];
}
void print(int x, int deep = 0) {
	for (int i = 0; i < deep; i++)putchar(' ');
	printf("%d - %d\n", x, V[x]);
	if (L[x])print(L[x], deep + 4);
	if (R[x])print(R[x], deep + 4);
}
int n, q, w[MAXN], x, y, z;
int main() {
	memset(head, -1, sizeof(head));
	memset(f, -1, sizeof(f));
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addEdge(x, y, z);
	}
	Build(1, -1);
	//print(1); puts("");
	DP(1, q + 1);
	printf("%d\n", f[1][q + 1]);
	system("pause");
	return 0;
}