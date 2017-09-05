#include<cstdio>
#include<cstring>
#include<algorithm>
#pragma comment(linker,"/STACK:102400000,102400000")
int n, m;
long long k[100010];
int len;
char buf[100010];
struct splay {
	splay *left, *right, *father;
	int val, size;
	long long hash;
	splay(int val = 0,
		int size = 1,
		long long hash = 0,
		splay *left = NULL,
		splay *right = NULL,
		splay *father = NULL) :
		val(val),
		size(size),
		hash(hash),
		left(left),
		right(right),
		father(father) {}
}*root;
inline void print(splay *x) {
	if (x == NULL)return;
	print(x->left);
	if (x->val)printf("%c", x->val + 'a' - 1);
	print(x->right);
}
inline void pushUp(splay *x) {
	x->size = 1;
	if (x->left)x->size += x->left->size;
	if (x->right)x->size += x->right->size;
	x->hash = 0;
	int rs = 0;
	if (x->right) {
		rs = x->right->size;
		x->hash += x->right->hash;
	}
	x->hash += x->val * k[rs];
	if (x->left)x->hash += x->left->hash * k[rs + 1];
}
inline void rightRotate(splay *x) {
	splay *f = x->father;
	f->left = x->right;
	if (x->right)x->right->father = f;
	x->father = f->father;
	if (f->father) {
		if (f == f->father->left)f->father->left = x;
		else f->father->right = x;
	}
	f->father = x;
	x->right = f;
	pushUp(f);
	pushUp(x);
	if (x->father == NULL)root = x;
}
inline void leftRotate(splay *x) {
	splay *f = x->father;
	f->right = x->left;
	if (x->left)x->left->father = f;
	x->father = f->father;
	if (f->father) {
		if (f == f->father->left)f->father->left = x;
		else f->father->right = x;
	}
	f->father = x;
	pushUp(f);
	pushUp(x);
	x->left = f;
	if (x->father == NULL)root = x;
}
inline void Splay(splay *x, splay *goal) {
	while (x->father != goal) {
		splay *f = x->father;
		if (f->father == goal) {
			if (x == f->left) rightRotate(x);
			if (x == f->right)leftRotate(x);
		}
		else {
			if (f == f->father->left) {
				if (x == f->left) {
					rightRotate(f);
					rightRotate(x);
				}
				else {
					leftRotate(x);
					rightRotate(x);
				}
			}
			else {
				if (x == f->left) {
					rightRotate(x);
					leftRotate(x);
				}
				else {
					leftRotate(f);
					leftRotate(x);
				}
			}
		}
		pushUp(x);
	}
	if (goal == NULL)root = x;
}
inline void build(splay* &x, int l, int r, splay *f) {
	if (l > r)return;
	int mid = (l + r) >> 1;
	x = new splay(buf[mid] - 'a' + 1, 1, buf[mid] - 'a' + 1, NULL, NULL, f);
	build(x->left, l, mid - 1, x);
	build(x->right, mid + 1, r, x);
	pushUp(x);
}
inline splay* find(splay *x, int k) {
	int c = 0;
	if (x->left != NULL)c = x->left->size;
	if (c + 1 == k)return x;
	if (k <= c)return find(x->left, k);
	return find(x->right, k - c - 1);
}
inline splay* min(splay *r) {
	while (r->left) {
		r = r->left;
	}
	return r;
}
inline void del(splay *x) {
	if (x == NULL)return;
	del(x->left); del(x->right);
	delete x;
}
inline bool equal(int x, int y, int len) {
	splay *X = find(root, x);
	Splay(X, NULL);
	splay *XR = find(root, x + len + 1);
	Splay(XR, root);
	int hash1 = root->right->left->hash;
	splay *Y = find(root, y);
	Splay(Y, NULL);
	splay *YR = find(root, y + len + 1);
	Splay(YR, root);
	int hash2 = root->right->left->hash;
	return hash1 == hash2;
}
inline int query(int x, int y) {
	int l = 0, r = root->size - std::max(x, y) - 1;
	while (l + 1 < r) {
		int mid = (l + r) >> 1;
		if (equal(x, y, mid)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	return equal(x, y, r) ? r : l;
}
char op[3];
int x, y;
int main() {
	scanf("%s", buf);
	len = strlen(buf);
	k[0] = 1;
	for (int i = 1; i <= 100010; i++) {
		k[i] = k[i - 1] * 31;
	}
	root = new splay(0, 2, 0, NULL, new splay(0, 1, 0), NULL);
	root->right->father = root;
	build(root->right->left, 0, len - 1, root->right);
	pushUp(root->right);
	pushUp(root);
	scanf("%d", &m);
	while (m--) {
		scanf("%s", op);
		switch (op[0]) {
		case 'Q': {
			scanf("%d%d", &x, &y);
			printf("%d\n", query(x, y));
			break;
		}
		case 'R': {
			scanf("%d%s", &x, op);
			splay *s = find(root, x + 1);
			Splay(s, NULL);
			root->val = op[0] - 'a' + 1;
			pushUp(root);
			break;
		}
		case'I': {
			scanf("%d%s", &x, op);
			splay *a = find(root, x + 1);
			Splay(a, NULL);
			splay *b = find(root, x + 2);
			Splay(b, root);
			root->right->left = new splay(op[0] - 'a' + 1, 1, op[0] - 'a' + 1, NULL, NULL, root->right);
			pushUp(root->right);
			pushUp(root);
			break;
		}
		}
	}
	return 0;
}
