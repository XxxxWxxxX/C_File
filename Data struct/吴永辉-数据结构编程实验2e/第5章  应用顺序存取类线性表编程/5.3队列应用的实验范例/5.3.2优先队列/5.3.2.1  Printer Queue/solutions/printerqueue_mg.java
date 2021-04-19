/* NWERC 2006
 * Sample solution to Printer Queue
 * By Mikael Goldmann
 */
import java.util.*;

public class printerqueue_mg 
{
    static Scanner in=new Scanner(System.in);

    public static void main(String[] args) throws Exception
    {
	for (int N=in.nextInt(); N>0; --N){	    
	    int n=in.nextInt(), pos=in.nextInt();
	    int[] q=new int[n];
	    int[] nprio = new int[10];	    
	    for (int i=0; i<n; ++i) nprio[q[i]=in.nextInt()]++;
	    int hd=0, tm=0, res=0;	    
	    for (int prio=9; res==0; --prio) {
		while(res ==0 && nprio[prio]-->0) {
		    while (q[hd] != prio) hd=(hd+1)%n;		    
		    q[hd]=-q[hd];
		    ++tm;
		    if (hd==pos) res = tm;
		}
	    }
	    System.out.println(res);
	}
    }
}
