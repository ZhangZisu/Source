#include<cstdio>
#define $ 65536
char _1[$], _2[$], *_3 = _1 + $, *_4 = _2;
inline char _getchar() { if (_3 == _1 + $)fread(_1, 1, $, stdin), _3 = _1; return *_3++; }
inline int getInt() {
	register int __ = 0; register char _ = _getchar(); while (_ < '0' || _ > '9')_ = _getchar();
	for (; _ >= '0' && _ <= '9'; _ = _getchar())__ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
	return __;
}
inline long long getInt64() {
	register long long __ = 0; register char _ = _getchar(); while (_ < '0' || _ > '9')_ = _getchar();
	for (; _ >= '0' && _ <= '9'; _ = _getchar())__ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
	return __;
}
inline void _putchar(char c) { if (_4 == _2 + $)fwrite(_2, 1, $, stdout), _4 = _2; *_4++ = c; }
int _5[65];
inline void putInt(int x) {
	if (x == 0) { _putchar('0'); return; }
	register int _6; for (_6 = 0; x; x /= 10)_5[++_6] = x % 10; while (_6)_putchar(_5[_6--] ^ 48);
}
inline void putInt64(long long x) {
	if (x == 0) { _putchar('0'); return; }
	register int _6; for (_6 = 0; x; x /= 10)_5[++_6] = x % 10; while (_6)_putchar(_5[_6--] ^ 48);
}
inline void flush() { fwrite(_2, 1, _4 - _2, stdout); }
#include<cstdlib>
#include<algorithm>
#define MAXN 100010
int n, m, head, tail, Q[MAXN];
long long f[MAXN][2], sum[MAXN], y[MAXN][2];
int now = 0;
inline long long A(int i, int j) {
	return sum[i] - sum[j];
}
inline long long B(int i, int j) {
	return y[i][now ^ 1] - y[j][now ^ 1];
}
int main() {
	n = getInt(); m = getInt();
	for (int i = 1; i <= n; i++) {
		sum[i] += getInt64() + sum[i - 1];
	}
	for (int i = 1; i <= n; i++)y[i][0] = sum[i] * sum[i];
	for (int j = 1; j <= m; j++) {
		now ^= 1;
		Q[head = tail = 0] = 0;
		for (int i = 1; i <= n; i++) {
			while (head < tail && sum[i] * A(Q[head + 1], Q[head]) >= B(Q[head + 1], Q[head])) head++;
			f[i][now] = f[Q[head]][now ^ 1] + sum[i] * sum[Q[head]] - sum[Q[head]] * sum[Q[head]];
			y[i][now] = sum[i] * sum[i] - f[i][now];
			while (head < tail && B(Q[tail], Q[tail - 1])*A(i, Q[tail]) >= B(i, Q[tail])*A(Q[tail], Q[tail - 1])) tail--;
			Q[++tail] = i;
		}
	}
	putInt64(f[n][now]); _putchar(10);
	flush();
	system("pause");
	return 0;
}