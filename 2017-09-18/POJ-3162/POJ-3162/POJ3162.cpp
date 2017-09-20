#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXN 1000010
#define INF 0x7FFFFFFF
int n, m, a, b;
int head[MAXN], next[MAXN << 1], to[MAXN << 1], val[MAXN << 1], tot;
inline void addEdge(int u, int v, int w) {
	next[tot] = head[u]; to[tot] = v; val[tot] = w; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; val[tot] = w; head[v] = tot++;
}
int dis0[MAXN], dis1[MAXN], _max, Q[MAXN], h, t;
inline void bfs0(int x) {
	memset(dis0, -1, sizeof(dis0));
	Q[h = t = dis0[x] = 0] = x; t++;
	while (h < t) {
		int now = Q[h++];
		if (dis0[_max] < dis0[now])_max = now;
		for (int i = head[now]; ~i; i = next[i]) {
			if (~dis0[to[i]])continue;
			dis0[to[i]] = dis0[now] + val[i];
			Q[t++] = to[i];
		}
	}
}
inline void bfs1(int x) {
	memset(dis1, -1, sizeof(dis1));
	Q[h = t = dis1[x] = 0] = x; t++;
	while (h < t) {
		int now = Q[h++];
		if (dis1[_max] < dis1[now])_max = now;
		for (int i = head[now]; ~i; i = next[i]) {
			if (~dis1[to[i]])continue;
			dis1[to[i]] = dis1[now] + val[i];
			Q[t++] = to[i];
		}
	}
}
int min[MAXN << 2], max[MAXN << 2];
void build(int n, int l, int r) {
	if (l == r) {
		min[n] = max[n] = dis0[l - 1];
		return;
	}
	int mid = (l + r) >> 1;
	build(n << 1, l, mid); build(n << 1 | 1, mid + 1, r);
	min[n] = __min(min[n << 1], min[n << 1 | 1]);
	max[n] = __max(max[n << 1], max[n << 1 | 1]);
}
int Min(int n, int l, int r, int L, int R) {
	if (L <= l && R >= r)return min[n];
	int ret = INF, mid = (l + r) >> 1;
	if (L <= mid)ret = __min(ret, Min(n << 1, l, mid, L, R));
	if (R > mid)ret = __min(ret, Min(n << 1 | 1, mid + 1, r, L, R));
	return ret;
}
int Max(int n, int l, int r, int L, int R) {
	if (L <= l && R >= r)return max[n];
	int ret = -INF, mid = (l + r) >> 1;
	if (L <= mid)ret = __max(ret, Max(n << 1, l, mid, L, R));
	if (R > mid)ret = __max(ret, Max(n << 1 | 1, mid + 1, r, L, R));
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	memset(head, -1, sizeof(head)); tot = 0; _max = 0;
	for (int i = 1; i < n; i++) { scanf("%d%d", &a, &b); addEdge(i, a - 1, b); }
	bfs0(_max); bfs1(_max); bfs0(_max);
	for (int i = 0; i < n; i++)dis0[i] = __max(dis0[i], dis1[i]);
	build(1, 1, n);
	int ans = 0, l = 1, r = 1;
	while (r <= n) {
		int Delta = Max(1, 1, n, l, r) - Min(1, 1, n, l, r);
		if (Delta <= m) {
			ans = __max(ans, r - l + 1);
			r++;
		}
		else {
			l++;
		}
	}
	printf("%d\n", ans);
	return 0;
}