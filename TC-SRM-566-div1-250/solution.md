#PenguinSledding
作者：丁力煌
关键词：图论 数学
##题目描述
给定一个n个点m条边的图，求有多少个边的子集，使得无论这n个点在平面上怎么分布，这个子集里的边两两不相交。
$$n,m\leq50$$
##分析
考虑什么样子的边的子集是符合条件的。容易知道，如果一个图中的最长链$$\geq 3$$，那么由题目描述中的unsafe情况知道这样是不符合条件的，所以一个符合条件的图的最长链$$\leq 2$$，容易知道这个图中要么存在一个点与所有其他点都相邻，要么是一个三角形。
##算法
先计算出三角形个数，时间复杂度$$O(n^3)$$；再枚举一个点i做为中心，方案数则为$$2^d(i)-1$$，由于这时候每条边会被计算2次，所以最后减去边数即可。总时间复杂度$$O(n^3)$$
