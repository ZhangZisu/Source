#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define INF 0x3F3F3F3F
int Q, n, t[1005], b[1005], f[1010][300][20], ans;
int main() {
	scanf("%d", &Q);
	while (Q--) {
		memset(f, INF, sizeof(f));
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)scanf("%d%d", &t[i], &b[i]);
		f[1][0][-1 + 8] = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 1 << 8; ++j)
				for (int k = -8; k <= 7; ++k) {
					if (f[i][j][k + 8] == INF)continue;
					if (j & 1)f[i + 1][j >> 1][k - 1 + 8] = std::min(f[i + 1][j >> 1][k - 1 + 8], f[i][j][k + 8]);
					else {
						int lim = INF;
						for (int _i = 0; _i <= 7; ++_i)
							if (!(j&(1 << _i))) {
								if (i + _i > lim)break;
								lim = std::min(lim, i + _i + b[i + _i]);
								f[i][j + (1 << _i)][_i + 8] = std::min(
									f[i][j + (1 << _i)][_i + 8],
									f[i][j][k + 8] + (i + k <= 0 ? 0 : t[i + k] ^ t[i + _i])
								);
							}
					}
				}
		ans = INF;
		for (int i = -8; i <= 7; ++i)ans = std::min(ans, f[n + 1][0][i + 8]);
		printf("%d\n", ans);
	}
	system("pause");
	return 0;
}