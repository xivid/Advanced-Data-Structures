public class HistoRB
{
   public static int experiment(int N)
   {
      RedBlackBST<Integer, Integer> tree = new RedBlackBST<Integer, Integer>();
      int[] a = StdRandomPlus.perm(N);
      for (int i = 0; i < N; i++)
	  tree.put(a[i], i);
      return tree.rootRank();
   }
   public static void main(String[] args)
   {
      StdDraw.setCanvasSize(1000, 400);
      StdDraw.show(0);
      int N = Integer.parseInt(args[0]);   // tree size
      int T = Integer.parseInt(args[1]);   // number of trials
      int s = Integer.parseInt(args[2]);   // smoothing factor
      HistogramPlus histogram = new HistogramPlus(N+1); 
      for (int t = 0; t < T; t++)
      {
         histogram.addDataPoint(experiment(N));
         StdDraw.clear();
         histogram.draw(s);
         StdDraw.show(10);
      }
   } 
} 
