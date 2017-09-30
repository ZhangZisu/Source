#include<cstdio>
#include<cstdlib>
#include<cstring>
#undef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#define MAXN 2000
int head[MAXN], to[MAXN << 1], next[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
}
int map[MAXN][MAXN], Q[MAXN], H, T, go[MAXN][MAXN];
inline void BFS(int s) {
	Q[H = T = 0] = s; map[s][s] = 0;
	while (H <= T) {
		int x = Q[H++];
		for (int i = head[x]; ~i; i = next[i]) {
			if (!~map[s][to[i]]) {
				map[s][to[i]] = map[s][x] + 1;
				Q[++T] = to[i];
			}
		}
	}
}
double f[MAXN][MAXN];
bool F[MAXN][MAXN];
double dfs(int x, int y) {
	if (map[x][y] == 0)return 0;
	if (map[x][y] <= 2)return 1;
	if (F[x][y])return f[x][y];
	F[x][y] = 1; int cnt = 0;
	for (int i = head[y]; ~i; i = next[i], cnt++) {
		f[x][y] += dfs(go[go[x][y]][y], to[i]);
	}
	return f[x][y] = f[x][y] / cnt + 1.0;
}
int n, e, c, m, u, v;
int main() {
	memset(head, -1, sizeof(head)); memset(map, -1, sizeof(map));
	scanf("%d%d%d%d", &n, &e, &c, &m);
	for (int i = 0; i < e; i++) {
		scanf("%d%d", &u, &v); addEdge(u, v); addEdge(v, u);
	}
	for (int i = 1; i <= n; i++) {
		BFS(i);
		for (int j = 1; j <= n; j++) {
			if (i == j)continue;
			int min = 0x7FFFFFFF;
			for (int k = head[j]; ~k; k = next[k]) {
				if (map[i][to[k]] < min) {
					go[j][i] = to[k];
					min = map[i][to[k]];
				}
				else if (map[i][to[k]] == min) {
					go[j][i] = __min(go[j][i], to[k]);
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)addEdge(i, i);
	printf("%.3f\n", dfs(c, m));
	system("pause");
	return 0;
}