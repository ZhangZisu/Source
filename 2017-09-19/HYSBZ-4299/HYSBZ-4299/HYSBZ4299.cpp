#include<cstdio>
#include<cstdlib>
#define MAXN 100000
#define POOL 5000000
#define INF 1000000000
int L[POOL], R[POOL], sum[POOL], tot = 0;
inline int newNode(int old) {
	if (old == -1) { L[tot] = R[tot] = -1; sum[tot] = 0; }
	else { L[tot] = L[old]; R[tot] = R[old]; sum[tot] = sum[old]; }
	return tot++;
}
int insert(int l, int r, int a, int old) {
	if (l == r) {
		int ret = newNode(old);
		sum[ret] += a;
		return ret;
	}
	int mid = (l + r) >> 1;
	int ret = newNode(old);
	sum[ret] += a;
	if (a <= mid) { L[ret] = insert(l, mid, a, L[old]); }
	else { R[ret] = insert(mid + 1, r, a, R[old]); }
	return ret;
}
int query(int l, int r, int x, int r0, int r1) {
	if (l == r) { return sum[r1] - sum[r0]; }
	int mid = (l + r) >> 1;
	if (x <= mid)return query(l, mid, x, L[r0], L[r1]);
	return sum[L[r1]] - sum[L[r0]] + query(mid + 1, r, x, R[r0], R[r1]);
}
int n, l, r, root[MAXN];
int main() {
	scanf("%d", &n);
	root[0] = newNode(-1);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &l);
		root[i] = insert(1, INF, l, root[i - 1]);
	}
	scanf("%d", &n);
	while (n--) {
		scanf("%d%d", &l, &r);
		int ans = 1;
		while (1) {
			int ret = query(1, INF, ans, root[l - 1], root[r]);
			if (ret < ans)break;
			ans = ret + 1;
		}
		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}