
/*************************************************************************
 *  Compilation:  javac Bernoulli.java
 *  Execution:    java Bernoulli N
 *  Dependencies: StdDraw.java
 *  
 *  Each experiment consists of flipping N fair coins. Plots (in real
 *  time) a histogram of the number of times i of the N coins are heads.
 *
 *  % java Bernoulli 32
 *
 *  % java Bernoulli 64
 *
 *  % java Bernoulli 128
 *
 *************************************************************************/



public class Bernoulli { 

    // number of heads when flipping N coins biased-p coins
    public static int binomial(int N, double p) {
        int heads = 0;
        for (int j = 0; j < N; j++) {
            if (StdRandomPlus.bernoulli(p)) {
                heads++;
            }
        }
        return heads;
    } 

    // number of heads when flipping N fair coins
    public static int binomial(int N) {
        return binomial(N, 0.5);
    } 



    public static void main(String[] args) { 
        int N = Integer.parseInt(args[0]);   // number of coins to flip per trial
        int T = Integer.parseInt(args[1]);   // number of trials

        StdDraw.setYscale(0, 0.2);

        // flip N fair coins, T times
        int[] freq = new int[N+1];
        for (int i = 0; i < T; i++) {
            freq[binomial(N)]++;
        }

        // plot normalized values
        double[] normalized = new double[N+1];
        for (int i = 0; i <= N; i++) {
            normalized[i] = (double) freq[i] / T;
        }
        StdStats.plotBars(normalized);

        // plot Gaussian approximation
        double mean = N / 2.0;
        double stddev = Math.sqrt(N) / 2.0;
        double[] phi  = new double[N+1];
        for (int i = 0; i <= N; i++) {
            phi[i] = Gaussian.phi(i, mean, stddev);
        }
        StdStats.plotLines(phi);
    } 
} 
