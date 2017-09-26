#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 100010
template<int MAXE>
struct EDGE {
	int head[MAXN], to[MAXE], val[MAXE], next[MAXE], bl[MAXE], tot;
	EDGE() {
		memset(head, -1, sizeof(head)); tot = 0;
	}
	inline void addEdge(int u, int v, int w, int x) {
		next[tot] = head[u]; to[tot] = v; val[tot] = w; bl[tot] = x; head[u] = tot++;
	}
};
EDGE<MAXN << 1> A;
EDGE<2000000> B;
int size[MAXN], f[MAXN], root, sum, _index = 0, n;
void getRoot(int x, int pre) {
	size[x] = 1; f[x] = 0;
	for (int i = A.head[x]; ~i; i = A.next[i])if (A.bl[i] && A.to[i] != pre) {
		getRoot(A.to[i], x);
		size[x] += size[A.to[i]];
		f[x] = std::max(f[x], size[A.to[i]]);
	}
	f[x] = std::max(f[x], sum - size[x]);
	if (f[x] < f[root])root = x;
}
void dfsEdge(int x, int pre, int dis) {
	B.addEdge(x, root, dis, _index);
	for (int i = A.head[x]; ~i; i = A.next[i])
		if (A.bl[i] && A.to[i] != pre)
			dfsEdge(A.to[i], x, dis + A.val[i]);
}
void slove(int x) {
	for (int i = A.head[x]; ~i; i = A.next[i])if (A.bl[i]) {
		_index++; dfsEdge(A.to[i], x, A.val[i]);
	}
	for (int i = A.head[x]; ~i; i = A.next[i])if (A.bl[i]) {
		A.bl[i ^ 1] = 0; f[root = 0] = sum = size[A.to[i]];
		getRoot(A.to[i], 0); slove(root);
	}
}
int top[MAXN], dfn[MAXN], pos[MAXN], cnt = 0;
void getSize(int x, int pre) {
	size[x] = 1;
	for (int i = A.head[x]; ~i; i = A.next[i])if (A.to[i] != pre) {
		f[A.to[i]] = x;
		getSize(A.to[i], x);
		size[x] += size[A.to[i]];
	}
}
void split(int x) {
	if (!top[x])top[x] = x; pos[dfn[x] = ++cnt] = x;
	int t = 0, max = -1;
	for (int i = A.head[x]; ~i; i = A.next[i])
		if (A.to[i] != f[x] && size[A.to[i]] > max) { t = A.to[i]; max = size[A.to[i]]; }
	if (t)top[t] = top[x], split(t);
	for (int i = A.head[x]; ~i; i = A.next[i])
		if (A.to[i] != f[x] && A.to[i] != t)split(A.to[i]);
}
long long val[MAXN << 2], lt[MAXN << 2];
inline void pushDown(int x) {
	val[x << 1] += lt[x]; lt[x << 1] += lt[x];
	val[x << 1 | 1] += lt[x]; lt[x << 1 | 1] += lt[x];
	lt[x] = 0;
}
void Modify(int n, int l, int r, int L, int R, int v) {
	if (l == L && r == R) {
		val[n] += v;
		lt[n] += v;
		return;
	}
	pushDown(n);
	int mid = (l + r) >> 1;
	if (R <= mid)Modify(n << 1, l, mid, L, R, v);
	else if (L > mid)Modify(n << 1 | 1, mid + 1, r, L, R, v);
	else Modify(n << 1, l, mid, L, mid, v), Modify(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	val[n] = std::max(val[n << 1], val[n << 1 | 1]);
}
inline int findRoot(int n, int l, int r) {
	while (l < r) {
		pushDown(n); int mid = (l + r) >> 1;
		if (val[n << 1 | 1] * 2 < val[1]) {
			r = mid, n = n << 1;
		}
		else {
			l = mid + 1, n = n << 1 | 1;
		}
	}
	return pos[l];
}
long long value[MAXN], a[MAXN], a2[MAXN], b[MAXN], b2[MAXN];
void modify(int x, int y) {
	value[x] += y;
	for (int i = B.head[x]; ~i; i = B.next[i]) {
		a[B.to[i]] += y; a2[B.to[i]] += (long long)B.val[i] * y;
		b[B.bl[i]] += y; b2[B.bl[i]] += (long long)B.val[i] * y;
	}
	while (top[x] != 1)Modify(1, 1, n, dfn[top[x]], dfn[x], y), x = f[top[x]];
	Modify(1, 1, n, dfn[1], dfn[x], y);
}
inline long long query(int x) {
	long long ret = a2[x];
	for (int i = B.head[x]; ~i; i = B.next[i])
		ret += (a[B.to[i]] - b[B.bl[i]] + value[B.to[i]]) * B.val[i] + a2[B.to[i]] - b2[B.bl[i]];
	return ret;
}
int q, u, v, w;
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &u, &v, &w);
		A.addEdge(u, v, w, 1); A.addEdge(v, u, w, 1);
	}
	f[root = 0] = sum = n;
	getRoot(1, 0);
	slove(root); f[1] = 0;
	getSize(1, 0);
	split(1);
	while (q--) {
		scanf("%d%d", &u, &v);
		modify(u, v);
		printf("%lld\n", query(findRoot(1, 1, n)));
	}
	system("pause");
	return 0;
}