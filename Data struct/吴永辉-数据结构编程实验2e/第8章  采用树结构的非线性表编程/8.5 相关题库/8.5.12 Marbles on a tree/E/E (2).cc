#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

int cost;
vector<int> child[100005];
int marbles[100005],sizet[100005],count[100005],parent[100005];

// determine the size of the tree rooted at 'at', and count
// how many marbles are in this tree.
void init(int at)
{
	sizet[at] = 1;
	count[at] = marbles[at];
	for (int i=0; i<child[at].size(); i++) {
		 init(child[at][i]);
		 sizet[at] += sizet[child[at][i]];
		 count[at] += count[child[at][i]];
	}
}

// solve the subtree with root 'at'
int doit(int at)
{
	int i,c;
	for (i=0; i<child[at].size(); i++) { 
		// child has more than enough marbles:
		// finish it off and receive the surplus.
		if (count[child[at][i]] >= sizet[child[at][i]]) {
			c = doit(child[at][i]);
			marbles[at] += c;
			cost += c;
			child[at][i] = -1;
		} 
	}
	// now finish off the other children
	for (i=0; i<child[at].size(); i++) { 
		if (child[at][i]==-1) continue; 
		c = sizet[child[at][i]] - count[child[at][i]];
		marbles[at] -= c;
		marbles[child[at][i]] += c;
		cost += c;
		doit(child[at][i]);
	}
	// send the surplus up
	return marbles[at] - 1;
}

int main()
{
	int i,j,at,v,c,n,root;
	while (scanf("%d ", &n)==1) {
	  if (!n) break;
		memset(parent, -1, sizeof(parent));
		memset(marbles, 0, sizeof(marbles));
		memset(sizet, 0, sizeof(sizet));
		memset(count, 0, sizeof(count));
		for (i=0; i<100005; i++) child[i].clear();	
		for (i=0; i<n; i++) {
			scanf("%d %d %d ", &at, &c, &v);
			marbles[at] = c;
			for (j=0; j<v; j++) {
				scanf("%d ", &c);
				child[at].push_back(c);
				parent[c] = at;
			}
		}
		for (root=1; root<=n; root++) if (parent[root]==-1) break;
		cost = 0;
		init(root);
		doit(root);
		printf("%d\n", cost);
	}
	return 0;
}
