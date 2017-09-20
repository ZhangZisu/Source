#include<cstdio>
#include<cstdlib>
#define MAXN 100
int f[MAXN][MAXN], a[MAXN], n;
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)scanf("%d", &a[i]);
	for (int i = 2; i < n; i++) {
		for (int j = 0; j + i < n; j++) {
			f[j][j + i] = 0x7FFFFFFF;
			for (int k = j + 1; k < j + i; k++)
				f[j][j + i] = __min(f[j][j + i], a[k] * a[j + i] * a[j] + f[j][k] + f[k][j + i]);
		}
	}
	printf("%d\n", f[0][n - 1]);
	system("pause");
	return 0;
}