#include<cstdio>
#include<cstdlib>
#include<cstring>
int t, n, m, cnt;
long long x, ji[65], qi[65];
inline void insert(long long x) {
	for (int i = 63; i >= 0; i--) {
		if ((x >> i) & 1) {
			if (ji[i]) {
				x ^= ji[i];
			}
			else {
				ji[i] = x;
				break;
			}
		}
	}
}
inline void rebuild() {
	for (int i = 63; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			if ((ji[i] >> j) & 1) {
				ji[i] ^= ji[j];
			}
		}
	}
	for (int i = 0; i <= 63; i++)if (ji[i])qi[cnt++] = ji[i];
}
inline long long query(long long k) {
	if (cnt != n)k--;
	if (k >> cnt)return -1;
	long long ret = 0;
	for (int i = 63; i >= 0; i--) {
		if ((k >> i) & 1)ret ^= qi[i];
	}
	return ret;
}
int main() {
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		scanf("%d", &n); memset(ji, 0, sizeof(ji)); memset(qi, 0, sizeof(qi)); cnt = 0;
		for (int i = 0; i < n; i++) { scanf("%lld", &x); insert(x); }
		rebuild();
		scanf("%d", &m); printf("Case #%d:\n", i);
		for (int i = 0; i < m; i++) { scanf("%lld", &x); printf("%lld\n", query(x)); }
	}
	system("pause");
	return 0;
}