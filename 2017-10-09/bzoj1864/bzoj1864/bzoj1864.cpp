#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 500000
int L[MAXN], R[MAXN], pos = 0, cnt = 1;
char buf[600000];
int process() {
	int cur = cnt++, ch = buf[pos++];
	if (ch == '0')return cur;
	else if (ch == '1')L[cur] = process();
	else L[cur] = process(), R[cur] = process();
	return cur;
}
void Print(int x, int deep = 0) {
	if (!x)return;
	for (int i = 0; i < deep; i++)putchar(' ');
	printf("%d\n", x);
	Print(L[x], deep + 4);
	Print(R[x], deep + 4);
}
int f[MAXN][2], g[MAXN][2];
void DP(int x) {
	if (L[x])DP(L[x]);
	if (R[x])DP(R[x]);
	f[x][0] = std::max(f[L[x]][0] + f[R[x]][1], f[L[x]][1] + f[R[x]][0]);
	f[x][1] = f[L[x]][0] + f[R[x]][0] + 1;
	g[x][0] = std::min(g[L[x]][0] + g[R[x]][1], g[L[x]][1] + g[R[x]][0]);
	g[x][1] = g[L[x]][0] + g[R[x]][0] + 1;
}
int root;
int main() {
	scanf("%s", buf);
	root = process(); //Print(root);
	DP(root); printf("%d %d\n", std::max(f[root][0], f[root][1]), std::min(g[root][0], g[root][1]));
	system("pause");
	return 0;
}