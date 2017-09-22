#include<cstdio>
#include<cstdlib>
#include<cmath>
int f[20][10], sum[10], stk[20], top, a, b;
inline int calc(int x) {
	top = 0;
	int ret = 0;
	while (x) {
		ret += sum[top];
		stk[++top] = x % 10;
		x /= 10;
	}
	for (int i = 1; i < stk[top]; i++)ret += f[top][i];
	for (int i = top - 1; i > 0; i--) {
		for (int j = 0; j < stk[i]; j++)if (abs(j - stk[i + 1]) >= 2)ret += f[i][j];
		if (abs(stk[i + 1] - stk[i]) < 2)break;
	}
	return ret;
}
int main() {
	for (int i = 0; i < 10; i++)f[1][i] = 1; sum[1] = 9;
	for (int i = 2; i <= 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++)if (abs(k - j) >= 2)f[i][j] += f[i - 1][k];
			if (j != 0)sum[i] += f[i][j];
		}
	}
	scanf("%d%d", &a, &b);
	printf("%d\n", calc(b + 1) - calc(a));
	system("pause");
	return 0;
}