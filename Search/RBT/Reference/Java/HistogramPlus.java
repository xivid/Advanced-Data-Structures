/*************************************************************************
 *
 *  This data type supports simple client code to create dynamic
 *  histograms of the frequency of occurrence of values in [0, N).
 *  The frequencies are kept in an instance-variable array, and
 *  an instance variable max tracks the maximum frequency (for scaling).
 *
 *  % java HistogramPlus 50 1000000 
 *
 *************************************************************************/

public class HistogramPlus {
    private final double[] freq;   // freq[i] = # occurences of value i
    private double max;            // max frequency of any value
    private double total;          // total number of data points

    // Create a new histogram. 
    public HistogramPlus(int N) {
        freq = new double[N];
    }

    // Add one occurrence of the value i. 
    public void addDataPoint(int i) {
        freq[i]++; 
        if (freq[i] > max) max = freq[i]; 
        total++;
    } 

    public double maxS()
    {  return max/total;  }

    // draw (and scale) the histogram.
    public void draw()
    {
	draw(0.0, 1.0, 0);
    }

    // offset, smoothed version.
    public void draw(double offset, double scale, int k)
    {  
       int N = freq.length;
       double[] freqS = new double[N];
       for (int i = 0; i < N; i++)
          freqS[i] = freq[i];
       for (int i = k; i < N-k; i++)
       {
         double sum = 0.0;
         for(int j = -k; j <= k; j++)
	     sum += freq[i+j];
         freqS[i] = sum/(2*k + 1);
       }
       for (int i = 0; i < N; i++)
	    freqS[i] = offset + freqS[i]/total/scale;
       StdStats.plotLines(freqS);
    } 
    // See Program 2.2.6.
    public static void main(String[] args) {

        StdDraw.setCanvasSize(500, 100);
        StdDraw.show(0);

        int N = Integer.parseInt(args[0]);   // number of coins
        int T = Integer.parseInt(args[1]);   // number of trials

        HistogramPlus histogram = new HistogramPlus(N+1); 
        for (int t = 0; t < T; t++) {
            histogram.addDataPoint(Bernoulli.binomial(N));
            StdDraw.clear();
            histogram.draw();
            StdDraw.show(10);
        }
    } 
} 
