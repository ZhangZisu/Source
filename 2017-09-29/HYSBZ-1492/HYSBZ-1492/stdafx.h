/*
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 100005
int n;
double A[MAXN], B[MAXN], R[MAXN], X[MAXN], Y[MAXN], f[MAXN];
inline void calc(int x) {
	X[x] = f[x] / (A[x] * R[x] + B[x]) * R[x];
	Y[x] = f[x] / (A[x] * R[x] + B[x]);
}
int main() {
	scanf("%d%lf", &n, &f[1]);
	for (int i = 1; i <= n; i++)scanf("%lf%lf%lf", &A[i], &B[i], &R[i]);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			f[i] = std::max(f[i], X[j] * A[i] + Y[j] * B[i]);
		}
		calc(i);
	}
	printf("%.3lf\n", f[n]);
	system("pause");
	return 0;
}
*/