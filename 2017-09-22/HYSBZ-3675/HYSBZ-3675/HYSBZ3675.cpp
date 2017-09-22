#include<cstdio>
#define MAXN 100001
int n, k, Q[MAXN], head, tail, p = 0;
long long a[MAXN], sum[MAXN], f[MAXN][2], temp;
inline long long A(int i, int j){
	return sum[i] * sum[i] - f[i][p ^ 1] + f[j][p ^ 1] - sum[j] * sum[j];
}
inline long long B(int i, int j){
	return sum[i] - sum[j];
}
int main() {
	scanf("%d%d", &n, &k);
	for(int i = 1;i <= n;i++){
		scanf("%lld", &a[i]);
		sum[i] = a[i] + sum[i - 1];
	}
	for(int i = 0;i < k;i++){
		Q[head = tail = 0] = 0;p ^= 1;
		for(int j = 1;j <= n;j++){
			while(head < tail && A(Q[head], Q[head + 1]) > B(Q[head], Q[head + 1]) * sum[j])head++;
			temp = f[j][p ^ 1];
			f[j][p ^ 1] = f[j][p] = f[Q[head]][p ^ 1] + sum[Q[head]] * (sum[j] - sum[Q[head]]);
			while(head < tail && A(Q[tail - 1], Q[tail]) * B(Q[tail], j) <= A(Q[tail], j) * B(Q[tail - 1], Q[tail]))tail--;
			Q[++tail] = j;
			f[j][p ^ 1] = temp;
		}
	}
	printf("%lld\n", f[n][p]);
	return 0;
}
