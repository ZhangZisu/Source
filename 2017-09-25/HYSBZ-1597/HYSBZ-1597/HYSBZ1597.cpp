#include<cstdio>  
#include<algorithm>  
struct data {
	long long a, b;
	inline friend bool operator < (const data &x, const data &y) {
		if (x.a == y.a)return x.b > y.b;
		else return x.a < y.a;
	}
}a[50001], b[50001];
int Q[50001], n, m, head, tail;
long long f[50001];
inline long long A(int k, int j) { return f[j] - f[k]; }
inline long long B(int k, int j) { return b[k + 1].b - b[j + 1].b; }
int main() {
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)scanf("%lld%lld", &a[i].a, &a[i].b);
	std::sort(a + 1, a + 1 + m);
	b[n = 1] = a[1];
	for (int i = 2; i <= m; i++) {
		while (n > 0 && a[i].b >= b[n].b)n--;
		b[++n] = a[i];
	}
	Q[head = tail = 0] = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail && A(Q[head], Q[head + 1]) < b[i].a * B(Q[head], Q[head + 1]))head++;
		f[i] = f[Q[head]] + b[i].a * b[Q[head] + 1].b;
		while (head < tail && A(Q[tail - 1], Q[tail]) * B(Q[tail], i) > A(Q[tail], i) * B(Q[tail - 1], Q[tail]))tail--;
		Q[++tail] = i;
	}
	printf("%lld\n", f[n]);
	system("pause");
	return 0;
}