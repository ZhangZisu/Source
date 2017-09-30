#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 100010
#define INF 0x7FFFFFFFFFFLL
#define __abs(a) ((a)<0?-(a):(a))
int n, a[MAXN], b[MAXN];
long long f[MAXN];
inline long long _abs(int x, int y) {
	return a[x] == b[y] ? INF : __abs(a[x] - b[y]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)scanf("%d%d", &a[i], &b[i]);
	std::sort(a + 1, a + n + 1); std::sort(b + 1, b + n + 1);
	f[1] = _abs(1, 1);
	f[2] = std::min(f[1] + _abs(2, 2), _abs(1, 2) + _abs(2, 1));
	for (int i = 3; i <= n; i++) {
		f[i] = f[i - 1] + _abs(i, i);
		f[i] = std::min(f[i], f[i - 2] + _abs(i - 1, i) + _abs(i, i - 1));
		f[i] = std::min(f[i], f[i - 3] + _abs(i - 2, i) + _abs(i - 1, i - 2) + _abs(i, i - 1));
		f[i] = std::min(f[i], f[i - 3] + _abs(i, i - 2) + _abs(i - 1, i) + _abs(i - 2, i - 1));
		f[i] = std::min(f[i], f[i - 3] + _abs(i, i - 2) + _abs(i - 1, i - 1) + _abs(i - 2, i));
	}
	printf("%lld\n", f[n] >= INF ? -1 : f[n]);
	system("pause");
	return 0;
}