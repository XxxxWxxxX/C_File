/**********************************************************************
 * 
 * First notice we start with (1,1) and only ever increase the numbers,
 * so all values are positive. Now since a left child contains (a+b,b)
 * and a right child contains (a,a+b), it's easy to see for a given
 * node whether it's a left or right child: Simply look whether its
 * first or second value is larger. And to get to the parent node,
 * simply subtract the smaller value from the larger, e.g. for (a+b,b)
 * subtract b from a+b to get ((a+b)-b,b) = (a,b), the parent. So it's
 * easy to get from a node upwards to its parent node, and from there
 * further up, until we reach the root of the tree. So we just walk
 * upwards, counting the lefts and rights. That's all.
 * 
 * There's a little gotcha, though. Imagine the node (1000000000,1).
 * We'd go from there up to (999999999,1), then to (999999998,1), etc.
 * We'd do a billion steps! That's too slow. So instead of always only
 * going one step upwards, we compute how many steps we'll go upwards
 * in the same direction. In the example, we'd compute that we'll go
 * 999999999 steps upwards, directly jumping from (1000000000,1) to (1,1).
 * 
 * But if we for example have (32,5), how often exactly must we subtract
 * 5 from 32? Well, we want to reach a value in [1,5]. Getting from 32
 * down into [1,5] takes as many steps as getting from 31 down into [0,4]
 * which is the remainder part of the division. So we just subtract 1
 * from 32 and then divide by 5. You can see the general way in the code.
 * 
 **********************************************************************/

#include <iostream>
using namespace std;

int main () {
  int SC;
  cin >> SC;
  for( int S=1; S<=SC; S++ ){
    cout << "Scenario #" << S << ":" << endl;
    
    //--- Read the testcase data.
    int a, b;
    cin >> a >> b;
    
    //--- Dance...
    int left = 0, right = 0;
    while( a > 1  ||  b > 1 ){
      if( a > b ){
	int up = (a - 1) / b;
	left += up;
	a -= up * b;
      } else {
	int up = (b - 1) / a;
	right += up;
	b -= up * a;
      }
    }
    
    //--- Answer.
    cout << left << " " << right << endl << endl;
  }
}
