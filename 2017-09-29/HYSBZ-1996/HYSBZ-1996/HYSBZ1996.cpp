#include<cstdio>
#include<cstdlib>
#define MAXN 2000
#define MOD 19650827
int n, h[MAXN], f[MAXN][MAXN][2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)scanf("%d", &h[i]);
	for (int i = 1; i <= n; i++)f[i][i][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i - 1; j > 0; j--) {
			f[j][i][0] = (f[j][i][0] + f[j + 1][i][0] * (h[j] < h[j + 1])) % MOD;
			f[j][i][0] = (f[j][i][0] + f[j + 1][i][1] * (h[j] < h[i])) % MOD;
			f[j][i][1] = (f[j][i][1] + f[j][i - 1][0] * (h[i] > h[j])) % MOD;
			f[j][i][1] = (f[j][i][1] + f[j][i - 1][1] * (h[i] > h[i - 1])) % MOD;
		}
	}
	printf("%d\n", (f[1][n][1] + f[1][n][0]) % MOD);
	system("pause");
	return 0;
}