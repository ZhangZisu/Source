#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 210
int n, k, a[MAXN], b[MAXN], f[MAXN][MAXN << 5], ans;
long long x;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < MAXN; i++)for (int j = 0; j < (MAXN << 5); j++)f[i][j] = 0x80000000;
	f[0][0] = 0;
	for (int i = 0; i < n; i++) {
		scanf("%I64d", &x);
		while (!(x & 1)) {
			b[i]++; x >>= 1;
		}
		while (!(x % 5)) {
			a[i]++; x /= 5;
		}
		for (int j = i; j >= 0; j--) {
			for (int k = (j << 5); k >= 0; k--) {
				f[j + 1][k + a[i]] = __max(f[j + 1][k + a[i]], f[j][k] + b[i]);
			}
		}
	}
	for (int i = 0; i <= (n << 5); i++)ans = __max(ans, __min(i, f[k][i]));
	printf("%d\n", ans);
	//system("pause");
	return 0;
}