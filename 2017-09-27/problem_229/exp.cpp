#include "boxes.h"
#include <algorithm>
using std::min;
long long f[20000005], g[20000005], ans;
long long delivery(int N, int K, int L, int P[])
{
	ans = (long long)N * L;
	for (int i = 0; i < N; i++)
		if (i >= K)
			f[i] = f[i - K] + (P[i] << 1);
		else
			f[i] = P[i] << 1;
	for (int i = N - 1; i >= 0; i--)
		if (N - i > K)
			g[i] = g[i + K] + ((L - P[i]) << 1);
		else
			g[i] = (L - P[i]) << 1;
	for (int i = 0; i < N; i++)
		ans = min(ans, min(f[i - 1] + g[i + K] + L, f[i] + g[i + 1]));
	ans = min(ans, min(f[N - 1], g[0]));
	return ans;
}