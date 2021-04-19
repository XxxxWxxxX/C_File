// Leaf prunning.

// Each leaf keeps information about the subtree that was reduced
// to the leaf during the course of the algorithm, it is the number
// of surplus marbles in the subtree, when negative it is the number of missing
// marbles in the subtree.

// Initially, each vertex has the value m equal the number of original marbles
// at it.

// Let set L be the set of leaves of the tree.
// tcost = 0
// while card(L) > 1
//   pick a member of L, name it v
//   switch m[v] of
//   case m[v] < 0
//     tcost += -m[v]           // all have to walk this step from the parent
//     m[parent[v]] += m[v]
//   case m[v] = 0
//     tcost++                  // 1 has to walk from the parent
//     m[parent[v]--   
//   else
//     tcost += m[v]-1          // 1 has to stay the rest has to walk 
//                              // to the parent
//     m[parent[v]] += m[v]-1
//   

// P. Rudnicki, Edmonton, April 8th 

#include <stdio.h>
#include <set>

#define MAXN 10000

int m[MAXN], parent[MAXN];
set<int> children[MAXN];
set<int> leaves, nleaves;
int main () {
  int n, tcost;
  while (scanf("%d",&n) == 1) {
    if (!n) break;
    leaves.clear();
    tcost = 0;
    for(int i = 1; i <= n; i++) {
      int v, d;
      scanf("%d",&v);
      scanf("%d%d",&m[v],&d);
      for(int j = 1; j <= d; j++) {
	int c;
	scanf("%d",&c);
	children[v].insert(c);
	parent[c] = v;
      }
      if (!d) leaves.insert(v);
    }
    set<int>:: iterator pos;
    while (leaves.size() != 1) {
      nleaves.clear();
      for(pos = leaves.begin(); pos != leaves.end(); pos++) {
	if (m[*pos] <= 0) {
	  tcost += -m[*pos]+1;
	  m[parent[*pos]] += m[*pos]-1;
	} else {
	  tcost += m[*pos]-1;
	  m[parent[*pos]] += m[*pos]-1;
	}
	children[parent[*pos]].erase(*pos);
	if (children[parent[*pos]].empty()) 
	  nleaves.insert(parent[*pos]);
      }
      leaves = nleaves;
    }
    printf("%d\n",tcost);
  }
}
