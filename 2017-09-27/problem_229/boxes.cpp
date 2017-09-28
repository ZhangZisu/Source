#include "boxes.h"
#define __min(a,b) ((a)<(b)?(a):(b))
long long f[20000010], g[20000010], ans;
long long delivery(int N,int K,int L,int positions[]){
	ans = (long long)N * L;
	for(int i = 0, j = N - 1;i < N;i++, j--){
		if(i >= K){
			f[i] = f[i - K] + (positions[i] << 1);
			g[j] = f[j + K] + ((L - positions[j]) << 1);
		}else{
			f[i] = positions[i] << 1;
			g[j] = (L - positions[j]) << 1;
		}
	}
	ans = __min(ans, g[K] + L);
	for(int i = 0;i < N;i++){
		ans = __min(ans, f[i - 1] + g[i + K] + L);
		ans = __min(ans, f[i] + g[i + 1]);
	}
	ans = __min(ans, f[N - 1]);ans = __min(ans, g[0]);
	return ans;
}
