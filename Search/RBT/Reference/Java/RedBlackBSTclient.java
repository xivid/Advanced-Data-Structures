public class RedBlackBSTclient
{
   public static void main(String[] args)
   {
      int species = Integer.parseInt(args[0]);
      int N = Integer.parseInt(args[1]);
      RedBlackBST<Integer, Integer> st;
      st = new RedBlackBST<Integer, Integer>(species);
      int[] a = StdRandomPlus.perm(N);
      double[] xpl = new double[N];
      double[] htB = new double[N];
      double htBold = 1;
      for (int i = 0; i < N; i++)
      {
         st.put(a[i], i);
         if (st.heightB() != htBold) 
         {
             htBold = st.heightB();
	     StdOut.print(i + " ");
         }
         if (N < 1111)
         {
            StdDraw.setPenRadius(.0025);
            StdDraw.clear(StdDraw.LIGHT_GRAY);
            st.draw(.95, .003, .004);
            xpl[i] = (1.0*st.ipl() + 2.0*(i+1))/(i+2);
            htB[i] = st.heightB();            
            for (int j = 0; j <= i; j++)
            {
		double x = (0.5 + j)/(i+1);
                double scale = 40.0;
		StdDraw.setPenRadius(.003);
                StdDraw.setPenColor(StdDraw.RED);
                StdDraw.line(x, 0.0, x, xpl[j]/scale);
                StdDraw.setPenColor(StdDraw.BLACK);
                StdDraw.line(x, 0.0, x, htB[j]/scale);
                StdDraw.setPenColor(StdDraw.RED);
                StdDraw.line(x, 0.3, x, 0.3 + (xpl[j]-htB[j])/scale);
            }
            StdDraw.show(100);
         }
      }
      double REDpl = (1.0*st.ipl() + 2.0*(N))/(N+1) - st.heightB();
      StdOut.println();
      StdOut.println("       " + (st.ipl() + 2*N) + " " + 1.0*st.sizeRed()/N);
      StdOut.println("       " + st.heightB() + " " + REDpl);
   }

}
