#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > c;
vector<int> imb, seen;

void doit(int x) {
	if( seen[x] ) return;
	seen[x] = 1;
	for( int i = 0; i < c[x].size(); i++ ) {
		doit(c[x][i]);
		imb[x] += imb[c[x][i]];
	}
}

main() {
	int i, j, k, x, y, z, n;

	while( cin >> n ) {
	  if (!n) break;
		c = vector<vector<int> >(n+1);
		imb = seen = vector<int>(n+1, 0);
		for( i = 0; i < n; i++ ) {
			cin >> x >> y >> z;
			imb[x] = y-1;
			for( j = 0; j < z; j++ ) {
				cin >> y;
				c[x].push_back(y);
			}
		}
		for( i = 1; i <= n; i++ ) doit(i);
		for( i = 1, x = 0; i <= n; i++ ) x += abs(imb[i]);
		cout << x << '\n';
	}
}
