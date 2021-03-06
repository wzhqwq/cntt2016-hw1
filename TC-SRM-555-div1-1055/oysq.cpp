#line 2 "MapGuessing.cpp"  
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

const int N = 36;

class MapGuessing {  
public:  
	long long countPatterns(string goal, vector <string> _code) {
		string code;
		vector<int> pos[N + 9], validstart;
		bitset<N> posbit[N + 9];
		// concatenating
		for(int i = 0; i < SZ(_code); ++i) code += _code[i];
		int maxnum = 0;// maximum number of positions changed
		for(int i = 0; i < SZ(goal); ++i) {
			// process starts from i
			std::map<int, int> col;
			std::vector<int> curpos;
			bool flag = true;
			int cur = i;
			// simulation
			for(int j = 0; j < SZ(code); ++j) {
				if(code[j] == '0') col[cur] = 0;
				else if(code[j] == '1') col[cur] = 1;
				else if(code[j] == '<') cur--;
				else cur++;
				// not allowed to leave the tape
				if(cur < 0 || cur >= SZ(goal)) {
					flag = false;
					break;
				}
				// check if at any moment it matches the goal
				bool same = true;
				for(map<int, int>::iterator k = col.begin(); k != col.end(); ++k)
					if(goal[k->fi] != k->se + '0') {
						same = false;
						break;
					}
				if(same) {
					curpos.clear();
					for(map<int, int>::iterator k = col.begin(); k != col.end(); ++k)
						curpos.pb(k->fi);
				}
			}
			posbit[i].reset();
			if(flag) {
				pos[i] = curpos;// positions changed if process starts from i
				for(int j = 0; j < SZ(curpos); ++j)
					posbit[i][curpos[j]] = 1;
				// "positions changed if process starts from i" in binary form
				validstart.pb(i);
				// valid starting positions
				chkmax(maxnum, SZ(curpos));
			}
		}
		if(SZ(validstart)) {
			int vsn = SZ(validstart);
			if(vsn <= 22) {
				ll ans = 0;
				// brute force of inclusion-exclusion principle
				for(int i = 1; i < (1 << vsn); ++i) {
					bitset<N> cur;
					for(int j = 0; j < SZ(goal); ++j) cur[j] = 1;
					for(int j = 0; j < SZ(validstart); ++j)
						if(i >> j & 1)
							cur &= posbit[validstart[j]];
					if(__builtin_popcount(i) & 1) ans += 1ll << cur.count();
					else ans -= 1ll << cur.count();
				}
				return ans;
			}
			else {
				set<ll> s;
				for(int i = 0; i < SZ(validstart); ++i) {
					vector<int> p = pos[validstart[i]];
					// enumerate all possible conditions and use a set to store it
					for(int j = 0; j < (1 << SZ(p)); ++j) {
						ll cur = 0;
						for(int k = 0; k < SZ(p); ++k)
							if(j >> k & 1)
								cur |= 1ll << p[k];
						s.insert(cur);
					}
				}
				return SZ(s);
			}
		}
		return 0;
	}
};  
