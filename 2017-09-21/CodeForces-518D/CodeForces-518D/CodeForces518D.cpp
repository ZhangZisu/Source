#include<cstdio>
#include<cstdlib>
int n, t;
double p, f[2050][2050];
int main() {
	scanf("%d%lf%d", &n, &p, &t);
	f[0][0] = 1;
	for (int i = 0; i <= t; i++) {
		for (int j = 0; j < n; j++) {
			f[i + 1][j] += f[i][j] * (1 - p);
			f[i + 1][j + 1] += f[i][j] * p;
		}
		f[i + 1][n] += f[i][n];
	}
	double sum = 0;
	for (int i = 0; i <= n; i++)sum += f[t][i] * i;
	printf("%lf\n", sum);
	return 0;
}