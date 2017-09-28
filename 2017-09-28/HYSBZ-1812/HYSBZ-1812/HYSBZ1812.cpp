#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXN 200
#undef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
int L[MAXN], R[MAXN], n, k, x, p, w[MAXN], D[MAXN], d[MAXN], f[MAXN][MAXN][MAXN];
void calc(int x) { for (int i = L[x]; ~i; i = R[i])d[i] = d[x] + D[i], calc(i); }
int DP(int x, int y, int l) {
	if (!~x || !~y)return 0;
	if (~f[x][y][l])return f[x][y][l];
	f[x][y][l] = 0x3F3F3F3F;
	for (int i = 0; i < y; i++) {
		f[x][y][l] = __min(f[x][y][l], DP(L[x], i, l) + DP(R[x], y - i, l) + w[x] * (d[x] - d[l]));
		f[x][y][l] = __min(f[x][y][l], DP(L[x], i, x) + DP(R[x], y - i - 1, l));
	}
	f[x][y][l] = __min(f[x][y][l], DP(L[x], y, l) + DP(R[x], 0, l) + w[x] * (d[x] - d[l]));
	return f[x][y][l];
}
void Print(int x = 0, int deep = 0) {
	for (int i = 0; i < deep; i++)printf("  "); printf("%d\n", x);
	for (int i = L[x]; ~i; i = R[i])Print(i, deep + 1);
}
int main() {
	scanf("%d%d", &n, &k);
	memset(L, -1, sizeof(L)); memset(R, -1, sizeof(R)); memset(f, -1, sizeof(f));
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &w[i], &x, &D[i]);
		if (~L[x]) {
			p = L[x];
			while (~R[p])p = R[p];
			R[p] = i;
		}
		else L[x] = i;
	}
	calc(0); //Print();
	printf("%d\n", DP(0, k, 0));
	system("pause");
	return 0;
}