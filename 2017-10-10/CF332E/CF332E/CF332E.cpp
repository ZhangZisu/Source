#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
string s, p, a[2010], b[2010], ans, tmp;
int k, rest, cur, first = 1;
int main() {
	getline(cin, p); getline(cin, s); cin >> k;
	for (int i = 0; i < p.length(); i++)a[i % k] += p[i];
	for (int i = 1; i <= std::min((int)s.length(), k); i++) {
		for (int j = 0; j < i; j++)b[j].clear();
		for (int j = 0; j < s.length(); j++)b[j % i] += s[j];
		rest = i - 1; tmp.clear();
		for (int j = k - 1; j >= 0; j--)if (rest >= 0 && a[j] == b[rest]) {
			rest--; tmp = "1" + tmp;
		}
		else {
			tmp = "0" + tmp;
		}
		if (rest >= 0)continue;
		if (first)ans = tmp, first = 0;
		else ans = std::min(ans, tmp);
	}
	if (first)cout << "0" << endl;
	else cout << ans << endl;
	//system("pause");
	return 0;
}