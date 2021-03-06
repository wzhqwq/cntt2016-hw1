#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class IncrementAndDoubling {
public :
	// 贪心，倍增
	// 答案等于集体倍增的次数 + 所有数二进制表示下1的个数
	int getMin(vector<int> num) {
		int ans = 0, mx = 0;
		rep (i, 0, num.size()-1) {
			int d = 0;
			while (num[i]) {
				d++;
				ans += num[i] & 1;
				num[i] >>= 1;
			}
			upmax(mx, d - 1);
		}
		return ans + mx;
	}
};
