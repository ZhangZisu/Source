#include<cstdio>
#include<cstdlib>
#define MAXN 1002
int n, m;
long long f1[MAXN][MAXN], f2[MAXN][MAXN], f3[MAXN][MAXN], f4[MAXN][MAXN], a[MAXN][MAXN], ans = 0;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%I64d", &a[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			f1[i][j] = __max(f1[i - 1][j], f1[i][j - 1]) + a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--)
			f2[i][j] = __max(f2[i - 1][j], f2[i][j + 1]) + a[i][j];
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= m; j++)
			f3[i][j] = __max(f3[i + 1][j], f3[i][j - 1]) + a[i][j];
	for (int i = n; i >= 1; i--)
		for (int j = m; j >= 1; j--)
			f4[i][j] = __max(f4[i + 1][j], f4[i][j + 1]) + a[i][j];
	for (int i = 2; i < n; i++)
		for (int j = 2; j < m; j++) {
			ans = __max(ans, f1[i][j - 1] + f4[i][j + 1] + f3[i + 1][j] + f2[i - 1][j]);
			ans = __max(ans, f1[i - 1][j] + f4[i + 1][j] + f3[i][j - 1] + f2[i][j + 1]);
		}
	printf("%I64d\n", ans);
	//system("pause");
	return 0;
}