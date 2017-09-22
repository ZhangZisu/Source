#include<cstdio>
#include<cstdlib>
#define MAXN 1000010
int n, head, tail;
long long f[MAXN], s[MAXN], t[MAXN], l[MAXN], p[MAXN], c[MAXN], Q[MAXN];
inline long long A(int a, int b) {
	return f[a] + t[a] - f[b] - t[b];
}
inline long long B(int a, int b) {
	return s[a] - s[b];
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld%lld", &l[i], &p[i], &c[i]);
		s[i] = s[i - 1] + p[i];
		t[i] = t[i - 1] + l[i] * p[i];
	}
	Q[head = tail = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail && A(Q[head + 1], Q[head]) < B(Q[head + 1], Q[head])*l[i])head++;
		f[i] = f[Q[head]] + (s[i] - s[Q[head]]) * l[i] - t[i] + t[Q[head]] + c[i];
		while (head < tail && A(i, Q[tail]) * B(Q[tail], Q[tail - 1]) < A(Q[tail], Q[tail - 1]) * B(i, Q[tail]))tail--;
		Q[++tail] = i;
	}
	printf("%lld\n", f[n]);
	system("pause");
	return 0;
}