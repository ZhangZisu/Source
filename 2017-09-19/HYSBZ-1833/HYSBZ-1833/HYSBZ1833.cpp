#include<cstdio>
#include<cstring>
#include<cstdlib>
long long f[15], ans[10], bak[10];
inline void calc(long long x) {
	memset(ans, 0, sizeof(ans));
	long long now, temp = 1; int i = 0;
	for (; temp * 10 < x; i++, temp *= 10) {
		for (int j = 0; j < 10; j++)ans[j] += f[i] * 9;
		for (int j = 1; j < 10; j++)ans[j] += temp;
	}
	now = temp;
	while (now < x) {
		while (now + temp <= x) {
			long long dv = now / temp;
			while (dv)ans[dv % 10] += temp, dv /= 10;
			for (int j = 0; j < 10; j++)ans[j] += f[i];
			now += temp;
		}
		i--; temp /= 10;
	}
}
int main() {
	f[1] = 1;
	for (long long i = 2, temp = 10; i <= 12; i++, temp *= 10)f[i] = f[i - 1] * 10 + temp;
	long long a, b; scanf("%lld%lld", &a, &b);
	calc(b + 1); memcpy(bak, ans, sizeof(bak)); calc(a);
	for (int i = 0; i < 9; i++)printf("%lld ", bak[i] - ans[i]); printf("%lld\n", bak[9] - ans[9]);
	system("pause");
	return 0;
}