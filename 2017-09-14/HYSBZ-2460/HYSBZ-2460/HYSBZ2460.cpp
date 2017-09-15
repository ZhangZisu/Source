#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 2000
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
struct data {
	long long num; int val;
	data(long long num = 0, int val = 0) :num(num), val(val) {}
	inline void read() { num = getInt64(); val = getInt(); }
	inline friend bool operator < (const data &a, const data &b) { return a.val > b.val; }
}a[MAXN];
int n;
long long x[65], ans;
int main() {
	n = getInt();
	for (int i = 0; i < n; i++)a[i].read();
	std::sort(a, a + n);
	for (int i = 0; i < n; i++) {
		long long &v = a[i].num;
		for (int j = 65; j >= 0; j--) {
			if ((v >> j) & 1) {
				if (x[j]) {
					v ^= x[j];
				}
				else {
					x[j] = v;
					break;
				}
			}
		}
		if (v)ans += a[i].val;
	}
	putInt64(ans); _putchar('\n'); flush();
	system("pause");
	return 0;
}