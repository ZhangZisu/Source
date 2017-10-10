#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 5010
#define ABS(a) ((a)<0?-(a):(a))
#define INF 0x3F3F3F3F3F3F3F3F
long long n, m, x[MAXN], f[2][MAXN];
struct Hole {
	long long x, y;
	Hole(long long x = 0, long long y = 0) :x(x), y(y) {}
	inline friend bool operator < (const Hole &a, const Hole &b) {
		return a.x < b.x;
	}
}hole[MAXN];
long long s[MAXN], pre[MAXN], Q[MAXN], H, T;
int main() {
	scanf("%I64d%I64d", &n, &m);
	for (int i = 1; i <= n; i++)scanf("%I64d", &x[i]);
	for (int i = 1; i <= m; i++)scanf("%I64d%I64d", &hole[i].x, &hole[i].y);
	std::sort(x + 1, x + n + 1); std::sort(hole + 1, hole + m + 1);
	for (int i = 1; i <= m; i++)pre[i] = pre[i - 1] + hole[i].y;
	if (pre[m] < n) {
		puts("-1");
		return 0;
	}
	memset(f, 0x3F, sizeof(f));
	f[0][0] = 0;
	for (int i = 1; i <= m; i++) {
		f[i & 1][0] = 0;
		Q[H = T = 0] = 0;
		for (int j = 1; j <= n; j++) {
			s[j] = s[j - 1] + ABS(hole[i].x - x[j]);
		}
		for (int j = 1; j <= pre[i] && j <= n; j++) {
			f[i & 1][j] = f[!(i & 1)][j];
			while (j - Q[H] > hole[i].y)H++;
			while (H < T && f[!(i & 1)][Q[H]] - s[Q[H]] > f[!(i & 1)][Q[H + 1]] - s[Q[H + 1]])H++;
			f[i & 1][j] = std::min(f[i & 1][j], f[!(i & 1)][Q[H]] + s[j] - s[Q[H]]);
			Q[++T] = j;
		}
	}
	printf("%I64d\n", f[m & 1][n]);
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}