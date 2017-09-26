#include<cstdio>
#include<cstdlib>
#include<complex>
using std::complex;
#include<vector>
using std::vector;
const double PI = acos(-1.0);
void FFT(vector<complex<double>> &a, int n, int rev) {
	if (n == 1)return;
	vector<complex<double>> w0, w1;
	for (int i = 0; i < n; i += 2)w0.push_back(a[i]), w1.push_back(a[i + 1]);
	FFT(w0, n >> 1, rev); FFT(w1, n >> 1, rev);
	complex<double> wn(cos(2 * PI / n), sin(rev * 2 * PI / n)), w(1, 0);
	for (int i = 0; i < (n >> 1); i++, w *= wn)a[i] = w0[i] + w * w1[i], a[i + (n >> 1)] = w0[i] - w * w1[i];
}
int n, m, x;
vector<complex<double>> a, b;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) {
		scanf("%d", &x);
		a.push_back(complex<double>(x));
	}
	for (int i = 0; i <= m; i++) {
		scanf("%d", &x);
		b.push_back(complex<double>(x));
	}
	m += n; n = 1; while (n <= m)n <<= 1;
	while (a.size() <= n)a.push_back(complex<double>());
	while (b.size() <= n)b.push_back(complex<double>());
	FFT(a, n, 1); FFT(b, n, 1);
	for (int i = 0; i <= n; i++)a[i] *= b[i];
	FFT(a, n, -1);
	for (int i = 0; i <= m; i++)printf("%d ", (int)(a[i].real() / n + 0.5)); putchar(10);
	system("pause");
	return 0;
}