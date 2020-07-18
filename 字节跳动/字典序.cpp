/**
 * 问题：
 * 给定整数n和m, 将1到n的这n个整数按字典序排列之后, 求其中的第m个数。
 * 对于n=11, m=4, 按字典序排列依次为1, 10, 11, 2, 3, 4, 5, 6, 7, 8, 9, 因此第4个数是2.
 * 
 * 解决思路：
 * 将字典序看作一个树，有如下特点：
 *                  1                                        2                                      3
 *       /          |           \                 /          |            \             /           |            \
 *      10          11           12             20           21           22           30           31            32
 *   /  |  \     /  |  \     /   |   \      /   |   \      / | \      /   |   \      / | \       /  |   \       /  |   \
 * 100 101 102 110 111 112  120 121 122    200 201 202  210 211 212  220 221 222  300 301 302  310 311 312   320  321  322
 * 每个节点都有一个序号，是它的先序遍历顺序。
 * 我们可以计算一棵树的节点数量：先设定好一棵树和它的边界，边界取相邻的树的最左边的节点，在树的最底端取n；
 * 设置两个变量：index代表先序序号，初值为1；tree代表树的节点，值为它指向的节点的值。
 * 如果发现1号树的节点数量+index < m,则测量二号树，index加上节点数量；
 * 若节点数量+index >= m,则index + 1（即移到最左边的子节点的序号），继续测量10号树…………
 * 当index == m时，tree指向的就是结果。
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	long n, m;
	cin >> n >> m;
	long index = 1;
	long tree = 1;
	while (index < m) {          
		long count = 0;
		long left = tree, right = left + 1;    //边界为相邻的树的最左边的节点
		while (left <= n) {                     //防止测量过深
			count += min(n+1,right) - left;    //如果没有到达最底层，边界为right;如果到达，则为n
			right *= 10;
			left *= 10;                       //测量下一层
		}
		if ((index + count) > m) {          //如果目标节点在tree所在的树上
			tree *= 10;                     //从tree的最左的子树开始测量
			index++;                        //index移动到子树的根节点的序号
		}
		else {                             //如果不在tree所在的树上
			tree++;                        //tree右移
			index += count;                //index跨越一棵树
		}
	}
	cout << tree << endl;
}