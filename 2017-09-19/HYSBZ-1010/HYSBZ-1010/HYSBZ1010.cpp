#include<cstdio>
#include<cstdlib>
#define MAXN 50010
inline long long sqr(long long x) { return x * x; }
long long sum[MAXN], f[MAXN], l, Q[MAXN];
int n, head, tail;
inline long long A(int x, int y) {
	return f[x] + sqr(sum[x]) - f[y] - sqr(sum[y]);
}
inline long long B(int x, int y) {
	return sum[x] - sum[y];
}
inline long long C(int x) {
	return 2 * (sum[x] - l);
}
int main() {
	scanf("%d%lld", &n, &l); l++;
	for (int i = 1; i <= n; i++) { scanf("%lld", &sum[i]); sum[i] += sum[i - 1] + 1; }
	Q[head = tail = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail && (A(Q[head + 1], Q[head]) < B(Q[head + 1], Q[head]) * C(i)))head++;
		f[i] = f[Q[head]] + sqr(sum[i] - sum[Q[head]] - l);
		while (head < tail && (A(i, Q[tail]) * B(Q[tail], Q[tail - 1]) < A(Q[tail], Q[tail - 1]) * B(i, Q[tail])))tail--;
		Q[++tail] = i;
	}
	printf("%lld\n", f[n]);
	system("pause");
	return 0;
}