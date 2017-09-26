#include<cstdio>
#include<cstdlib>
#include<cstring>
int t, n, x, sg[30], pool[30], ans, tot;
int getSG(int x) {
	if (~sg[x])return sg[x];
	for (int i = 1; i < x; i++)
		for (int j = i; j < x; j++)
			pool[getSG(i) ^ getSG(j)] = x;
	for (sg[x] = 0; pool[sg[x]] == x; sg[x]++);
	return sg[x];
}
int main() {
	memset(sg, -1, sizeof(sg));
	for (int i = 2; i < 30; i++)getSG(i);
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n); ans = tot = 0;
		for (int i = 1; i <= n; i++)scanf("%d", &x), ans ^= x & 1 ? sg[n - i + 1] : 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = j; k < n; k++)
					if (!(ans ^ sg[n - i] ^ sg[n - j] ^ sg[n - k])) {
						if (!(tot++))printf("%d %d %d\n", i, j, k);
					}
		if (!tot)printf("-1 -1 -1\n");
		printf("%d\n", tot);
	}
	system("pause");
	return 0;
}