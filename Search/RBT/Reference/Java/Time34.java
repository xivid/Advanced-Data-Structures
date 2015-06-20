public class Time34
{
   public static void main(String args[]) 
   { 
      int N = Integer.parseInt(args[0]);
      Stopwatch sw = new Stopwatch();
      TreeMapST<Integer, Integer> st1; 
      st1 = new TreeMapST<Integer, Integer>();
      for (int i = 0; i < N; i++)
      { 
	 Integer key = StdRandom.uniform(N/100);
         if (!st1.contains(key)) st1.put(key, 1);
	 //         else                    st1.put(key, st1.get(key) + 1);
      }
      double time1 = sw.elapsedTime();
      sw = new Stopwatch();
      RedBlack23BST<Integer, Integer> st2; 
      st2 = new RedBlack23BST<Integer, Integer>();
      for (int i = 0; i < N; i++)
      { 
	 Integer key = StdRandom.uniform(N/100);
         if (!st2.contains(key)) st2.put(key, 1);
	 //         else                    st2.put(key, st2.get(key) + 1);
      }
      double time2 = sw.elapsedTime();
      StdOut.printf("For %d random searches with %d distinct ", N, N/100);
      StdOut.printf("Integer keys\n  RedBlack23BST is");
      StdOut.printf("  %.1f times faster than TreeMapST\n", time1/time2);
   }
}
