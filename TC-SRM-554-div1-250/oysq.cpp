#line 2 "TheBrickTowerEasyDivOne.cpp"  
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


class TheBrickTowerEasyDivOne {  
public:  
	int find(int rn, int rh, int bn, int bh) {
		if(rh == bh) return std::min(rn, bn) * 2 + (bn != rn);
		else return std::min(rn - 1, bn) + 1 + std::min(rn, bn - 1) + 1 + std::min(rn, bn);
		// 1 : rh + x * (rh + bh) = bh + y * (rh + bh) -> (rh + bh) * (x - y) = bh - rh only if  x = y, bh = rh
		// 2 : rh + x * (rh + bh) = y * (rh + bh) -> (rh + bh) * (y - x) = rh only if x = y , rh = 0 which is impossible
	}  
};  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     