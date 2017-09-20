#include<cstdio>
#include<cstdlib>
#define MAXN 2010
int n, m, a[MAXN], c[MAXN], _1, _2, f[MAXN][MAXN];
char buf[MAXN];
int main() {
	scanf("%d%d%s", &n, &m, buf);
	for (int i = 0; i < m; i++)a[i] = buf[i] - 'a';
	for (int i = 0; i < n; i++) {
		scanf("%s%d%d", buf, &_1, &_2);
		c[buf[0] - 'a'] = __min(_1, _2);
	}
	for (int i = m - 1; i >= 0; i--) {
		for (int j = i + 1; j < m; j++) {
			f[i][j] = __min(f[i + 1][j] + c[a[i]], f[i][j - 1] + c[a[j]]);
			if (a[i] == a[j])f[i][j] = __min(f[i][j], f[i + 1][j - 1]);
		}
	}
	printf("%d\n", f[0][m - 1]);
	system("pause");
	return 0;
}