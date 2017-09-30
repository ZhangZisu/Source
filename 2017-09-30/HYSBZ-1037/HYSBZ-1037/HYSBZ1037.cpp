#include<cstdio>
#include<cstdlib>
#include<cstring>
#undef __max
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define MOD 12345678
int n, m, k, f[2][200][30][30], ans = 0;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	f[0][0][0][0] = 1;
	for (int i = 0; i < n + m; i++) {
		memset(f[!(i & 1)], 0, sizeof(f[!(i & 1)]));
		for (int j = 0; j <= i && j <= m; j++) {
			for (int _i = 0; _i <= k; _i++) {
				for (int __i = 0; __i <= k; __i++) {
					f[!(i & 1)][j + 1][__max(_i - 1, 0)][__i + 1] += f[(i & 1)][j][_i][__i];
					f[!(i & 1)][j + 1][__max(_i - 1, 0)][__i + 1] %= MOD;
					f[!(i & 1)][j][_i + 1][__max(__i - 1, 0)] += f[(i & 1)][j][_i][__i];
					f[!(i & 1)][j][_i + 1][__max(__i - 1, 0)] %= MOD;
				}
			}
		}
	}
	for (int i = 0; i <= k; i++)for (int j = 0; j <= k; j++)ans = (ans + f[(n + m) & 1][m][i][j]) % MOD;
	printf("%d\n", ans);
	system("pause");
	return 0;
}