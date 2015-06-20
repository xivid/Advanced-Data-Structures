/*************************************************************************
 *  Compilation:  javac Stopwatch.java
 *
 *
 *************************************************************************/

public class Stopwatch { 

   private final long start;

   public Stopwatch() {
       start = System.currentTimeMillis();
   } 

   // return time (in seconds) since this object was created
   public double elapsedTime() {
       return (System.currentTimeMillis() - start) / 1000.0;
   } 


} 
