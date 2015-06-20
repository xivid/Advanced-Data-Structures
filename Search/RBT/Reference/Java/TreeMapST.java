import java.util.TreeMap;
public class TreeMapST<Key extends Comparable<Key>, Value> 
{

    private TreeMap<Key, Value> st;

    public TreeMapST() {
        st = new TreeMap<Key, Value>();
    }

    public void put(Key key, Value val) {
        if (val == null) st.remove(key);
        else             st.put(key, val);
    }
    public Value get(Key key)             { return st.get(key);            }
    public Value delete(Key key)          { return st.remove(key);         }
    public boolean contains(Key key)    { return st.containsKey(key);    }
    public int size()                   { return st.size();              }


  public static void main(String[] args)
  {
      TreeMapST<Integer, Integer> st;
      st = new TreeMapST<Integer, Integer>();
      int[] a = { 3, 1, 4, 5, 6, 2, 8, 7, 9 };
      for (int i = 0; i < a.length; i++)
	  st.put(a[i], i);
      for (int i = 0; i < a.length; i++)
	  StdOut.println(st.get(a[i]) + " " + a[i]);
  }

}
