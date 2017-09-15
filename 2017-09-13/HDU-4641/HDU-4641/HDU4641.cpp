#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAX_SAM_SIZE
int son[MAX_SAM_SIZE][26], pre[MAX_SAM_SIZE], len[MAX_SAM_SIZE], size, last;
inline int sam(int old) {
	int cur = size++;
	memcpy(son[cur], son[old], sizeof(son[cur]));
	pre[cur] = pre[old]; len[cur] = len[old];
	return cur;
}
inline void init_sam() {
	memset(son[0], -1, sizeof(son[0]));
	pre[0] = -1; len[0] = 0; size = 1; last = 0;
}
inline void insert_sam(char c) {

}
int main() {

	return 0;
}