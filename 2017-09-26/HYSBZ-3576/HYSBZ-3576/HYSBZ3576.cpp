#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
int t, f, n, x, sg[200000], pool[200000], ans;
int getSG(int x) {
	if (x < f)return 0;
	if (~sg[x])return sg[x];
	sg[x] = 0;
	for (int i = 2; i <= x; i = x / (x / i) + 1) {
		getSG(x / i), getSG(x / i + 1);
		if (i < x)
			getSG(x / (i + 1)), getSG(x / (i + 1) + 1);
	}
	for (int i = 2; i <= x; i = x / (x / i) + 1) {
		pool[((i - x % i) & 1 ? getSG(x / i) : 0) ^ ((x % i) & 1 ? getSG(x / i + 1) : 0)] = x;
		if (i < x)
			pool[((i + 1 - x % (i + 1)) & 1 ? getSG(x / (i + 1)) : 0) ^ ((x % (i + 1)) & 1 ? getSG(x / (i + 1) + 1) : 0)] = x;
	}
	for (sg[x] = 0; pool[sg[x]] == x; sg[x]++);
	return sg[x];
}
int main() {
	memset(sg, -1, sizeof(sg));
	scanf("%d%d", &t, &f);
	while (t--) {
		scanf("%d", &n); ans = 0;
		for (int i = 1; i <= n; i++)scanf("%d", &x), ans ^= getSG(x);
		printf("%d", ans != 0); if (t)putchar(' ');
	}
	system("pause");
	return 0;
}