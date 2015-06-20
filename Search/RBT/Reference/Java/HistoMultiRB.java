public class HistoMultiRB
{
   public static int experiment(int species, int N)
   {
      RedBlackBST<Integer, Integer> tree;
      tree = new RedBlackBST<Integer, Integer>(species);
      int[] a = StdRandomPlus.perm(N);
      for (int i = 0; i < N; i++)
	  tree.put(a[i], i);
      return tree.rootRank();
   }
   public static void main(String[] args)
   {
      StdDraw.setCanvasSize(400, 700);
      StdDraw.show(0);
      int species = Integer.parseInt(args[0]);   // BST (0), TD234(1), BU23(2)
      int lo = Integer.parseInt(args[1]);        // tree size (low)
      int hi = Integer.parseInt(args[2]);        // tree size (high)
      int T = Integer.parseInt(args[3]);         // number of trials
      int s = 0;
      if (args.length > 4)
         s = Integer.parseInt(args[4]);   // smoothing factor
      int M = hi - lo + 1;
      HistogramPlus[] histograms = new HistogramPlus[M]; 
      for (int N = lo; N <= hi; N++)
         histograms[N - lo] = new HistogramPlus(N+1); 
      HistogramPlus scale = new HistogramPlus(lo);
      for (int t = 0; t < T/10; t++)
	  scale.addDataPoint(experiment(species, lo));
      double max = scale.maxS();
	    StdOut.println(max);
      for (int t = 0; t < T; t++)
      {
         StdDraw.clear();
         for (int N = lo; N <= hi; N++)
         {
            double delta = .5*(hi - N + 1)/M;
            histograms[N-lo].addDataPoint(experiment(species, N));
            histograms[N-lo].draw(delta, 2*max, s);
         }
         StdDraw.show(1);
         if (((t+1) % 1000) == 0) StdOut.println(t+1);
      }
   } 
} 
