#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int MAX = 20 + 5;                  //the upper limit of the maze size
char map[MAX][MAX];                  //maze
bool visPerson[MAX][MAX];             // the path that you walk in the maze 
bool visBox[MAX][MAX];               // the path that the box is pushed
int R, C;                              // the size of the maze R*C
int dir[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}}; // displacement in 4 directions
char pushes[4] = {'E', 'W', 'S', 'N'};         //Characters for pushing the box
char walks[4] = {'e', 'w', 's', 'n'};           // Characters for your walking
string path;                            // the sequence of minimal moves
struct NODE                          // the structure for state
{
    int br, bc;                        // the position of the box
    int pr, pc;                        //your position
    string ans;                       // the sequence of moves
};
bool InMap(int r, int c)                 //whether (r, c) is in the maze
{
    return (r >= 1 && r <= R && c >= 1 && c <= C);
}
bool Bfs2(int sr, int sc, int er, int ec, int br, int bc, string & ans) 
// BFS is used to solve the problem whether you can walk to (er, ec) from (sr, sc) or not.
//(er, ec) must be adjacent to (br, bc).
{
    memset(visPerson, false, sizeof(visPerson));  //Initialization
    queue<NODE> q;                   //Queue q is used to store states
    NODE node, tmpNode;              // node: the front of q, tmpNode: new extended state
node.pr = sr;  node.pc = sc;  node.ans = "";  
// Initial state (your current position(sr, sc), the sequence of moves is empty) is added into q
    q.push(node);
     visPerson[br][bc] = true;                  //the current position of box (br, bc) 
    while (!q.empty())            //while q isn’t empty, the front is taken out
    {
        node = q.front();
        q.pop();
        if (node.pr==er && node.pc==ec) { ans = node.ans; return true; } 
// if you walk to (er, ec), return successful mark and the sequence of moves
        if (visPerson[node.pr][node.pc]) continue; 
        visPerson[node.pr][node.pc] = true;  
        for (int i=0; i<4; i++)                  //4 directions are enumerated
        {  //the adjacent cell in direction i (nr, nc): if the cell is in the maze, isn’t filled with rock and you didn’t walk to it , a new state tmpNode is produced (the current position (nr, nc)), the character of direction i is added to the sequence of moves, and tmpNode is added into q
            int nr = node.pr + dir[i][0]; int nc = node.pc + dir[i][1]; 
            if (InMap(nr, nc) && !visPerson[nr][nc] && map[nr][nc] != '#')
            {
                tmpNode.pr = nr; tmpNode.pc = nc; tmpNode.ans = node.ans + walks[i]; 
                q.push(tmpNode);
            }
        }
    }
    return false;  
}
bool Bfs1(int sr, int sc, int br, int bc)            //your position (sr, sc), the position of the box is (br, bc). BFS is used to determine whether the box can be pushed to the target cell
{
    memset(visBox, false, sizeof(visBox));     // Initialization
    queue<NODE> q;                      //queue q is used to store states
NODE node, tmpNode;           // node: the front of q, tmpNode: new extended state
// Initial state (your current position(sr, sc), the position of the box is (br, bc), the sequence of moves is empty) is added into q
    node.pr = sr; node.pc = sc; node.br = br; node.bc = bc; node.ans = "";
    q.push(node);
    while (!q.empty())                     // while q isn’t empty, the front is taken out
    {
        node = q.front();
        q.pop();
        if (visBox[node.br][node.bc]) continue; 
        visBox[node.br][node.bc] = true; 
        if (map[node.br][node.bc] == 'T')     // Target cell
        {
            path = node.ans; return true;
        }
        for (int i=0; i<4; i++)              // 4 directions are enumerated
        {
// the adjacent cell in direction i (nextr, nextc) for the box, and its opposite adjacent cell (backR, backC). The box can be pushed to (nextr, nextc) if and only if you can walk to (backR, backC).
            int nextr = node.br + dir[i][0]; int nextc = node.bc + dir[i][1];
            int backR = node.br - dir[i][0]; int backC = node.bc - dir[i][1];
            string ans = "";               //Initialize the sequence of moves
//If (backR, backC) and (nextr, nextc) are in the maze, aren’t filled with rock, and the box didn’t come to (nextr, nextc), then BFS is used to determine whether you can walk to (backR, backC). If successful, the new state tmpNode is produced and pushed into q. 
            if (InMap(backR, backC) && InMap(nextr, nextc) && map[nextr][nextc] != '#'
                && map[backR][backC] != '#' && !visBox[nextr][nextc])
            {
                if (Bfs2(node.pr, node.pc, backR, backC, node.br, node.bc, ans))
                {
                    tmpNode.pr = node.br; tmpNode.pc = node.bc;
                    tmpNode.br = nextr; tmpNode.bc = nextc;
                    tmpNode.ans = node.ans + ans + pushes[i];
                    q.push(tmpNode);
                }
            }
        }
    }
    return false; 
}
int main()
{
    int sr, sc;                                // your starting position
    int br, bc;                                // the position of box
    int cases = 1;                              //the number of test case
    while (scanf("%d%d", &R, &C) && R && C)   //input test cases
    {
        for (int r=1; r<=R; r++)                 //input maze
        {
            for (int c=1; c<=C; c++)
            {
                cin >> map[r][c];
                if (map[r][c] == 'S'){ sr = r; sc = c; }           // your starting position
                   else if (map[r][c] == 'B') { br = r; bc = c; }   // the position of box
            }
        }
                path = "";                     //Initialize the sequence of moves
//If the box can be pushed to the target, then output the minimal sequence of moves; else output “Impossible.”
        (Bfs1(sr, sc, br, bc)) ? cout << "Maze #" << cases << endl << path << endl :
                          cout << "Maze #" << cases << endl << "Impossible." << endl;
        cases++;  
        cout << endl; 
    }
    return 0;
}
