public class Animate
{
    public static void main(String[] args)
    {
        int species = Integer.parseInt(args[0]);
        int N = Integer.parseInt(args[1]);
        int which = 0;
        if (args.length > 2) which = Integer.parseInt(args[2]);

        double lineWidth = .06*Math.log(2.0)/Math.log(N);
        double nodeSize =  lineWidth;
        if (N > 256) nodeSize = nodeSize*.75;
        if (N > 512) nodeSize = 0;
        StdDraw.setCanvasSize(600, 600);
        RedBlackBST<Integer, Integer> st;
        st = new RedBlackBST<Integer, Integer>(species);
        int[] keys = new int[N];
        
        for (int i = 0; i < N; i++)
           keys[i] = StdRandomPlus.uniform(N);

        StdDraw.clear(StdDraw.LIGHT_GRAY);
        StdDraw.show(1000);

        for (int i = 0; i < N; i++)
        {
           st.put(keys[i], i);
           if (which == 0)
           {
              StdDraw.clear(StdDraw.LIGHT_GRAY);
              st.draw(.99, lineWidth, nodeSize);
              if (N < 500)      StdDraw.show(100);
              else              StdDraw.show(10);
	   }
        }

	if (st.check() && which == 3)
        for (int i = 0; i < N/3; i++)
        {
           StdDraw.clear(StdDraw.LIGHT_GRAY);
           st.draw(.99, lineWidth, nodeSize);
           st.mark(keys[2*i + 1]);
           if (st.contains(keys[2*i + 1]))
             st.delete(keys[2*i + 1]);
           st.draw(.5, lineWidth, nodeSize);
           StdDraw.show(500);
           if (!st.check()) break;
        }

	if (st.check() && which == 1)
        for (int i = 0; i < N/3; i++)
        {
           StdDraw.clear(StdDraw.LIGHT_GRAY);
           st.draw(.99, lineWidth, nodeSize);
           st.deleteMin();
           st.draw(.5, lineWidth, nodeSize);
           StdDraw.show(300);
           if (!st.check()) break;
        }

	if (st.check() && which == 2)
        for (int i = 0; i < N/3; i++)
        {
           StdDraw.clear(StdDraw.LIGHT_GRAY);
           st.draw(.99, lineWidth, nodeSize);
           st.deleteMax();
           st.draw(.5, lineWidth, nodeSize);
           StdDraw.show(300);
           if (!st.check()) break;
        }

    }
}
