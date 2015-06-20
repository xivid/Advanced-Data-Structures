
/*************************************************************************
 *  Compilation:  javac Stack.java
 *  Execution:    java Stack
 *
 *  A generic stack, implemented using a linked list. Each stack
 *  element is of type Item.
 *  
 *  % java Stack
 *  Pieces of Me
 *  Drop It Like It's Hot
 *  Just Lose It
 *  Vertigo
 *  
 *  17
 *  24
 *  30
 *  35
 *  39
 *  42
 *  44
 *  45
 *  45
 *
 *************************************************************************/

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Stack<Item> implements Iterable<Item> {
    private int N;          // size of the stack
    private Node first;     // top of stack

    // helper linked list class
    private class Node {
        private Item item;
        private Node next;

        Node(Item item, Node next) {
            this.item = item;
            this.next = next;
        }
    }


    // is the stack empty?
    // number of elements on the stack
    public boolean isEmpty() { return first == null; }
    public int size()        { return N;             }


    // add an element to the stack
    public void push(Item item) {
        first = new Node(item, first);
        N++;
    }

    // delete and return the most recently added element
    public Item pop() {
        if (isEmpty()) throw new RuntimeException("Stack underflow");
        Item item = first.item;        // save item to return
        first = first.next;            // delete first node
        N--;
        return item;                   // return the saved item
    }

    // return string representation - takes quadratic time for string concat
    public String toString() {
        String s = "";
        for (Node x = first; x != null; x = x.next) {
            s += x.item + ", ";
        }
        return "[ " + s + "]";
    }


    public Iterator<Item> iterator()  { return new StackIterator();  }

    // an iterator, doesn't implement remove() since it's optional
    private class StackIterator implements Iterator<Item> {
        private Node current = first;
        public boolean hasNext()  { return current != null;                     }
        public void remove()      { throw new UnsupportedOperationException();  }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next; 
            return item;
        }
    }




    // a test client
    public static void main(String[] args) {

       /***********************************************
        *  A stack of strings
        ***********************************************/
        Stack<String> s1 = new Stack<String>();
        s1.push("Vertigo");
        s1.push("Just Lose It");
        s1.push("Pieces of Me");
        System.out.println(s1.pop());
        s1.push("Drop It Like It's Hot");
        while (!s1.isEmpty()) {
            System.out.println(s1.pop());
        }
        System.out.println();


       /*********************************************************
        *  A stack of integers. Illustrates autoboxing and
        *  auto-unboxing.
        *********************************************************/
        Stack<Integer> s2 = new Stack<Integer>();
        for (int i = 0; i < 10; i++) {
            s2.push(i);
        }

        // test out the iterator
        for (int i : s2) {
            StdOut.print(i + " ");
        }
        StdOut.println();

        while (s2.size() >= 2) {
            int a = s2.pop();
            int b = s2.pop();
            int c = a + b;
            System.out.println(c);
            s2.push(a + b);
        }

    }
}

