#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 1005
#define INF 0x2FFFFFFF
int head[MAXN], to[MAXN << 1], next[MAXN << 1], val[MAXN << 1], tot;
int w[MAXN], d[MAXN], n;
inline void addEdge(int u, int v, int w) {
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
int dis[MAXN], Q[MAXN << 1], h, t;
int f[MAXN][MAXN], best[MAXN];
inline void getDis(int x) {
	memset(dis, -1, sizeof(dis));
	Q[h = t = dis[x] = 0] = x; t++;
	while (h < t) {
		int x = Q[h++];
		for (int i = head[x]; ~i; i = next[i]) {
			if (~dis[to[i]])continue;
			dis[to[i]] = dis[x] + val[i];
			Q[t++] = to[i];
		}
	}
}
void dfs(int x, int pre) {
	for (int i = head[x]; ~i; i = next[i])if (to[i] != pre)dfs(to[i], x);
	getDis(x);
	best[x] = INF;
	for (int i = 0; i < n; i++) {
		if (dis[i] > d[x])f[x][i] = INF;
		else {
			f[x][i] = w[i];
			for (int j = head[x]; ~j; j = next[j]) {
				if (to[j] != pre)f[x][i] += std::min(best[to[j]], f[to[j]][i] - w[i]);
			}
			best[x] = std::min(best[x], f[x][i]);
		}
	}
}
int _;
int main() {
	scanf("%d", &_);
	while (_--) {
		scanf("%d", &n);
		memset(head, -1, sizeof(head)); tot = 0;
		for (int i = 0; i < n; i++)scanf("%d", &w[i]);
		for (int i = 0; i < n; i++)scanf("%d", &d[i]);
		for (int i = 1; i < n; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			addEdge(u - 1, v - 1, w);
		}
		dfs(0, -1);
		printf("%d\n", best[0]);
	}
	return 0;
}