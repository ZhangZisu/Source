#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 500010
int n, a[MAXN], f1[MAXN], f2[MAXN];
void DP(int l, int r, int L, int R, int f[]) {
	if (l > r || L > R) return;
	int pos = 0, mid = (l + r) >> 1; double max = 0;
	for (int i = L; i <= std::min(R, mid); i++)
		if ((double)a[i] + sqrt(mid - i) >= max)
			pos = i, max = (double)a[i] + sqrt(mid - i);
	f[mid] = a[pos] + ceil(sqrt(mid - pos));
	DP(l, mid - 1, L, pos, f);
	DP(mid + 1, r, pos, R, f);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)scanf("%d", &a[i]);
	DP(1, n, 1, n, f1);
	for (int i = 1; i <= (n >> 1); i++)std::swap(a[i], a[n - i + 1]);
	DP(1, n, 1, n, f2);
	for (int i = 1; i <= n; i++)printf("%d\n", std::max(f1[i], f2[n - i + 1]) - a[n - i + 1]);
	system("pause");
	return 0;
}