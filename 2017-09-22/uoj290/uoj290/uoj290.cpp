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
#include<cstring>
#include<algorithm>
#define MAXN 500010
#define MAXE 1000100
#define MOD 998244353
int head[MAXN], next[MAXE], to[MAXE], tot;
inline void addEdge(int u, int v) { next[tot] = head[u]; to[tot] = v; head[u] = tot++; }
int dfn[MAXN], fa[MAXN], deep[MAXN], _index;
inline void dfs(int x) {
	dfn[x] = ++_index;
	for (int i = head[x]; ~i; i = next[i]){
		if (dfn[to[i]])continue;
		fa[to[i]] = x;
		deep[to[i]] = deep[x] + 1;
		dfs(to[i]);
	}
}
int cnt[MAXN];
long long f[MAXN], g[MAXN];
inline void dp(int x, bool rt) {
	cnt[x] = -1; int count = 0; f[x] = 1;
	for (int i = head[x]; ~i; i = next[i]) {
		if (to[i] != fa[x] && cnt[to[i]] == 1) {
			dp(to[i], false);
			count++;
			f[x] = f[x] * f[to[i]] % MOD;
		}
	}
	if (!rt)f[x] = f[x] * g[count + 1] % MOD;
	else f[x] = f[x] * g[count] % MOD;
}
int t, n, m, x, y;
int id[MAXN];
inline int cmp(const int &a, const int &b) {
	return deep[a] < deep[b];
}
int main() {
	t = getInt();
	g[0] = g[1] = 1;
	for (int i = 2; i < MAXN; i++)g[i] = (g[i - 2] * (i - 1) + g[i - 1]) % MOD;
	while (t--) {
		n = getInt(); m = getInt();
		long long ans = 1;
		tot = _index = 0;
		for (int i = 0; i < n; i++) head[i] = -1, fa[i] = dfn[i] = deep[i] = cnt[i] = 0;
		for (int i = 0; i < m; i++) { x = getInt() - 1; y = getInt() - 1; addEdge(x, y); addEdge(y, x); }
		dfs(0);
		for (int i = 0; i < m; i++) {
			x = to[i << 1]; y = to[i << 1 | 1];
			if (dfn[x] < dfn[y])std::swap(x, y);
			while (x != y) {
				cnt[x]++;
				if (cnt[x] > 2)goto fail;
				x = fa[x];
			}
		}
		for (int i = 0; i < n; i++)id[i] = i;
		std::sort(id, id + n, cmp);
		for (int i = 0; i < n; i++) {
			if (~cnt[id[i]]) {
				dp(id[i], true);
				ans = ans * f[id[i]] % MOD;
			}
		}
		putInt64(ans); _putchar(10); continue;
	fail:_putchar(48); _putchar(10);
	}
	flush();
	system("pause");
	return 0;
}