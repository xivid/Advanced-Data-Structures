#include <iostream>
#include <utility>
using namespace std;

template<class DATA, class PRIORITY>
class PriorityQueue{
    //This queue always pops the element with top(i.e. least in number) priority.
    typedef pair<DATA, PRIORITY> PDP;
private:
    PDP *arr;
    int length; //capacity of queue
    int n; //number of elements
    void pushdown() {
        //pushes bigger elements down
        int p = 0;
        PDP t;
        while(p*2 + 1 <= n-1) {
            if(p*2 + 1 == n-1) {
                if(arr[p*2+1].second < arr[p].second) {
                    t = arr[p]; arr[p] = arr[p*2+1]; arr[p*2+1] = t;
                }
                break;
            }
            else if(arr[p].second > arr[p*2+1].second && arr[p*2+1].second < arr[p*2+2].second) {
                t = arr[p]; arr[p] = arr[p*2+1]; arr[p*2+1] = t;
                p = p*2+1;
            }
            else if(arr[p].second > arr[p*2+2].second && arr[p*2+2].second < arr[p*2+1].second) {
                t = arr[p]; arr[p] = arr[p*2+2]; arr[p*2+2] = t;
                p = p*2+2;
            }
            else break;
        }
    }
    
    void pushup() {
        int p = n - 1;
        PDP t;
        while (p > 0) {
            if(arr[(p-1)/2].second > arr[p].second) {
                t = arr[p]; arr[p] = arr[(p-1)/2]; arr[(p-1)/2] = t;
                p = (p-1) / 2;
            }
            else break;
        }
    }
    
public:
    PriorityQueue(int size): length(size) {
        //size must be specified
        n = 0;
        arr = new PDP[size];
    }
    
    void push(DATA d, PRIORITY p){
        if(n == length) {
            cout << "Full queue!" << endl;
            return;
        }
        arr[n++] = make_pair(d, p);
        pushup();
        
        //cout << d << " with priority " << p << " has been successfully pushed into the queue." << endl;
        
        //cout << "n = " << n << endl;
        //for(int i = 0; i < n; i++) cout << "(" << arr[i].first << ", " << arr[i].second << ")" << endl;
    }
    
    DATA pop() {
        if(isempty()) return -1;
        
        DATA d = arr[0].first;
        arr[0] = arr[--n];
        pushdown();
        
        return d;
    }
    DATA peek() {
        if(isempty()) return -1;
        
        DATA d = arr[0].first;
        return d;
    }
    
    bool isempty() {
        return n == 0;
    }
};

int main(){
    int c, n, d, p;
    cout << "Priority Queue Demo" << endl;
    cout << "Input the maximum size of the priority queue:" << endl;
    cin >> n;
    PriorityQueue<int, int> Q(n);
    cout << "Type 1 to push, 2 to pop, 3 to peek, Control+D to end:" << endl;
    while(cin >> c) {
        if (c == 1) {
            cout << "Input data and its priority:" << endl;
            cin >> d >> p;
            Q.push(d, p);
        }
        else if (c == 2) {
            if(Q.isempty()) cout << "Empty queue!" << endl;
            else cout << Q.pop() << " poped." << endl;
        }
        else if (c == 3) {
            if(Q.isempty()) cout << "Empty queue!" << endl;
            else cout << "Next data to pop is " << Q.peek() << endl;
        }
        cout << "\nType 1 to push, 2 to pop, 3 to peek, Control+D to end:" << endl;
    }
    return 0;
}