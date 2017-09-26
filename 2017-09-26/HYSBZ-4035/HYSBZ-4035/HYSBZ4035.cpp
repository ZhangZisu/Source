#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 100010
int t, n, sg[MAXN], stk[MAXN], pool[MAXN], pos[MAXN], top = 0, m, x, cnt = 0;
int main() {
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i = n / (n / i) + 1)stk[++top] = i;
	pos[0] = n + 1;
	for (int i = top; i > 0; i--) {
		int max = 0, t = 0;
		for (int j = cnt; j > 0; j--) {
			int x = pos[j - 1] / stk[i];
			if (!(pos[j - 1] % stk[i]))x--;
			int y = pos[j] / stk[i];
			if (!(pos[j] % stk[i]))y--;
			if (x != y) {
				pool[t ^ sg[j]] = i;
				if ((t ^ sg[j]) > max)max = t ^ sg[j];
				if ((x & 1) ^ (y & 1))t ^= sg[j];
			}
		}
		max++;
		for (int j = 1; j <= max; j++) {
			if (pool[j] != i) {
				if (sg[cnt] == j)pos[cnt] = stk[i];
				else pos[++cnt] = stk[i], sg[cnt] = j;
				break;
			}
		}
	}
	while (t--) {
		scanf("%d", &m); int rt = 0;
		while (m--) {
			scanf("%d", &x);
			int l = 1, r = cnt;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (x >= pos[mid])r = mid; else l = mid + 1;
			}
			rt ^= sg[l];
		}
		if (rt) printf("Yes\n"); else printf("No\n");
	}
	system("pause");
	return 0;
}