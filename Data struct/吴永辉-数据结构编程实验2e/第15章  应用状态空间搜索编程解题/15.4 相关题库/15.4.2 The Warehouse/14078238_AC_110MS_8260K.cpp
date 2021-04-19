#include<iostream>
using std::cin;
using std::cout;
using std::endl;
#include<cstdio>
#include<cstring>
const long MAXN = 10;        //The upper limit of the size of the warehouse
const long MAXH = 1048575;   // The upper limit of the length of Hash table and queue
const long fx[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  //Four directions
struct Tmap    //the structure of the state
{
   long data[MAXN][MAXN]; //Map of the warehouse, 
// where data[i][j]= 
   long x, y;   //the position of Θ- 7
};
long n, x, y, tx, ty; //the size of the warehouse is n*n, the exit is (tx, ty)
Tmap a;  // the current state
Tmap queue[1048580];   // the queue storing states
long hash[1048580];   // Hash table storing pointers for the queue
long dep[1048580];   // queue storing the number of steps
void init( )       // Input data and set up initial state
{
   char st[MAXN];  //string for the current row
   long i, j;
   memset(a.data, 0xff, sizeof(a.data));  // Initialize cells in the warehouse -1
   for (i=1; i<=n; ++i)     // input the warehouse row by row
   {
      scanf("%s", st);    // the i-th row
      for (j=0; j<n; ++j)   
      {
        if (st[j] == '.') a.data[i][j+1] = 0;
        else if (st[j] == 'E')      // (i, j+1) is exit
        {
           a.data[i][j+1] = 1;  // the position can’t be occupied by other boxes
           tx = i;
           ty = j + 1;       // the position of exit
        }
        else a.data[i][j+1] = st[j] - '0';  // the height of the box at (i, j+1)
      }
   }
   a.x = x;
   a.y = y;   // the start position of Θ- 7
}
long gethash(const Tmap &a)
// Calculate the hash address for state a: Firstly, from top to down, and from left to right, numbers in cells in state a are regards as a quinary number (a11,…,a1n, …ann)5. Secondly, an integer t is gotten as followed. The quinary number is transferred into its corresponding decimal number, then two digits are added at the end of the corresponding decimal number, and the two digits x and y are the coordinate of Θ- 7. Finally the Hash address for state a is t&(the size of Hash table).
{
   long i, j, t = 0;   
   for (i=1; i<=n; ++i)
   for (j=1; j<=n; ++j)
      t = (t * 5 + a.data[i][j]) & MAXH;
   t = (t * 10 + a.x) & MAXH;
   t = (t * 10 + a.y) & MAXH;
   return t;
}
bool thesame(const Tmap &a, const Tmap &b)
// Determine whether state a and state b are same or not
{
   long i, j;
// If positions of Θ- 7 in state a and state b aren’t same, or two corresponding cells in state a and state b aren’t same; then return false; else return true
   if ((a.x != b.x) || (a.y != b.y)) return false;
   for (i=1; i<=n; ++i)
   for (j=1; j<=n; ++j)
   if (a.data[i][j] != b.data[i][j]) return false;
   return true;
}
bool get(const Tmap &a)
// Determine whether state a has been appeared in the queue
{
   long k = gethash(a);  // Calculate Hash value k for state a
   while (hash[k] != 0)
   {
      if (thesame(queue[hash[k]], a)) return true;
      k = (k + 1) & MAXH;
   }
   return false;  // state a didn't appeare
}
bool run(const Tmap &a, Tmap &b, long d)
//If new state b can be gotten from state a expanded in direction d, then the new state b and successful mark true are returned; else return false
{
   long x = a.x + fx[d][0];
   long y = a.y + fx[d][1];  //(x, y) is adjacent cell for position of Θ- 7 in state a in direction d
   b = a;
// If (x, y) is out of the boundary, return false; 
   if (a.data[x][y] == -1) return false;
// If (x, y) isn't empty, record the position of Θ- 7 in state b and return true
   if (a.data[x][y] > 0)
   {
      b.x = x;
      b.y = y;
      return true;
   }
//if the position of Θ- 7 in state a can’t be occupied by other boxes, then return false
   if (a.data[a.x][a.y] < 2) return false;
//enumerate every height i for box: in direction the i-th cell isn’t empty, then return false; else the height of the cell in state b is 1
   for (long i=1; i<=a.data[a.x][a.y]; ++i) //enumerate
   {
      if (a.data[a.x+fx[d][0]*i][a.y+fx[d][1]*i] != 0) return false;
      b.data[a.x+fx[d][0]*i][a.y+fx[d][1]*i] = 1;
   }
// the box at the position of Θ- 7 in state a is toppled in direction d, the position is empty in state b, (x, y) is the position of Θ- 7, and return true
   b.data[a.x][a.y] = 0;
   b.x = x;
   b.y = y;
   return true;
}
void save(long a)       //direct addressing, pointer for queue rear a is stored in Hash table
{
   long k = gethash(queue[a]);
   while (hash[k] != 0) k = (k + 1) & MAXH;
   hash[k] = a;
}
void solve(void)  //calculate and output the solution
{
   long open = 0;  //Initialize pointers for the front and rear for the queue
   long closed = 1;
   long i;
   Tmap k, k2;
   memset(hash, 0x00, sizeof(hash));  //Initialize Hash Table
   queue[1] = a; dep[1] = 0; //map of warehouse and the number of steps 0 are added into queues
   while (open < closed )  // while the queue isn’t empty
   {
      k = queue[++open]; // the front of the queue
      for (i=0; i<4; ++i)   // 4 directions are enumerated
      if (run(k, k2, i))  //new state k2 can be gotten from state k in direction i
      if (!get(k2))  //state k2 is different from all states in the queue
      {
         queue[++closed] = k2;  //state k2 and number of steps are added into the queue
         dep[closed] = dep[open] + 1;
         if ((k2.x == tx) && (k2.y == ty)) // state k2 is exit
         {
            printf("%ld\n", dep[closed]);
            return;
         }
         save(closed); //pointer closed pointing to the rear of the queue is stored in Hash Table
      }
   }
   printf("Impossible.\n");  //output impossible
}
int main( )
{
   while ((scanf("%ld %ld %ld", &n, &x, &y) != EOF) && n && x && y)
   {
      init( ); // Input data and set up initial state
      solve( ); //calculate and output the solution
   }
   return 0;
}
