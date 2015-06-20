/*************************************************************************
 *  Compilation:  javac ST.java
 *  Execution:    java ST
 *  
 *  Symbol table implementation using Java's java.util.TreeMap library.
 *  Does not allow duplicates.
 *
 *  % java ST
 *  128.112.136.11
 *  208.216.181.15
 *  null
 *
 *************************************************************************/

import java.util.TreeMap;
import java.util.Iterator;

public class ST<Key extends Comparable<Key>, Val> implements Iterable<Key> {


   /***********************************************************************
    * Test routine.
    **********************************************************************/
    public static void main(String[] args) {
        ST<String, String> st = new ST<String, String>();

        // insert some key-value
        st.put("www.cs.princeton.edu", "128.112.136.11");
        st.put("www.princeton.edu",    "128.112.128.15");
        st.put("www.yale.edu",         "130.132.143.21");
        st.put("www.amazon.com",       "208.216.181.15");
        st.put("www.simpsons.com",     "209.052.165.60");

        // search for IP addresses given URL
        System.out.println(st.get("www.cs.princeton.edu"));
        System.out.println(st.get("www.amazon.com"));
        System.out.println(st.get("www.amazon.edu"));
        System.out.println();

        // print out all key-value pairs
        for (String s : st)
            System.out.println(s + " " + st.get(s));
    }

}
