#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 2000
int t, n, k, m;
inline double fast_pow(double a, int p) {
	double ret = 1;
	while (p) {
		if (p & 1)ret *= a;
		a *= a;
		p >>= 1;
	}
	return ret;
}
double f[MAXN], a[MAXN];
int main() {
	scanf("%d", &t);
	for (int $ = 1; $ <= t; $++) {
		memset(f, 0, sizeof(f));
		scanf("%d%d%d", &n, &k, &m);
		for (int i = 0; i < n; i++)scanf("%lf", &a[i]);
		f[1] = a[0];
		for (int i = 2; i <= m; i++) {
			for (int j = 0; j < n; j++)f[i] += fast_pow(f[i - 1], j) * a[j];
		}
		printf("Case #%d: %.7f\n", $, fast_pow(f[m], k));
	}
	system("pause");
	return 0;
}