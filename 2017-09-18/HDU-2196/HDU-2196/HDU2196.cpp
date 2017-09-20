#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 10000
int head[MAXN], next[MAXN << 1], to[MAXN << 1], dis[MAXN << 1], tot, n, u, v;
int dis0[MAXN], dis1[MAXN], max;
inline void addEdge(const int &u, const int &v, const int &w) {
	next[tot] = head[u]; to[tot] = v; dis[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; dis[tot] = w; head[v] = tot++;
}
inline void dfs0(int x, int f) {
	if (dis0[x] > dis0[max])max = x;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == f)continue;
		dis0[to[i]] = std::max(dis0[to[i]], dis0[x] + dis[i]);
		dfs0(to[i], x);
	}
}
inline void dfs1(int x, int f) {
	if (dis1[x] > dis1[max])max = x;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == f)continue;
		dis1[to[i]] = std::max(dis1[to[i]], dis1[x] + dis[i]);
		dfs1(to[i], x);
	}
}
int main() {
	while (~scanf("%d", &n)) {
		memset(head, -1, sizeof(head)); tot = 0;
		max = 0;
		for (int i = 1; i < n; i++) {
			scanf("%d%d", &u, &v);
			addEdge(i, u - 1, v);
		}
		memset(dis0, 0, sizeof(dis0)); dfs0(0, -1);
		memset(dis1, 0, sizeof(dis1)); dfs1(max, -1);
		memset(dis0, 0, sizeof(dis0)); dfs0(max, -1);
		for (int i = 0; i < n; i++)printf("%d\n", std::max(dis0[i], dis1[i]));
	}
	return 0;
}