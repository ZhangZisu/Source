#include<cstdio>
#include<cstdlib>
#include<cstring>
#undef __max
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define MAXN 2010
int t, p, w, a, b, c, d, f[MAXN][MAXN], X[MAXN], Y[MAXN], H, T, ans;
int main() {
	scanf("%d%d%d", &t, &p, &w);
	memset(f, 0x80, sizeof(f));
	for (int i = 1; i <= t; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);
		for (int j = 0; j <= c; j++)f[i][j] = -j * a;
		for (int j = 0; j <= p; j++)f[i][j] = __max(f[i][j], f[i - 1][j]);
		int k = i - w - 1;
		if (k >= 0) {
			H = 0; T = -1;
			for (int j = 0; j <= p; j++) {
				while (H <= T && X[H] < j - c)H++;
				while (H <= T && Y[T] <= f[k][j] + a * j)T--;
				X[++T] = j; Y[T] = f[k][j] + a * j;
				if (H <= T)f[i][j] = __max(f[i][j], Y[H] - a * j);
			}
			H = 0; T = -1;
			for (int j = p; j >= 0; j--) {
				while (H <= T && X[H] > j + d)H++;
				while (H <= T && Y[T] <= f[k][j] + b * j)T--;
				X[++T] = j; Y[T] = f[k][j] + b * j;
				if (H <= T)f[i][j] = __max(f[i][j], Y[H] - b * j);
			}
		}
		ans = __max(ans, f[i][0]);
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}