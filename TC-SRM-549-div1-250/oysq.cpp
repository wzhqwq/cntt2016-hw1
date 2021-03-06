#line 2 "PointyWizardHats.cpp"  
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

const int N = 50;

class PointyWizardHats {  
public:
	int ans, n, m;
	bool g[N + 9][N + 9], vis[N + 9];
	int mat[N + 9];
	bool dfs(int x) {
		for(int i = 0; i < m; ++i)
			if(g[x][i] && !vis[i]) {
				vis[i] = true;
				if(mat[i] == -1 || dfs(mat[i])) {
					mat[i] = x;
					return true;
				}
			}
		return false;
	}
	int getNumHats(vector <int> h1, vector <int> r1, vector <int> h2, vector <int> r2) {  
		ans = 0, n = SZ(h1), m = SZ(h2);
		memset(g, false, sizeof g), memset(mat, -1, sizeof mat);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(r1[i] < r2[j]) {
					// r1[i] / r2[j] = h / h2[j]
					// h = r1[i] / r2[j] * h2[j] < h1[i]
					if(r1[i] * h2[j] < r2[j] * h1[i])
						g[i][j] = true;
				}
		// bipartite graph matching
		for(int i = 0; i < n; ++i) {
			memset(vis, false, sizeof vis);
			ans += dfs(i);
		}
		return ans;
	}  
};  
