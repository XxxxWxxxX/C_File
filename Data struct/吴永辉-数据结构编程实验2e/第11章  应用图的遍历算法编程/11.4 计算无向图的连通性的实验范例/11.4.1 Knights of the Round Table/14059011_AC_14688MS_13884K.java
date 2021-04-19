import java.lang.*; 
import java.math.*;
import java.util.*;
public class Main {    
	public static void print(String x) { 
		System.out.print(x);
	}
	static int N, M;                  // Numbers of vertices and edges
	static boolean G[ ][ ], ok[ ], flag;     //G: an adjacency matrix; ok: a mark sequence for expelled knights; flag: a mark for an odd cycle
	static int[ ] low, pre, color, st; 
	static int[ ][ ] ans = new int[1 << 10][1 << 10];  // ans: current block;
	static int r, sp, cnt; 
	static void dfs(int c) { 
		st[sp++] = c;                        //c is pushed into the stack
		pre[c] = low[c] = ++cnt;              //Initialization
		for (int i = 0; i < N; i++)              // Search vertices adjacent to c
			if (G[i][c]) {                   // If (c, i)G, 
				if (pre[i] == 0) {            //If it is the first time that t is visited
			  	 dfs(i);
				 if (low[i]<low[c])
						low[c] = low[i];
  				if (low[i] >= pre[c]) { 
						int k = 0;  
						st[sp] = -1;
						ans[r][0] = c;       // vertex c into ans[r]
						while (st[sp] != i)
							ans[r][++k] = st[--sp];
						ans[r][++k] = -1;  
						if (k > 2)          // if number of vertices > 2, it is a block
							r++;
					}
				} else if (pre[i] < low[c])  //(c, i) is a back edge, low[c]=min{pre[i], low[c]}
					low[c] = pre[i];
			}
	}
	static void dfs(int pnt, int c, int col) {  
		if (flag)                     // if the block has an odd cycle
			return;
		for (int i = 0; i < N; ++i) {  
			if (G[c][i] && color[i] != 0 && i != pnt && i != c) {
		  	  if (color[i] == 1){     // if vertex i isn’t in the path
					color[i] = col;
					dfs(c, i, -col);
				} else if (color[i] == color[c]) { // the block has an odd cycle
					flag = true;
					return;
				}
			}
		}
	}
	static void solve(int c) {       // determine vertices whether should be expelled
		int now = 0;   
		while (ans[c][now] != -1) {
			color[ans[c][now]] = 1;
			++now;
		}
		flag = false; 
		color[ans[c][0]] = 2;   
		dfs(-1, ans[c][0], -2); 
		now = 0;  
		while (ans[c][now] != -1) {
			color[ans[c][now]] = 0;
			if (flag)
				ok[ans[c][now]] = true;
			++now;
		}
	}
	public static void main(String args[ ]) {
		Scanner input = new Scanner(System.in);
		st = new int[1 << 10];
		while ((N = input.nextInt()) != 0) {  // Input numbers of vertices and edges N and M
			M = input.nextInt();
			G = new boolean[N][N];
			ok = new boolean[N];
			low = new int[N];
			pre = new int[N];
			color = new int[N];
			sp = r = 0;  
			for (int i = 0; i < N; i++)       // Initialization: a complete graph
				for (int j = 0; j < N; j++)
					G[i][j] = true;
			for (int i = 0; i < M; i++) {     //delete knights who hate each other
				int x = input.nextInt() - 1, y = input.nextInt() - 1;
				G[x][y] = false;
				G[y][x] = false;
			}
			pre = new int[N]; 
			for (int i = 0; i < N; i++) 
				if (pre[i] == 0)        // vertex i isn’t visited
					dfs(i);
			for (int i = 0; i < r; i++)     // Calculate expelled knights
				solve(i);
			int kick = 0;              // Calculate the number of expelled knights
			for (int i = 0; i < N; ++i)   
				if (ok[i] == false)
					++kick;
			print(kick + "\n");         // output the number of expelled knights
		}
	}
}
