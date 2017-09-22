#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
struct mtx {
	double mt[2][2];
	mtx(double a = 0, double b = 0, double c = 0, double d = 0) {
		mt[0][0] = a; mt[0][1] = b; mt[1][0] = c; mt[1][1] = d;
	}
	mtx(const mtx &other) { memcpy(mt, other.mt, sizeof(mt)); }
	inline friend mtx operator * (const mtx &a, const mtx &b) {
		return mtx(a.mt[0][0] * b.mt[0][0] + a.mt[0][1] * b.mt[1][0],
			a.mt[0][0] * b.mt[0][1] + a.mt[0][1] * b.mt[1][1],
			a.mt[1][0] * b.mt[0][0] + a.mt[1][1] * b.mt[1][0],
			a.mt[1][0] * b.mt[0][1] + a.mt[1][1] * b.mt[1][1]);
	}
	inline void print() {
		printf("mtx:\n%3.3f %3.3f\n%3.3f %3.3f\n", mt[0][0], mt[0][1], mt[1][0], mt[1][1]);
	}
};
inline mtx pow(mtx a, int p) {
	mtx ret(1, 0, 0, 1);
	while (p) {
		if (p & 1)ret = ret * a;
		a = a * a;
		p >>= 1;
	}
	return ret;
}
int n, d[20];
double p, ans;
int main() {
	while (~scanf("%d%lf", &n, &p)) {
		mtx transfer(p, 1 - p, 1, 0); ans = 1;
		for (int i = 0; i < n; i++)scanf("%d", &d[i]);
		std::sort(d, d + n);
		for (int i = 0; i < n; i++) {
			if (i != 0 && d[i] == d[i - 1]) {
				continue;
			}
			mtx res = pow(transfer, i == 0 ? d[i] - 1 : d[i] - d[i - 1] - 1);
			ans *= (1 - res.mt[0][0]);
		}
		printf("%.7f\n", ans);
	}
	system("pause");
	return 0;
}