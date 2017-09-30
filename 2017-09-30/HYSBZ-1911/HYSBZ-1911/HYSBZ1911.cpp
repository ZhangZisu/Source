#include<cstdio>
#include<cstdlib>
#include<cstring>
#undef __max
#define __max(a,b) (((a) > (b)) ? (a) : (b))
#define MAXN 1000010
int n, x[MAXN], Q[MAXN], H, T;
long long s[MAXN], f[MAXN], a, b, c;
inline long long _2(long long x) { return x * x; }
inline long long A(int x, int y) {
	return (_2(s[x]) - _2(s[y])) * a + f[x] - f[y];
}
inline long long B(int x, int y) {
	return s[x] - s[y];
}
int main() {
	scanf("%d%lld%lld%lld", &n, &a, &b, &c);
	for (int i = 1; i <= n; i++)scanf("%d", &x[i]), s[i] = s[i - 1] + x[i];
	Q[H = T = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (H < T && A(Q[H + 1], Q[H]) > B(Q[H + 1], Q[H]) * (s[i] * a * 2 + b))H++;
		f[i] = f[Q[H]] + a * _2(s[i] - s[Q[H]]) + b * (s[i] - s[Q[H]]) + c;
		while (H < T && A(Q[T], Q[T - 1]) * B(i, Q[T]) < A(i, Q[T]) * B(Q[T], Q[T - 1]))T--;
		Q[++T] = i;
	}
	printf("%lld\n", f[n]);
	system("pause");
	return 0;
}