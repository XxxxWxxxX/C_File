#include <iostream>
#include <stack>
#include <queue>
#include <cstdio>

using namespace std;

const int MXN = 1007;

int n;
int op[MXN], x[MXN];

int main()
{
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; ++i)
			scanf("%d%d", op + i, x + i);

		stack<int> st;
		queue<int> q;
		priority_queue<int> heap;

		bool flag1 = true, flag2 = true, flag3 = true;
		for (int i = 0; i < n; ++i)
			if (op[i] == 1) st.push(x[i]);
			else {
				if (st.empty()) {
					flag1 = false;
					break;
				}
				int u = st.top();
				st.pop();
				if (u != x[i]) {
					flag1 = false;
					break;
				}
			}
		for (int i = 0; i < n; ++i)
			if (op[i] == 1) q.push(x[i]);
			else {
				if (q.empty()) {
					flag2 = false;
					break;
				}
				int u = q.front();
				q.pop();
				if (u != x[i]) {
					flag2 = false;
					break;
				}
			}
		for (int i = 0; i < n; ++i)
			if (op[i] == 1) heap.push(x[i]);
			else {
				if (heap.empty()) {
					flag3 = false;
					break;
				}
				int u = heap.top();
				heap.pop();
				if (u != x[i]) {
					flag3 = false;
					break;
				}
			}
		if (!flag1 && !flag2 && !flag3) {
			puts("impossible");
			continue;
		}
		if (flag1 && !flag2 && !flag3) {
			puts("stack");
			continue;
		}
		if (!flag1 && flag2 && !flag3) {
			puts("queue");
			continue;
		}
		if (!flag1 && !flag2 && flag3) {
			puts("priority queue");
			continue;
		}
		puts("not sure");
	}
}
