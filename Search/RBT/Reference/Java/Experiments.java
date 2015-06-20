public class Experiments
{
   public static int experiment(int species, int property, int N)
   {
      RedBlackBST<Integer, Integer> tree;
      tree = new RedBlackBST<Integer, Integer>(species);
      int[] a = StdRandomPlus.perm(N);
      for (int i = 0; i < N; i++)
	  tree.put(a[i], i);
      int result = 0;
      switch (property)
      {
         case 0: result = tree.rootRank(); break;
         case 1: result = tree.sizeRed(); break;
         case 2: result = tree.ipl(); break; 
         case 3: result = tree.ipl() + 2*N - (N+1)*tree.heightB(); break; 
         case 4: result = N*tree.height(); break;
      }
      return result;
   }

   public static void main(String[] args)
   {
      int species = Integer.parseInt(args[0]);   // BST (0), TD234(1), BU23(2)
      int property = Integer.parseInt(args[1]);   // see experiment()
      int  lo = Integer.parseInt(args[2]);        // tree size (low)
      int inc = Integer.parseInt(args[3]);        // tree size increment
      int  hi = Integer.parseInt(args[4]);        // tree size (high)
      int   T = Integer.parseInt(args[5]);        // number of trials
      double scale;
      if (property < 2) scale = 1.0; else scale = 30.0;
      if (property == 3) scale = 5.0;
      StdDraw.setCanvasSize(500, 500);
      double[] results = new double[T];
      double avg = 0.0, sd = 0.0;

      // Draw curve for hypothesis.
      StdDraw.setPenColor(StdDraw.LIGHT_GRAY);
      StdDraw.setPenRadius(.01);
      if (property == 1)
        {
           StdDraw.line(.25, 0, .25, 1);
        }
      double c0 = 0.0;
      double c1 = 0.0;
      if (property == 2) { c0 = 1.0; c1 = 1.5; }
      if (property == 4) 
      {  c0 = 1.3862943611; 
         if (species == 1) c1 = 0.25; 
         else              c1 = 0.0;
      }
      if (property == 2 || property == 4)
        for (int N = lo; N < hi; N += inc)
        {
           double x0 = (c0*Math.log(N)/Math.log(2.0) - c1)/scale;
           double y0 = 1.0*(hi - N )/(hi - lo + 1);
           double x1 = (c0*Math.log(N+inc)/Math.log(2.0) - c1)/scale;
           double y1 = 1.0*(hi - N - inc)/(hi - lo + 1);
           StdDraw.line(x0, y0, x1, y1);
        }

      StdDraw.setPenRadius();
      for (int N = lo; N <= hi; N += inc)
      {
         for (int t = 0; t < T; t++)
	     results[t] = experiment(species, property, N)/(scale*N);
         avg = StdStats.mean(results);
         sd = StdStats.stddev(results);
         StdDraw.setPenColor(StdDraw.BLACK);
         double y = 1.0*(hi - N )/(hi - lo + 1);
         StdDraw.line(avg - 2*sd, y, avg - sd, y);
         StdDraw.line(avg + 2*sd, y, avg + sd, y);
         StdDraw.setPenColor(StdDraw.RED);
         StdDraw.filledCircle(avg, y, .002);
      }
      StdOut.println(avg + " " + sd);
   } 
} 
