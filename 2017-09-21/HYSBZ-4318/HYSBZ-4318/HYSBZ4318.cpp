#include<cstdio>
#include<cstdlib>
int n;
double ans, l1, l2, p;
int main() {
	scanf("%d", &n);
	while (n--) {
		scanf("%lf", &p);
		ans += (l2 * 3 + l1 * 3 + 1) * p;
		l2 = (l2 + l1 * 2 + 1) * p;
		l1 = (l1 + 1) * p;
	}
	printf("%.1lf\n", ans);
	system("pause");
	return 0;
}