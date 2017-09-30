#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define __abs(a) ((a)<0?-(a):(a))
#define MAXN 100005
#define INF 1e20
#define EPS 1e-10
int n, stk[MAXN];
double f[MAXN];
struct node {
	double a, b, r, x, y, k; int id;
	inline node() {}
	inline node(int x) {
		scanf("%lf%lf%lf", &a, &b, &r); k = -a / b; id = x;
	}
	inline friend bool operator < (const node &a, const node &b) {
		return a.k > b.k;
	}
	inline void calc() {
		y = f[id] / (a * r + b);
		x = y * r;
	}
	inline void calc(int id) {
		y = f[id] / (a * r + b);
		x = y * r;
	}
}Q[MAXN], P[MAXN];
inline double slope(int x, int y) {
	if (!x)return INF;
	if (!y)return -INF;
	if (__abs(Q[x].x - Q[y].x) < EPS)return INF;
	return (Q[x].y - Q[y].y) / (Q[x].x - Q[y].x);
}
void slove(int l, int r) {
	if (l == r) {
		f[l] = std::max(f[l], f[l - 1]); Q[l].calc(l);
		return;
	}
	int mid = (l + r) >> 1, L = l, R = mid + 1;
	for (int i = l; i <= r; i++)if (Q[i].id <= mid)P[L++] = Q[i]; else P[R++] = Q[i];
	memcpy(Q + l, P + l, sizeof(node) * (r - l + 1));
	slove(l, mid);
	L = 0;
	for (int i = l; i <= mid; i++) {
		while (L > 1 && slope(stk[L], i) + EPS > slope(stk[L - 1], stk[L]))L--;
		stk[++L] = i;
	}
	stk[++L] = 0; R = 1;
	for (int i = mid + 1; i <= r; i++) {
		while (R < L && slope(stk[R], stk[R + 1]) + EPS > Q[i].k)R++;
		f[Q[i].id] = std::max(f[Q[i].id], Q[stk[R]].x * Q[i].a + Q[stk[R]].y * Q[i].b);
	}
	slove(mid + 1, r);
	L = l, R = mid + 1;
	for (int i = l; i <= r; i++) {
		if (L <= mid && (Q[L].x < Q[R].x || (__abs(Q[L].x - Q[R].x) < EPS && Q[L].y < Q[R].y) || R > r))P[i] = Q[L++];
		else P[i] = Q[R++];
	}
	memcpy(Q + l, P + l, sizeof(node) * (r - l + 1));
}
int main() {
	scanf("%d%lf", &n, &f[0]);
	for (int i = 1; i <= n; i++)Q[i] = node(i);
	std::sort(Q + 1, Q + n + 1);
	slove(1, n);
	printf("%.3lf\n", f[n]);
	system("pause");
	return 0;
}