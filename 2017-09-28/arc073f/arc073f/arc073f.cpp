#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 200010
long long A[MAXN << 2], B[MAXN << 2], T[MAXN << 2];
inline void pushDown(int x) {
	if (!T[x])return;
	A[x << 1] += T[x]; A[x << 1 | 1] += T[x];
	B[x << 1] += T[x]; B[x << 1 | 1] += T[x];
	T[x << 1] += T[x]; T[x << 1 | 1] += T[x];
	T[x] = 0;
}
inline void pushUp(int x) {
	A[x] = std::min(A[x << 1], A[x << 1 | 1]);
	B[x] = std::min(B[x << 1], B[x << 1 | 1]);
}
void Insert(int n, int l, int r, int x, long long v) {
	if (l == r) {
		A[n] = std::min(A[n], v - x); B[n] = std::min(B[n], v + x); return;
	}
	pushDown(n); int mid = (l + r) >> 1;
	if (x <= mid)Insert(n << 1, l, mid, x, v);
	else Insert(n << 1 | 1, mid + 1, r, x, v);
	pushUp(n);
}
void Insert(int n, int l, int r, int L, int R, long long v) {
	if (l == L && r == R) {
		A[n] += v; B[n] += v; T[n] += v; return;
	}
	pushDown(n); int mid = (l + r) >> 1;
	if (R <= mid)Insert(n << 1, l, mid, L, R, v);
	else if (L > mid)Insert(n << 1 | 1, mid + 1, r, L, R, v);
	else Insert(n << 1, l, mid, L, mid, v), Insert(n << 1 | 1, mid + 1, r, mid + 1, R, v);
	pushUp(n);
}
long long a(int n, int l, int r, int L, int R) {
	if (l == L && r == R)return A[n];
	pushDown(n); int mid = (l + r) >> 1;
	if (R <= mid)return a(n << 1, l, mid, L, R);
	else if (L > mid)return a(n << 1 | 1, mid + 1, r, L, R);
	return std::min(a(n << 1, l, mid, L, mid), a(n << 1 | 1, mid + 1, r, mid + 1, R));
}
long long b(int n, int l, int r, int L, int R) {
	if (l == L && r == R)return B[n];
	pushDown(n); int mid = (l + r) >> 1;
	if (R <= mid)return b(n << 1, l, mid, L, R);
	else if (L > mid)return b(n << 1 | 1, mid + 1, r, L, R);
	return std::min(b(n << 1, l, mid, L, mid), b(n << 1 | 1, mid + 1, r, mid + 1, R));
}
int n, q, p[MAXN], x;
int main() {
	scanf("%d%d%d", &n, &q, &x);
	for (int i = 0; i <= q; i++)scanf("%d", &p[i]);
	memset(A, 0x3F, sizeof(A)); memset(B, 0x3F, sizeof(B));
	Insert(1, 1, n, x, 0);
	for (int i = 1; i <= q; i++) {
		long long now = std::min(a(1, 1, n, 1, p[i]) + p[i], b(1, 1, n, p[i], n) - p[i]);
		Insert(1, 1, n, 1, n, std::abs(p[i] - p[i - 1]));
		Insert(1, 1, n, p[i - 1], now);
	}
	long long ans = 0x7FFFFFFFFFFFFFFF;
	for (int i = 1; i <= n; i++) {
		ans = std::min(ans, a(1, 1, n, i, i) + i);
	}
	printf("%lld\n", ans);
	system("pause");
	return 0;
}