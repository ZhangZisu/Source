#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200000
int head[MAXN], next[MAXN << 1], to[MAXN << 1], tot = 0;
inline void addEdge(int u, int v) {
	next[tot] = head[u]; to[tot] = v; head[u] = tot++;
	next[tot] = head[v]; to[tot] = u; head[v] = tot++;
}
int fa[MAXN], size[MAXN], top[MAXN], dfn[MAXN], deep[MAXN], _index = 0;
void getSize(int x) {
	size[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] == fa[x])continue;
		fa[to[i]] = x; deep[to[i]] = deep[x] + 1; getSize(to[i]); size[x] += size[to[i]];
	}
}
void split(int x) {
	dfn[x] = ++_index;
	if (!~top[x])top[x] = x;
	int max = -1, mpos = -1;
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && size[to[i]] > max) {
			max = size[to[i]]; mpos = to[i];
		}
	if (~mpos) { top[mpos] = top[x]; split(mpos); }
	for (int i = head[x]; ~i; i = next[i])
		if (to[i] != fa[x] && to[i] != mpos)split(to[i]);
}
int color[MAXN], L[MAXN << 2], R[MAXN << 2], sum[MAXN << 2], lt[MAXN << 2];
inline void pushUp(int x) {
	L[x] = L[x << 1]; R[x] = R[x << 1 | 1];
	sum[x] = sum[x << 1] + sum[x << 1 | 1] - (R[x << 1] == L[x << 1 | 1]);
}
void Build(int n, int l, int r) {
	if (l == r) {
		L[n] = R[n] = color[l]; sum[n] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	Build(n << 1, l, mid); Build(n << 1 | 1, mid + 1, r);
	pushUp(n);
}
inline void pushDown(int n) {
	if (!~lt[n])return;
	L[n << 1] = L[n << 1 | 1] = R[n << 1] = R[n << 1 | 1] = lt[n];
	sum[n << 1] = sum[n << 1 | 1] = 1;
	lt[n << 1] = lt[n << 1 | 1] = lt[n]; lt[n] = -1;
}
void Modify(int n, int l, int r, int _l, int _r, int c) {
	if (l == _l && r == _r) {
		L[n] = R[n] = lt[n] = c; sum[n] = 1;
		return;
	}
	pushDown(n);
	int mid = (l + r) >> 1;
	if (_r <= mid)Modify(n << 1, l, mid, _l, _r, c);
	else if (_l > mid)Modify(n << 1 | 1, mid + 1, r, _l, _r, c);
	else Modify(n << 1, l, mid, _l, mid, c), Modify(n << 1 | 1, mid + 1, r, mid + 1, _r, c);
	pushUp(n);
}
int Query(int n, int l, int r, int _l, int _r) {
	if (l == _l && r == _r)return sum[n];
	pushDown(n);
	int mid = (l + r) >> 1;
	if (_r <= mid)return Query(n << 1, l, mid, _l, _r);
	if (_l > mid)return Query(n << 1 | 1, mid + 1, r, _l, _r);
	return Query(n << 1, l, mid, _l, mid) + Query(n << 1 | 1, mid + 1, r, mid + 1, _r) - (R[n << 1] == L[n << 1 | 1]);
}
int Left(int n, int l, int r, int pos) {
	if (l == r)return L[n]; pushDown(n); int mid = (l + r) >> 1;
	if (pos <= mid)return Left(n << 1, l, mid, pos); else return Left(n << 1 | 1, mid + 1, r, pos);
}
int Right(int n, int l, int r, int pos) {
	if (l == r)return R[n]; pushDown(n); int mid = (l + r) >> 1;
	if (pos <= mid)return Right(n << 1, l, mid, pos); else return Right(n << 1 | 1, mid + 1, r, pos);
}
int n;
inline int LCA(int x, int y) {
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]])std::swap(x, y);
		x = fa[top[x]];
	}
	if (deep[x] < deep[y])std::swap(x, y); return y;
}
inline int query(int u, int v) {
	int ans = 0, pre = -1, now;
	while (top[u] != top[v]) {
		ans += Query(1, 1, n, dfn[top[u]], dfn[u]);
		now = Right(1, 1, n, dfn[u]);
		if (now == pre)ans--; pre = Left(1, 1, n, dfn[top[u]]);
		u = fa[top[u]];
	}
	ans += Query(1, 1, n, dfn[v], dfn[u]);
	now = Right(1, 1, n, dfn[u]);
	if (now == pre)ans--;
	return ans;
}
inline void modify(int u, int v, int c) {
	while (top[u] != top[v]) {
		if (deep[top[u]] < deep[top[v]])std::swap(u, v);
		Modify(1, 1, n, dfn[top[u]], dfn[u], c); u = fa[top[u]];
	}
	if (deep[u] < deep[v])std::swap(u, v); Modify(1, 1, n, dfn[v], dfn[u], c);
}
int m, u, v, c, a[MAXN];
char buf[10];
int main() {
	memset(head, -1, sizeof(head)); memset(top, -1, sizeof(top)); memset(lt, -1, sizeof(lt));
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &u, &v);
		addEdge(u, v);
	}
	fa[1] = 1; deep[1] = 0; getSize(1); split(1);
	for (int i = 1; i <= n; i++)color[dfn[i]] = a[i];
	Build(1, 1, n);
	while (m--) {
		scanf("%s%d%d", buf, &u, &v);
		if (buf[0] == 'Q') {
			int lca = LCA(u, v);
			printf("%d\n", query(u, lca) + query(v, lca) - 1);
		}
		else {
			scanf("%d", &c);
			modify(u, v, c);
		}
	}
	system("pause");
	return 0;
}