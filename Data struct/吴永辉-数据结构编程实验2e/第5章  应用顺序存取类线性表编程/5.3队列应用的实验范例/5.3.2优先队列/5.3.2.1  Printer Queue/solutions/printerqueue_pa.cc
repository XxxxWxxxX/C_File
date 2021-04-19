/* Sample solution for NWERC'06: Printer Queue
 * Author: Per Austrin
 * Algorithm: Straightforward Simulation
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int main(void) {
  int q[150], n, m, t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) scanf("%d", q+i);
    int time = 0;
    for (int p = 0; q[m] > 0; (++p) %= n)
      if (q[p] > 0) {
	int mx = 0;
	for (int i = 0; i < n; ++i) mx = max(mx, q[i]);
	if (q[p] >= mx) { 
	  ++time;
	  q[p] = 0;
	}
      }
    printf("%d\n", time);
  }
  return 0;
}
