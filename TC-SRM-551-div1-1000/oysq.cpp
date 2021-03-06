#line 2 "SweetFruits.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 40;
const int MOD = 1e9 + 7;

int n, m, hf;
int g[N + 9][N + 9];
std::vector<int> w1, w2;
std::vector<pii> f1, f2;
int com[N + 9][N + 9];
int f[N + 9], c[N + 9];

class SweetFruits {  
public:
	// fast power
	int fpm(int a, int b) {
		int ret = 1;
		while(b) {
			if(b & 1) ret = (ll)ret * a % MOD;
			a = (ll)a * a % MOD, b >>= 1;
		}
		return ret;
	}
	// calc det(g)
	int det(int n) {
		int ret = 1;
		for(int i = 0; i < n; ++i) {
			int b = i;
			while(b < n && !g[b][i]) ++b;
			if(b == n) return 0;
			if(b != i) {
				for(int j = i; j < n; ++j)
					std::swap(g[i][j], g[b][j]);
				ret = (MOD - ret) % MOD;
			}
			ret = (ll)ret * g[i][i] % MOD;
			for(int j = i + 1; j < n; ++j)
				if(g[j][i]) {
					int t = (ll)g[j][i] * fpm(g[i][i], MOD - 2) % MOD;
					for(int k = i; k < n; ++k)
						(g[j][k] += MOD - (ll)g[i][k] * t % MOD) %= MOD;
				}
		}
		return ret;
	}
	// 2 ^ SZ(w) enumerate all possibilities of truly sweet
	void get(std::vector<pii> &f, std::vector<int> &w) {
		f.clear();
		std::sort(w.begin(), w.end(), std::greater<int>());
		int cnt = 0;
		while(cnt < SZ(w) && w[cnt] != -1) ++cnt;
		for(int i = 0; i < (1 << cnt); ++i) {
			int sum = 0;
			for(int j = 0; j < cnt; ++j)
				if(i >> j & 1)
					sum += w[j];
			f.pb(mp(sum, __builtin_popcount(i)));
		}
		std::sort(f.begin(), f.end());
	}
	int countTrees(vector <int> w, int maxw) {  
		n = SZ(w), m = 0;
		for(int i = 0; i < n; ++i)
			if(w[i] == -1) m++;
		for(int i = 0; i <= n - m; ++i) {
			// matrix-tree theorem
			memset(g, 0, sizeof g);
			for(int j = 0; j < n; ++j)
				for(int k = j + 1; k < n; ++k)
					if(j < m || k < m + i) g[j][k] = MOD - 1, g[k][j] = MOD - 1, g[k][k]++, g[j][j]++;
			// f[i] means number of situations that truly sweet <= i
			f[i] = det(n - 1);
		}
		// calc combinatoric number 
		memset(com, 0, sizeof com);
		for(int i = 0; i <= n - m; ++i) {
			com[i][0] = 1;
			for(int j = 1; j <= i; ++j)
				com[i][j] = (com[i - 1][j - 1] + com[i - 1][j]) % MOD;
		}
		// inclusion-exclusion
		for(int i = 1; i <= n - m; ++i)
			for(int j = 0; j < i; ++j)
				(f[i] += MOD - (ll)f[j] * com[i][j] % MOD) %= MOD;
		// meet in the middle
		hf = n / 2, w1.clear(), w2.clear();
		for(int i = 0; i < hf; ++i) w1.pb(w[i]);
		for(int i = hf; i < n; ++i) w2.pb(w[i]);
		get(f1, w1), get(f2, w2);
		memset(c, 0, sizeof c);
		for(int i = 0; i < SZ(f2); ++i) c[f2[i].se]++;
		int ret = 0;
		for(int i = 0, j = SZ(f2) - 1; i < SZ(f1); ++i) {
			while(j >= 0 && f1[i].fi + f2[j].fi > maxw) c[f2[j].se]--, j--;
			// c[i] means the number of situation that truly sweet = i in f2[0 ~ j]
			for(int k = 0; k <= n - hf; ++k) (ret += (ll)c[k] * f[f1[i].se + k] % MOD) %= MOD;
		}
		return ret;
	}  
};  
