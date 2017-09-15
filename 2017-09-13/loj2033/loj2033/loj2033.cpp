#include<cstdio>
#define __ 65536
char _1[__], _2[__], *_3 = _1 + __, *_4 = _2;
inline char _getchar() { if (_3 == _1 + __)fread(_1, 1, __, stdin), _3 = _1; return *_3++; }
inline int getInt() {
	register int x = 0;
	register char c = _getchar();
	while (c < '0' || c > '9')c = _getchar();
	for (; c >= '0' && c <= '9'; c = _getchar())x = ((x << 3) + (x << 1)) + (c ^ 48);
	return x;
}
inline void _putchar(char c) { if (_4 == _2 + __)fwrite(_2, 1, __, stdout), _4 = _2; *_4++ = c; }
int _5[65];
inline void putInt(long long x) {
	if (x == 0) { _putchar('0'); return; }
	register int _6;
	for (_6 = 0; x; x /= 10)_5[++_6] = x % 10;
	while (_6)_putchar(_5[_6--] ^ 48);
}
inline void flush() { fwrite(_2, 1, _4 - _2, stdout); }
#include<map>
using std::map;
#define MAX_SAM_SIZE 300000
map<int, int> son[MAX_SAM_SIZE];
int pre[MAX_SAM_SIZE], len[MAX_SAM_SIZE], size, last;
inline void init_sam() {
	pre[0] = -1; len[0] = 0; son[0].clear();
	size = 1; last = 0;
}
long long ans = 0;
inline void insert_sam(int c) {
	int cur = size++, p = last;
	son[cur].clear(); len[cur] = len[last] + 1; pre[cur] = 0;
	for (; ~p && !son[p].count(c); p = pre[p])son[p][c] = cur;
	if (~p) {
		int q = son[p][c];
		if (len[p] + 1 == len[q]) {
			pre[cur] = q;
		}
		else {
			int clone = size++;
			son[clone] = son[q]; pre[clone] = pre[q]; len[clone] = len[p] + 1;
			for (; ~p && son[p].count(c) && son[p][c] == q; p = pre[p])son[p][c] = clone;
			pre[q] = pre[cur] = clone;
		}
	}
	ans += len[cur];
	if (pre[cur])ans -= len[pre[cur]];
	last = cur;
}
int n, x;
int main() {
	n = getInt(); init_sam();
	for (int i = 0; i < n; i++) {
		x = getInt();
		insert_sam(x);
		putInt(ans); _putchar(10);
	}
	flush();
	return 0;
}