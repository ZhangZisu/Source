#include<cstdio>
#include<cstring>
#include<cstdlib>
#define MAXN 200
int f[MAXN][MAXN], p[MAXN][MAXN], n;
char s[MAXN];
void print(int l, int r) {
	if (l > r)return;
	if (l == r) {
		if (s[l] == 40 || s[l] == 41)printf("()");
		if (s[l] == 91 || s[l] == 93)printf("[]");
		return;
	}
	if (~p[l][r]) {
		print(l, p[l][r]);
		print(p[l][r] + 1, r);
		return;
	}
	putchar(s[l]);
	print(l + 1, r - 1);
	putchar(s[r]);
}
inline bool match(char l, char r) {
	if (l == 40 && r == 41)return true;
	if (l == 91 && r == 93)return true;
	return false;
}
int main() {
	scanf("%s", s); n = strlen(s);
	for (int i = 0; i < n; i++)f[i][i] = 1;
	for (int k = 1; k < n; k++) {
		for (int i = 0; i + k < n; i++) {
			f[i][i + k] = n;
			if (match(s[i], s[i + k])) {
				p[i][i + k] = -1;
				f[i][i + k] = f[i + 1][i + k - 1];
			}
			for (int j = i; j < i + k; j++)if (f[i][j] + f[j + 1][i + k] < f[i][i + k]) {
				p[i][i + k] = j;
				f[i][i + k] = f[i][j] + f[j + 1][i + k];
			}
		}
	}
	print(0, n - 1); putchar(10);
	system("pause");
	return 0;
}