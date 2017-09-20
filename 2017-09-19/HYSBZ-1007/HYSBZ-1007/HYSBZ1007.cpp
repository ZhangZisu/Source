#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define MAXN 50010
struct line {
	int k, b;
}data[MAXN];
int n, id[MAXN], stk[MAXN], top = 0;
inline double calc(line a, line b) {
	return (double)(b.b - a.b) / (a.k - b.k);
}
inline int cmp(const int &a, const int &b) {
	if (data[a].k == data[b].k) {
		return data[a].b < data[b].b;
	}
	else {
		return data[a].k < data[b].k;
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &data[i].k, &data[i].b);
		id[i] = i;
	}
	std::sort(id, id + n, cmp);
	for (int i = 0; i < n; i++) {
		while (top) {
			if (data[id[i]].k == data[stk[top]].k)top--;
			else if (top > 1 && calc(data[id[i]], data[stk[top]]) <= calc(data[stk[top]], data[stk[top - 1]]))top--;
			else break;
		}
		stk[++top] = id[i];
	}
	std::sort(stk, stk + top + 1);
	for (int i = 1; i <= top; i++)printf("%d ", stk[i] + 1); putchar(10);
	system("pause");
	return 0;
}