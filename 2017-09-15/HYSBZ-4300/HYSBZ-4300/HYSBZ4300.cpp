#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define $ 65536
char _1[$], _2[$], *_3 = _1 + $, *_4 = _2;
inline char _getchar() { if (_3 == _1 + $)fread(_1, 1, $, stdin), _3 = _1; return *_3++; }
inline int getInt() {
	register int __ = 0; register char _ = _getchar(); while (_ < '0' || _ > '9')_ = _getchar();
	for (; _ >= '0' && _ <= '9'; _ = _getchar())__ = ((__ << 3) + (__ << 1)) + (_ ^ 48);
	return __;
}
inline void _putchar(char c) { if (_4 == _2 + $)fwrite(_2, 1, $, stdout), _4 = _2; *_4++ = c; }
int _5[65];
inline void putInt(int x) {
	if (x == 0) { _putchar('0'); return; }
	register int _6; for (_6 = 0; x; x /= 10)_5[++_6] = x % 10; while (_6)_putchar(_5[_6--] ^ 48);
}
inline void flush() { fwrite(_2, 1, _4 - _2, stdout); }
int n, a[100000], f[31], ans;
int main() {
	n = getInt(); for (int i = 0; i < n; i++)a[i] = getInt();
	for (int i = 0; i < n; i++) {
		int now = 0; for (int j = 0; j < 31; j++)if ((a[i] >> j) & 1)now = std::max(now, f[j]);
		now++; for (int j = 0; j < 31; j++)if ((a[i] >> j) & 1)f[j] = std::max(f[j], now);
	}
	for (int i = 0; i < 32; i++)ans = std::max(ans, f[i]);
	putInt(ans); _putchar(10); flush();
	system("pause");
	return 0;
}