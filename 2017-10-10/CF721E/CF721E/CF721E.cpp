#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 100010
#define INF 0x3F3F3F3F
int sum, n, p, l, L[MAXN], R[MAXN], f[MAXN], g[MAXN], t;
int main() {
	scanf("%d%d%d%d", &sum, &n, &p, &l);
	for (int i = 1; i <= n; i++)scanf("%d%d", &L[i], &R[i]);
	f[0] = 0; g[0] = -INF; t = 1;
	for (int i = 1; i <= n; i++) {
		f[i] = f[i - 1]; g[i] = g[i - 1];
		for (t--; g[t] + l <= R[i] && t < i; t++) {
			int lR = std::max(L[i], g[t] + l);
			int nF = f[t] + (R[i] - lR) / p;
			int nG = R[i] - (R[i] - lR) % p;
			if (nF > f[i] || nF == f[i] && nG < g[i]) {
				f[i] = nF;
				g[i] = nG;
			}
		}
	}
	printf("%d\n", f[n]);
#ifdef DEBUG
	system("pause");
#endif
	return 0;
}