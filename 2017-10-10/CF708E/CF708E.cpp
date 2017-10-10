#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define MOD 1000000007
#define MAXK 100010
inline long long fpow(long long a, long long b){
	long long ret = 1;
	while(b){
		if(b & 1)ret = (ret * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return ret;
}
int n, m, k, a, b;
long long fact[MAXK], inv[MAXK], L[MAXK], R[MAXK], s1, s2, f[1600][1600];
inline long long P(int l){
	return fact[k] * inv[k - l] % MOD * inv[l] % MOD * L[l] % MOD * R[k - l] % MOD;
}
int main(){
	scanf("%d%d%d%d%d", &n, &m, &a, &b, &k);
	fact[0] = 1;
	for(int i = 1;i <= k;i++)fact[i] = fact[i - 1] * i % MOD;
	inv[k] = fpow(fact[k], MOD - 2);
	for(int i = k;i >= 1;i--)inv[i - 1] = inv[i] * i % MOD;
	L[0] = 1;L[1] = a * fpow(b, MOD - 2) % MOD;
	R[0] = 1;R[1] = (b - a) * fpow(b, MOD - 2) % MOD;
	for(int i = 2;i <= k;i++){
		L[i] = L[i - 1] * L[1] % MOD;
		R[i] = R[i - 1] * R[1] % MOD;
	}
	f[0][m] = 1;
	for(int i = 1;i <= n;i++){
		s1 = s2 = 0;
		for(int j = 0;j <= m;j++){
			f[i][j] = (f[i - 1][m] * s1 - s2 - s1 * f[i - 1][m - j]) % MOD * P(m - j) % MOD;
			s1 = (s1 + P(j)) % MOD;s2 = (s2 + f[i - 1][j] * P(j)) % MOD;
		}
		for(int j = 1;j <= m;j++)f[i][j] = (f[i][j] + f[i][j - 1]) % MOD;
	}
	printf("%I64d\n", (f[n][m] + MOD) % MOD);
	return 0;
}
