import java.util.Iterator;
public class BST<Key extends Comparable, Value> implements Iterable<Key>
{
   private Node root;              // root of BST

   private class Node
   {
      private Key key;              // sorted by key
      private Value val;            // associated data
      private Node left, right;     // left and right subtrees

      Node(Key key, Val val)
      {
            this.key = key;
            this.val = val;
      }
   }

   public boolean contains(Key key)
   {  return get(key) != null;   }

   public Value get(Key key)
   {  return get(root, key);  }

   public Value get(Node x, Key key)
   {  
      if (x == null) return null;
      int cmp = key.compareTo(x.key);
      if      (cmp < 0) return get(x.left, key);
      else if (cmp > 0) return get(x.right, key);
      else return x.val;
   }

   public void put(Key key, Value value)
   { root = insert(root, key, value);  }

   private Node put(Node x, Key key, Value value)
   {  
      if (x == null) return new Node(key, value);
      int cmp = key.compareTo(x.key);
      if      (cmp < 0) x.left  = insert(x.left,  key, value);
      else if (cmp > 0) x.right = insert(x.right, key, value);
      else x.val = value;
      return x;
   }

   public Iterator<Key> iterator()
   {  return new BSTIterator();  }

   private class BSTIterator implements Iterator<Key>
   {
      private Stack<Node> stack = new Stack<Node>();

      private void pushLeft(Node x)
      {
         while (x != null)
         {
            stack.push(x);
            x = x.left;
         }
      }
   
      BSTIterator()
      {  pushLeft(root);   }

      public boolean hasNext()
      {  return !stack.isEmpty();  }

      public void remove() { }

      public Key next()
      {
         Node x = stack.pop();
         pushLeft(x.right);
         return x.key;
      }
   }



   public static void main(String[] args)
   {
      String test = "S E A R C H E X A M P L E";
      String[] keys = test.split(" ");
      ArrayST<String, Integer> st = new ArrayST<String, Integer>(50);
      int N = keys.length;
      for (int i = 0; i < N; i++)
          st.put(keys[i], i);
      for (String s: st)
	  System.out.println(s + " " + st.get(s));
   }

}
