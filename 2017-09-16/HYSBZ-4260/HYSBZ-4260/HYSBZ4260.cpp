#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MAXN 400010
int son[MAXN << 5][2];
int n, m, a[MAXN], tot, L[MAXN], R[MAXN];
inline void insert(int x) {
	int now = 1;
	for (int i = 30; i >= 0; i--) {
		bool w;
		if ((x >> i) & 1) w = 1; else w = 0;
		if (!son[now][w]) son[now][w] = ++tot;
		now = son[now][w];
	}
}
inline int cal(int x) {
	int ans = 0, now = 1;
	for (int i = 30; i >= 0; i--) {
		bool w;
		if ((x >> i) & 1) w = 1; else w = 0;
		if (son[now][!w]) {
			ans += 1 << i;
			now = son[now][!w];
		}
		else {
			now = son[now][w];
		}
	}
	return ans;
}
inline void init() {
	memset(son, 0, sizeof(son)); tot = 1; insert(0);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int now = 0; init();
	for (int i = 1; i <= n; i++) {
		now ^= a[i];
		insert(now);
		L[i] = cal(now);
	}
	for (int i = 1; i <= n; i++) L[i] = std::max(L[i - 1], L[i]);
	memset(son, 0, sizeof(son));
	now = 0; init();
	for (int i = n; i >= 1; i--) {
		now ^= a[i];
		insert(now);
		R[i] = cal(now);
	}
	for (int i = n; i >= 1; i--) R[i] = std::max(R[i + 1], R[i]);
	int ans = 0;
	for (int i = 1; i < n; i++) ans = std::max(ans, L[i] + R[i + 1]);
	printf("%d\n", ans);
	system("pause");
	return 0;
}