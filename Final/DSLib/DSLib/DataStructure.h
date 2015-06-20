//
//  DataStructure.h
//  DSLib
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef DSLib_DataStructure_h
#define DSLib_DataStructure_h
#include <utility>
#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <vector>
using namespace std;

//-------Priority Queue----------
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

//---------SkipList---------
/*template<class T>
class SkipNode{
    friend class SkipList;
private:
    int key;
    T value;
    int lev;
    SkipNode<T>* *next;
    SkipNode(int D, int level) {
        key = D;
        lev = level;
        next = new SkipNode<T>*[level+1];
    }
};*/
template<class T>
class SkipList{
private:
    class SkipNode{
        friend class SkipList;
    private:
        int key;
        T value;
        int lev;
        SkipNode* *next;
        SkipNode(int D, T val, int level) {
            key = D;
            lev = level;
            value = val;
            next = new SkipNode*[level+1];
        }
    };
    int maxlevel, levels, maxE;
    SkipNode *Min, *Max, **path;
public:
    SkipList(int n, int Large) {
        srand((unsigned)time(NULL));
        if(n > 1)
            maxlevel = ceil(log(n)/log(2)) - 1;
        else
            maxlevel = 0;
        levels = 0; //levels == 0表示跳表为空
        Min = new SkipNode(1<<31, T(), maxlevel);
        maxE = Large + 1;
        Max = new SkipNode(maxE, T(), -1);
        for(int level = maxlevel; level >= 0; level--)
            Min->next[level] = Max;
        path = new SkipNode*[maxlevel + 1];
    }
    ~SkipList() {
        delete Min;
        delete Max;
        delete [] path;
    }
    bool search(int x) {
        if(x >= maxE) return false;
        SkipNode *p = Min;
        for(int level = levels - 1; level >= 0; level--)
            while(p->next[level]->key < x)
                p = p->next[level];
        if(p->next[0]->key == x) cout << "Level = " << p->next[0]->lev << endl;
        return p->next[0]->key == x;
    }
    bool savesearch(int x) {
        if(x >= maxE) return false;
        SkipNode *p = Min;
        for (int level = levels - 1; level >= 0; level--) {
            while (p->next[level]->key < x)
                p = p->next[level];
            path[level] = p;
        }
        return p->next[0]->key == x;
    }
    SkipList<T>& insert(int x, T value) {
        if(x >= maxE)
            cout << "超过了最大值！" << endl;
        else if(savesearch(x))
            cout << "插入失败，已经存在该数据！" << endl;
        else {
            int lev = 0;
            while (rand() < (1 << 30)) ++lev;
            if (lev > maxlevel) lev = maxlevel;
            if (lev >= levels) {  //注意>=更新levels
                lev = levels++;
                path[lev] = Min;
            }
            
            SkipNode *p = new SkipNode(x, value, lev);
            for (int level = lev; level >= 0; level--) {
                p->next[level] = path[level]->next[level];
                path[level]->next[level] = p;
            }
            
            cout << "数据" << x << "成功插入第" << lev << "层。" << endl;
        }
        return *this;
    }
    
    SkipList<T>& del(int x) {
        if(x < maxE && savesearch(x))
        {
            SkipNode* p = path[0]->next[0];
            for(int level = 0; level < levels && path[level]->next[level] == p; level++)
                path[level]->next[level] = path[level]->next[level]->next[level];
            delete p;
            
            while(levels > 0 && Min->next[levels-1] == Max) --levels;
        }
        else
            cout << "删除失败，不存在此结点！" << endl;
        return *this;
    }
    void print() {
        if(levels == 0)
            cout << "跳表为空。" << endl;
        else for(int lev = levels - 1; lev >= 0; lev--) {
            cout << "Level " << lev << ":";
            SkipNode *p = Min;
            cout << "Min -> ";
            while (p->next[lev] != Max) {
                cout << p->next[lev]->key << " -> ";
                p = p->next[lev];
            }
            cout << "Max" << endl;
        }
    }
};

//------SparseMatrix------
class SparseMatrix{
private:
    int size;
    int n;
    int *row, rows;
    int *col, cols;
    int *data;
public:
    SparseMatrix(int SIZE, int m, int n): size(SIZE), rows(m), cols(n) {
        row = new int[SIZE];
        col = new int[SIZE];
        data = new int[SIZE];
        n = 0;
    }
    
    ~SparseMatrix() {
        delete [] row;
        delete [] col;
        delete [] data;
    }
    
    bool insert(int r, int c, int d) {
        if(n && (r < row[n-1] || (r == row[n-1] && c < col[n-1]))) {
            cout << "输入顺序不合法！" << endl;
            return false;
        }
        if(n == size) {
            cout << "矩阵已存满！" << endl;
            return false;
        }
        if(!d) {
            cout << "不允许插入零元素！" << endl;
            return false;
        }
        if(r >= rows || c >= cols || r < 0 || c < 0) {
            cout << "元素位置超出矩阵规模！" << endl;
            return false;
        }
        
        row[n] = r;
        col[n] = c;
        data[n++] = d;
        return true; //success
    }
    
    SparseMatrix reverse(){
        SparseMatrix t(size, cols, rows);
        t.n = n;
        int i, index, *num = new int[cols](); //初始化为0
        for(i = 0; i < n; i++) ++num[col[i]]; //记录原矩阵每一列（转置矩阵每一行）的元素个数
        
        int *cpot = new int[cols](); //指示原矩阵每一列（转置矩阵每一行）第一个元素在转置矩阵中的存储次序，随着程序的运行，依次变为第二个、第三个……
        for(i = 1; i < cols; i++) cpot[i] = cpot[i-1] + num[i-1];
        
        for(i = 0; i < n; i++) {
            index = cpot[col[i]]++;
            t.row[index] = col[i];
            t.col[index] = row[i];
            t.data[index] = data[i];
        }
        return t;
    }
    
    void printtuple() {
        for(int i = 0; i < n; i++)
            cout << "(" << row[i] << ", " << col[i] << ", " << data[i] << ")" << endl;
    }
    
    void printmatrix() {
        int cur = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                if(row[cur] == i && col[cur] == j) cout << data[cur++] << "\t";
                else cout << "0\t";
            cout << endl;
        }
    }
};

//-------Dynamic Huffman Coding Tree-------
class HuffmanNode
{
    friend class HuffmanTree;
public:
    HuffmanNode(): lc(0), rc(0), fa(0), weight(0), data(0) {}
    ~HuffmanNode() {}
    
private:
    int lc, rc, fa;
    int weight, data; //data == -1: not leaf or not yet transmitted(NYT)
};

class HuffmanTree
{
private:
    int *table; //data -> index of node
    HuffmanNode *nodes;
    int nyt; //the index of NYT node in nodes[], starting at 1(root). so 0 means not exist
    const int root = 1;
public:
    HuffmanTree()
    {
        table = new int[256](); //initial value 0(not exist)
        nodes = new HuffmanNode[3*256];
        nyt = root;
        nodes[1].data = -1;
    }
    ~HuffmanTree()
    {
        delete [] table;
        delete [] nodes;
    }
    
    string getCode(int p)
    {
        string s;
        while (p != root)
        {
            if (p == nodes[nodes[p].fa].lc)
                s = '0' + s;
            else
                s = '1' + s;
            p = nodes[p].fa;
        }
        return s;
    }
    
    void printnodes() //for demo
    {
        cout << "id\tdata\tweight\tlc\trc\tfa\n";
        for (int i = root; i <= nyt; i++) {
            cout << i << '\t' << nodes[i].data << '\t'
            << nodes[i].weight << '\t' << nodes[i].lc
            << '\t' << nodes[i].rc << '\t' <<nodes[i].fa << endl;
        }
    }
    
    void exchange(int &cur, int i)
    {
        if (nodes[cur].fa == i) return; //交换的两棵子树不能为父子关系
        int t;
        t = nodes[cur].data; nodes[cur].data = nodes[i].data; nodes[i].data = t;
        t = nodes[cur].lc; nodes[cur].lc = nodes[i].lc; nodes[i].lc = t;
        t = nodes[cur].rc; nodes[cur].rc = nodes[i].rc; nodes[i].rc = t;
        nodes[nodes[cur].lc].fa = cur;
        nodes[nodes[cur].rc].fa = cur;
        nodes[nodes[i].lc].fa = i;
        nodes[nodes[i].rc].fa = i;
        
        if (nodes[cur].data >= 0)
            table[nodes[cur].data] = cur;
        if (nodes[i].data >= 0)
            table[nodes[i].data] = i;
        
        cur = i;
    }
    
    string toBinary(unsigned char c) {
        string s;
        //cout << c << ": " << (unsigned)c << "->";
        for (int i = 0; i < 8; ++i, c/=2)
            s = (char)('0' + c%2) + s;
        //cout << s << endl;
        return s;
    }
    
    string toByteCode(string& src) {
        string s;
        const unsigned char power[] = {1, 2, 4, 8, 16, 32, 64, 128};
        int i = 0;
        //src += CodeOfNYT + AnyExistingChar (构造出不合法的情况，在解码时作为end-of-input的标志)
        src += getCode(nyt);
        for (int i = 0; i < 256; i++) if(table[i]) {
            src += toBinary(i);
            break;
        }
        
        while (src[i]) {
            unsigned char c = 0;
            for (int j = 7; j >= 0 && src[i]; i++, j--)
                c += (src[i] == '1') * power[j];
            s += c;
        }
        
        return s;
    }
    
    unsigned char ByteToChar(const string& s) {
        unsigned char c = 0;
        const unsigned char power[] = {1, 2, 4, 8, 16, 32, 64, 128};
        for (int i = 0; i < 8; i++)
            c += power[7-i] * (s[i] == '1');
        return c;
    }
    
    string insert(int data)
    {
        string ret;
        int cur = table[data];
        if (cur)
        {
            ret += getCode(cur);
            for (int i = root; i < cur; i++)
                if (nodes[i].weight == nodes[cur].weight)
                {
                    exchange(cur, i); //cur will be changed
                    break;
                }
            nodes[cur].weight++;
        }
        else
        {
            ret += getCode(nyt);
            ret += toBinary(data);
            
            //new symbol
            nodes[nyt+1].data = data;
            nodes[nyt+1].weight = 1;
            nodes[nyt+1].fa = nyt;
            nodes[nyt].rc = nyt+1;
            nodes[nyt].weight = 1;
            table[data] = nyt + 1;
            
            //new nyt
            nodes[nyt+2].data = -1;
            nodes[nyt+2].fa = nyt;
            nodes[nyt].lc = nyt+2;
            
            cur = nyt;
            nyt += 2;
        }
        
        while (cur != root)
        {
            cur = nodes[cur].fa;
            for (int i = root; i < cur; i++)
                if (nodes[i].weight == nodes[cur].weight)
                {
                    exchange(cur, i); //cur will be changed
                    break;
                }
            nodes[cur].weight++;
        }
        return ret;
    }
    
    static string encode(const char* s, size_t length)
    {
        HuffmanTree tree;
        string ret; //用于存储字符形式的二进制串
        for (int i = 0; i < length; i++)
        {
            ret += tree.insert(int((unsigned char)*s++));
        }
        return tree.toByteCode(ret); //返回真正的二进制串
    }
    
    static string decode(const char* s, size_t length)
    {
        HuffmanTree tree;
        string ret, tmp;
        int spos = 0, p = tree.root;
        unsigned char chr;
        
        for(int i = 0; i < length; i++) //字符串s内部可能会出现字符'\0'，但不能视为结束，该多长就要读多长
            tmp += tree.toBinary(*s++);
        while(tmp[spos]) {
            if (p == tree.nyt) {
                chr = tree.ByteToChar(tmp.substr(spos, spos+8));
                spos += 8;
                if (tree.table[chr]) break; //end-of-input sign
                ret += chr;
                tree.insert(chr);
                p = tree.root;
            }
            else if (!tree.nodes[p].lc && !tree.nodes[p].rc) {
                ret += tree.nodes[p].data;
                tree.insert(tree.nodes[p].data);
                p = tree.root;
            }
            else if (tmp[spos++] == '0')
                p = tree.nodes[p].lc;
            else
                p = tree.nodes[p].rc;
        }
        
        return ret;
    }
};

//------Thread BT-------
//pre-definition
template<class T> class PreThreadBT;
template<class T> class PostThreadBT;

template<class T>
class BTNode
{
    friend class PreThreadBT<T>;
    friend class PostThreadBT<T>;
public:
    bool ltag, rtag; //false: is thread
    T data;
    BTNode *lc, *rc;
    
    BTNode();
    BTNode(T DATA);
    ~BTNode();
};

template<class T>
class PreThreadBT
{
private:
    BTNode<T>* nulptr;
    BTNode<T>* root;
public:
    PreThreadBT();
    ~PreThreadBT();
    void initialize(BTNode<T>* p);
    void insertRight(BTNode<T>* father, BTNode<T>* p);
    void insertLeft(BTNode<T>* father, BTNode<T>* p);
    void PreOrderTraversal();
};

template<class T>
class PostThreadBT
{
    /* BTNode中没有双亲信息，只能用空闲右指针存储后序后继，这样无法确定右子树非空的结点的后序后继，也就无法直接用后序线索二叉树生成后序遍历序列。
     * 这里采用折中的方法，即利用后序前驱，生成倒置的后序遍历序列，再将序列颠倒输出，即为后序遍历序列。
     */
private:
    BTNode<T>* nulptr;
    BTNode<T>* root;
public:
    PostThreadBT();
    ~PostThreadBT();
    void initialize(BTNode<T>* p);
    void insertRight(BTNode<T>* father, BTNode<T>* p);
    void insertLeft(BTNode<T>* father, BTNode<T>* p);
    void PostOrderTraversal();
};


template<class T>
BTNode<T>::BTNode()
{
    ltag = rtag = false;
    lc = rc = NULL;
}

template<class T>
BTNode<T>::BTNode(T DATA) :
data(DATA)
{
    ltag = rtag = false;
    lc = rc = NULL;
}

template<class T> BTNode<T>::~BTNode() {}

template<class T>
PreThreadBT<T>::PreThreadBT()
{
    root = NULL;
    nulptr = new BTNode<T>;
    nulptr->ltag = nulptr->rtag = true;
}

template<class T> PreThreadBT<T>::~PreThreadBT() {}

template<class T>
void PreThreadBT<T>::initialize(BTNode<T> *p)
{
    root = p;
    root->lc = root->rc = nulptr;
}

template<class T>
void PreThreadBT<T>::insertLeft(BTNode<T> *father, BTNode<T> *p)
{
    if (father->ltag)
    {
        p->ltag = true;
        p->lc = father->lc;
        
        //assign successor
        p->rc = father->lc;
        
        //modify successor
        if (!father->lc->ltag)
            father->lc->lc = p;
    }
    else
    {
        father->ltag = true;
        
        //assign successor
        p->rc = father->rc;
        
        //modify successor
        if (!father->rc->ltag)
            father->rc->lc = p;
        
        //assign precursor
        p->lc = father;
    }
    
    //modify precursor
    if (!father->rtag)
        father->rc = p;
    
    //modify father
    father->lc = p;
}

template<class T>
void PreThreadBT<T>::insertRight(BTNode<T> *father, BTNode<T> *p)
{
    BTNode<T> *q;
    if (father->rtag)
    {
        p->rtag = true;
        p->rc = father->rc;
        
        //precursor
        if (father->ltag)
        {
            q = father->lc;
            while (q->rtag || q->ltag) //find the last node in father->lc
                if (q->rtag)
                    q = q->rc;
                else
                    q = q->lc;
            q->rc = p;
            p->lc = q;
        }
        else
            p->lc = father;
        
        //successor
        if (!father->rc->ltag)
            father->rc->lc = p;
    }
    else
    {
        father->rtag = true;
        
        //successor && precursor
        if (father->ltag)
        {
            q = father->lc;
            while (q->rtag || q->ltag)
                if (q->rtag)
                    q = q->rc;
                else
                    q = q->lc;
            p->rc = q->rc;
            if (!q->rc->ltag)
                q->rc->lc = p;
            q->rc = p;
            p->lc = q;
        }
        else
        {
            p->rc = father->rc;
            if (!father->rc->ltag)
                father->rc->lc = p;
            p->lc = father;
        }
    }
    father->rc = p;
}

template<class T>
void PreThreadBT<T>::PreOrderTraversal()
{
    BTNode<T> *p = root;
    while (p != nulptr)
    {
        cout << p->data << endl;
        if (p->ltag)
            p = p->lc;
        else
            p = p->rc;
    }
}

template<class T>
PostThreadBT<T>::PostThreadBT()
{
    root = NULL;
    nulptr = new BTNode<T>;
    nulptr->ltag = nulptr->rtag = true;
}

template<class T> PostThreadBT<T>::~PostThreadBT() {}

template<class T>
void PostThreadBT<T>::initialize(BTNode<T> *p)
{
    root = p;
    root->lc = root->rc = nulptr;
}

template<class T>
void PostThreadBT<T>::insertLeft(BTNode<T> *father, BTNode<T> *p)
{
    BTNode<T> *q;
    if (father->ltag)
    {
        p->ltag = true;
        p->lc = father->lc;
        
        //precursor
        if (!father->lc->rtag)
            father->lc->rc = p;
        
        //successor
        if (!father->rtag)
            p->rc = father;
        else
        {
            q = father->rc;
            while (q->ltag || q->rtag)
                if (q->ltag)
                    q = q->lc;
                else
                    q = q->rc;
            q->lc = p;
            p->rc = q;
        }
    }
    else
    {
        father->ltag = true;
        //precursor && successor
        if (father->rtag)
        {
            q = father->rc;
            while (q->rtag || q->ltag)
                if (q->ltag)
                    q = q->lc;
                else
                    q = q->rc;
            p->lc = q->lc;
            if (!q->lc->rtag)
                q->lc->rc = p;
            q->lc = p;
            p->rc = q;
        }
        else
        {
            //successor
            p->rc = father;
            
            //precursor
            p->lc = father->lc;
            if (!father->lc->rtag)
                father->lc->rc = p;
        }
    }
    father->lc = p;
}

template<class T>
void PostThreadBT<T>::insertRight(BTNode<T> *father, BTNode<T> *p)
{
    if (father->rtag)
    {
        p->rtag = true;
        p->rc = father->rc;
        
        //precursor
        p->lc = father->rc;
        if (!father->rc->rtag)
            father->rc->rc = p;
    }
    else
    {
        father->rtag = true;
        
        //precursor
        p->lc = father->lc;
        if (!father->lc->rtag)
            father->lc->rc = p;
        
        //successor
        p->rc = father;
    }
    
    //successor
    if (!father->ltag)
        father->lc = p;
    
    father->rc = p;
}

template<class T>
void PostThreadBT<T>::PostOrderTraversal()
{
    stack<T> s;
    BTNode<T>* p = root;
    while (p != nulptr)
    {
        s.push(p->data);
        if (p->rtag)
            p = p->rc;
        else
            p = p->lc;
    }
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
}

//------Forest, Binary Tree and Multi Tree-------
template<class T> class TreeNode;
template<class T> class BinTree;
template<class T> class Tree;
template<class T> class Forest;

template<class T>
class BinNode
{
    friend class BinTree<T>;
    friend class Tree<T>;
    friend class Forest<T>;
    BinNode<T> *lc, *rc;
    T data;
    
public:
    BinNode();
    BinNode(T d);
    ~BinNode();
};

template<class T> BinNode<T>::BinNode() {lc = rc = NULL; data = T();}
template<class T> BinNode<T>::BinNode(T d) {lc = rc = NULL; data = d;}
template<class T> BinNode<T>::~BinNode() {lc = rc = NULL; data = T();}

template<class T>
class BinTree
{
    friend class Tree<T>;
    friend class Forest<T>;
    BinNode<T> *root;
    int nodeNum;
    void print(BinNode<T>* p, int level);
public:
    BinTree();
    BinTree(int n);
    ~BinTree();
    Forest<T>* toForest();
    void addtoTree(BinNode<T>* r, TreeNode<T>* node, Tree<T>* tree);
    void Print();
};

template<class T> BinTree<T>::BinTree() {root = NULL; nodeNum = 0;}
template<class T> BinTree<T>::BinTree(int n) : nodeNum(n)
{
    T d;
    vector<BinNode<T>*> nodes;
    cout << "Node #1 will be regarded as root." << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << "Input the data of node #" << i << ":" << endl;
        cin >> d;
        nodes.push_back(new BinNode<T>(d));
    }
    int lc, rc;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the numbers of left child and right child of node #" << i << "(0 for NULL):" << endl;
        cin >> lc >> rc;
        if (lc)
            nodes[i-1]->lc = nodes[lc-1];
        if (rc)
            nodes[i-1]->rc = nodes[rc-1];
    }
    root = nodes[0];
}
template<class T> BinTree<T>::~BinTree() {root = NULL; nodeNum = 0;}
template<class T> void BinTree<T>::addtoTree(BinNode<T>* r, TreeNode<T>* node, Tree<T>* tree)
{
    if (r->lc)
    {
        TreeNode<T>* tnode = new TreeNode<T>(r->lc->data);
        node->children.push_back(tree->nodeNum++);
        tree->nodes.push_back(tnode);
        addtoTree(r->lc, tnode, tree);
        BinNode<T>* p = r->lc->rc;
        while (p)
        {
            TreeNode<T>* cnode = new TreeNode<T>(p->data);
            node->children.push_back(tree->nodeNum++);
            tree->nodes.push_back(cnode);
            addtoTree(p, cnode, tree);
            p = p->rc;
        }
    }
}
template<class T> Forest<T>* BinTree<T>::toForest()
{
    Forest<T> *forest = new Forest<T>;
    forest->treeNum = 0;
    BinNode<T> *p = root;
    while (p != NULL)
    {
        Tree<T> *tree = new Tree<T>;
        TreeNode<T> *node = new TreeNode<T>(p->data);
        tree->nodes.push_back(node);
        ++tree->nodeNum;
        addtoTree(p, node, tree);
        tree->root = tree->nodes[0];
        
        forest->trees.push_back(tree);
        ++forest->treeNum;
        p = p->rc;
    }
    return forest;
}
template<class T> void BinTree<T>::print(BinNode<T>* p, int level)
{
    if (p)
    {
        print(p->rc, level+1);
        for (int i = 0; i < level; i++)
            putchar('\t');
        cout << p->data << endl;
        print(p->lc, level+1);
    }
}
template<class T> void BinTree<T>::Print()
{
    print(root, 0);
}

template<class T>
class TreeNode
{
    friend class BinTree<T>;
    friend class Tree<T>;
    vector<int> children;
    T data;
    
public:
    TreeNode();
    TreeNode(T d);
    ~TreeNode();
    void addChild(TreeNode<T>* child);
    TreeNode<T>* getChild(int pos);
};

template<class T> TreeNode<T>::TreeNode() {data = T();}
template<class T> TreeNode<T>::TreeNode(T d) {data = d;}
template<class T> TreeNode<T>::~TreeNode() {children.clear(); data = T(); }

template<class T>
class Tree
{
    friend class BinTree<T>;
    vector<TreeNode<T>*> nodes;
    TreeNode<T> *root;
    int nodeNum;
public:
    Tree();
    Tree(int n);
    ~Tree();
    void Delete(TreeNode<T> *p);
    BinTree<T>* toBinTree();
    void print(TreeNode<T>* p, int level);
    void Print();
};

template<class T> Tree<T>::Tree() {root = NULL; nodeNum = 0;}
template<class T> Tree<T>::Tree(int n) : nodeNum(n)
{
    T data;
    int no;
    cout << "Node #1 is regarded as root." << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the data of node #" << i << ":" << endl;
        cin >> data;
        nodes.push_back(new TreeNode<T>(data));
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the numbers of the children of node #" << i << "(end with 0):" << endl;
        cin >> no;
        while (no)
        {
            if (no > 0 && no <= n)
                nodes[i-1]->children.push_back(no-1);
            else
                cout << "Invalid number! Try again." << endl;
            cin >> no;
        }
    }
    root = nodes[0];
}
template<class T> Tree<T>::~Tree()
{
    Delete(root);
    nodes.clear();
    nodeNum = 0;
}
template<class T> void Tree<T>::Delete(TreeNode<T>* p)
{
    for (int i = 0; i < p->children.size(); ++i)
        Delete(nodes[p->children[i]]);
    delete p;
}
template<class T> void Tree<T>::print(TreeNode<T>* p, int level)
{
    int size = (int)p->children.size();
    for (int i = size - 1; i >= size/2; --i)
        print(nodes[p->children[i]], level+1);
    for (int j = 0; j < level; j++)
        putchar('\t');
    cout << p->data << endl;
    for (int i = size/2 - 1; i >= 0; --i)
        print(nodes[p->children[i]], level+1);
}
template<class T> void Tree<T>::Print()
{
    print(root, 0);
}
template<class T> BinTree<T>* Tree<T>::toBinTree()
{
    BinTree<T>* bt = new BinTree<T>;
    vector<BinNode<T>*> btnodes;
    bt->nodeNum = nodeNum;
    for (int i = 0; i < nodeNum; ++i)
        btnodes.push_back(new BinNode<T>(nodes[i]->data));
    bt->root = btnodes[0];
    for (int i = 0; i < nodeNum; ++i)
    {
        int childNum = (int)nodes[i]->children.size();
        if (childNum)
        {
            btnodes[i]->lc = btnodes[nodes[i]->children[0]];
            BinNode<T> *p = btnodes[i]->lc;
            for (int j = 1; j < childNum; ++j)
            {
                p->rc = btnodes[nodes[i]->children[j]];
                p = p->rc;
            }
        }
    }
    return bt;
}

template<class T>
class Forest
{
    friend class BinTree<T>;
    vector<Tree<T>*> trees;
    int treeNum;
public:
    Forest();
    Forest(int n);
    ~Forest();
    BinTree<T>* toBinTree();
    void Print();
};
template<class T> Forest<T>::Forest() {treeNum = 0;}
template<class T> Forest<T>::Forest(int n) : treeNum(n)
{
    int num;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Input the number of nodes in tree #" << i << ":" << endl;
        cin >> num;
        while (num < 1)
        {
            cout << "Illegal number! Try again." << endl;
            cin >> num;
        }
        trees.push_back(new Tree<T>(num)); //index starting from 0
    }
}
template<class T> Forest<T>::~Forest() {}
template<class T> BinTree<T>* Forest<T>::toBinTree()
{
    BinTree<T>* tree = trees[0]->toBinTree();
    BinNode<T>* p = tree->root;
    for (int i = 1; i < treeNum; ++i)
    {
        p->rc = trees[i]->toBinTree()->root;
        p = p->rc;
    }
    return tree;
}
template<class T> void Forest<T>::Print()
{
    for (int i = 0; i < treeNum; ++i)
    {
        cout << "Tree #" << i+1 << ":" << endl;
        trees[i]->Print();
        cout << endl;
    }
}
//-------AVL Tree--------
template<typename T, typename V> class AVLTree;
template<typename T, typename V> class AVLNode {
    friend class AVLTree<T, V>;
    AVLNode<T, V> *lc, *rc, *fa;
    T key;
    int value, bf; //times of occurrence, balance factor
    AVLNode() {lc = rc = fa = NULL; value = 1; bf = 0;}
    AVLNode(T d, V v): key(d) {lc = rc = fa = NULL; value = v; bf = 0;}
};
template<typename T, typename V> class AVLTree {
    AVLNode<T, V>* root;
    AVLNode<T, V>* get(T data) {
        //show the information of the corresponding node
        AVLNode<T, V> *p = root;
        while (p) {
            if (p->key > data)
                p = p->lc;
            else if (p->key < data)
                p = p->rc;
            else
                return p;
        }
        return NULL;
    }
    void rotate_left(AVLNode<T, V>* &p) {
        //need to change the value of p and balance factor of *p
        AVLNode<T, V>* n = p->rc; //new root
        n->fa = p->fa; //or null
        if (p == root) {
            root = n;
        } else {
            if (p == p->fa->lc)
                p->fa->lc = n;
            else
                p->fa->rc = n;
        }
        p->fa = n;
        p->rc = n->lc;
        if (n->lc)
            n->lc->fa = p;
        n->lc = p;
        if (p->bf == n->bf) {
            p->bf += 1 - n->bf;
            n->bf += 2;
        }
        else {
            p->bf += 1 + (n->bf < 0);
            ++n->bf;
        }
        p = n;
    }
    void rotate_right(AVLNode<T, V>* &p) {
        AVLNode<T, V>* n = p->lc; //new root
        n->fa = p->fa;
        if (p == root)
            root = n;
        else {
            if (p == p->fa->lc)
                p->fa->lc = n;
            else
                p->fa->rc = n;
        }
        p->fa = n;
        p->lc = n->rc;
        if (n->rc)
            n->rc->fa = p;
        n->rc = p;
        if (p->bf == n->bf) {
            p->bf -= 1 + n->bf;
            n->bf -= 2;
        }
        else {
            p->bf -= 1 + (n->bf > 0);
            --n->bf;
        }
        p = n;
    }
    void InOrderPrint(AVLNode<T, V>* p, int level) {
        if (p) {
            InOrderPrint(p->rc, level + 1);
            for (int i = 0; i < level; ++i)
                std::cout << '\t';
            std::cout << p->key << ',' << p->value << '[' << p->bf << ']' << std::endl;
            InOrderPrint(p->lc, level + 1);
        }
    }
public:
    AVLTree() {root = NULL;}
    bool hasKey(T key) {
        return (get(key) != NULL);
    }
    AVLNode<T, V>* search(T key) {
        //show the information of the corresponding node
        AVLNode<T, V> *p = root;
        int level = 0;
        while (p) {
            if (p->key > key)
                p = p->lc, ++level;
            else if (p->key < key)
                p = p->rc, ++level;
            else {
                std::cout << "key: " << p->key << ", value: " << p->value << ", level: " << level << std::endl;
                return p;
            }
        }
        return NULL;
    }
    void update(T key, V value) {
        AVLNode<T, V> *p = get(key);
        if (p) {
            p->value = value;
        }
        else
            std::cout << "Update failed: no such node." << std::endl;
    }
    void insert(T key, V value) {
        if (root == NULL) {
            root = new AVLNode<T, V>(key, value);
        }
        else {
            AVLNode<T, V> *p = root, *n;
            while (p) {
                if (key < p->key) {
                    if (p->lc)
                        p = p->lc;
                    else {
                        n = p->lc = new AVLNode<T, V>(key, value);
                        p->lc->fa = p;
                        break;
                    }
                }
                else if (key > p->key) {
                    if (p->rc)
                        p = p->rc;
                    else {
                        n = p->rc = new AVLNode<T, V>(key, value);
                        p->rc->fa = p;
                        break;
                    }
                }
                else {
                    p->value = value;
                    return;
                }
            }
            ///re-balance if:
            ///1) n is the subtree of p, and the height of n increases by 1
            ///2) n is a new child of p (can also seen as circumstance 1)
            ///after rotation, n becomes the root and the height of the whole part remains unchanged
            do {
                if (n == p->lc) {
                    //Left Rotation
                    if (p->bf == 1) {
                        p->bf = 2;
                        if (n->bf == -1) //为防止过右,若n已右倾,则先将n左旋
                            rotate_left(n);
                        rotate_right(p);
                        break;
                    }
                    else if (p->bf == -1) {
                        p->bf = 0;
                        break;
                    }
                    p->bf = 1;
                }
                else { //n == p->rc
                    if (p->bf == -1) {
                        p->bf = -2;
                        if (n->bf == 1)
                            rotate_right(n);
                        rotate_left(p);
                        break;
                    }
                    else if (p->bf == 1) {
                        p->bf = 0;
                        break;
                    }
                    p->bf = -1;
                }
                n = p;
                p = p->fa;
            } while(p);
        }
    }
    void pop(T key) { //delete by 1 time
        AVLNode<T, V> *x = get(key), *n, *p, *z;
        if (x) {
            if (x->value > 1)
                --x->value;
            else {
                if (x == root && !(x->lc || x->rc)) {//x is root and x is a leaf
                    root = NULL;
                    delete x;
                } else { //z := the node to be deleted
                    if (!(x->lc || x->rc)) { //x is a leaf
                        z = n = x;
                        p = x->fa;
                    }
                    else {
                        if ((x->lc == NULL) ^ (x->rc == NULL)) //x has only one subtree(which must be a leaf)
                            z = x->lc ? x->lc : x->rc; //z := subtree(x)
                        else {
                            z = x->lc;
                            while (z->rc)
                                z = z->rc; //in-order predecessor
                        }
                        x->key = z->key;
                        x->value = z->value;
                        n = z;
                        p = z->fa;
                    }
                    //n is the subtree of p whose height decreases by 1
                    int B;
                    AVLNode<T, V> *S;
                    do { //re-balance
                        if (n == p->lc) {
                            if (p->bf == -1) {
                                p->bf = -2;
                                S = p->rc; //sibling, in case it changes in rotation
                                B = S->bf; //in case it changes
                                if (B == 1)
                                    rotate_right(S);
                                rotate_left(p);
                                if (B == 0)
                                    break;
                            }
                            else if (p->bf == 0) {
                                p->bf = -1;
                                break;
                            }
                            p->bf = 0;
                        } else { //n == p->rc
                            if (p->bf == 1) {
                                p->bf = 2;
                                S = p->lc;
                                B = S->bf;
                                if (B == -1)
                                    rotate_left(S);
                                rotate_right(p);
                                if (B == 0)
                                    break;
                            }
                            else if (p->bf == 0) {
                                p->bf = 1;
                                break;
                            }
                            p->bf = 0;
                        }
                        n = p;
                        p = p->fa;
                    } while (p);
                    //delete z
                    p = z->fa;
                    n = z->lc ? z->lc : (z->rc ? z->rc : NULL);
                    if (n)
                        n->fa = p;
                    if (z == p->lc)
                        p->lc = n; //or null
                    else
                        p->rc = n;
                    delete z;
                }
            }
        }
        else
            std::cout << "Deletion failed: no such node." << std::endl;
    }
    void print() {
        std::cout << "The AVL Tree is: " << std::endl;
        if (root)
            InOrderPrint(root, 0);
        else
            std::cout << "Empty!" << std::endl;
    }
    
};
//-------Red Black Tree-------
template<class Key, class Value>
class RBTree {
private:
    static const bool RED = true, BLACK = false;
    
    class RBNode {
        friend class RBTree;
        
        RBNode *lc, *rc;
        Key key;
        Value value;
        bool color;
        
        RBNode() { }
        
        RBNode(Key k, Value v, bool c) : key(k), value(v), color(c) { lc = rc = NULL; }
    };
    
    RBNode *root;
    int BlackHeight;
    
    //Helper methods
    bool isRed(RBNode *const r) {
        return r == NULL ? false : r->color == RED;
    }
    
    void colorFlip(RBNode *r) {
        r->color = !r->color;
        r->lc->color = !r->lc->color; //nulptr?
        r->rc->color = !r->rc->color;
    }
    
    void leftRotate(RBNode *&r) {
        RBNode *h = r->rc;
        h->color = r->color;
        r->color = RED;
        r->rc = h->lc;
        h->lc = r;
        r = h;
    }
    
    void rightRotate(RBNode *&r) {
        RBNode *h = r->lc;
        h->color = r->color;
        r->color = RED;
        r->lc = h->rc;
        h->rc = r;
        r = h;
    }
    
    void moveRedLeft(RBNode* &r) {
        colorFlip(r);
        if (isRed(r->rc->lc)) {
            rightRotate(r->rc);
            leftRotate(r);
            colorFlip(r);
        }
    }
    
    void moveRedRight(RBNode* &r) {
        colorFlip(r);
        if (isRed(r->lc->lc)) {
            rightRotate(r);
            colorFlip(r);
        }
    }
    
    void fixUp(RBNode* &r) {
        if (isRed(r->rc))
            leftRotate(r);
        if (isRed(r->lc) && isRed(r->lc->lc))
            rightRotate(r);
        if (isRed(r->lc) && isRed(r->rc))
            colorFlip(r);
    }
    RBNode* getMin(RBNode* r) {
        while (r->lc)
            r = r->lc;
        return r;
    }
    
    void popMin(RBNode* &r) {
        if (r->lc == NULL) {
            r = NULL;
            return;
        }
        if (!isRed(r->lc) && !isRed(r->lc->lc))
            moveRedLeft(r);
        popMin(r->lc);
        fixUp(r);
    }
    
    //Operation methods
    void insert(RBNode *&r, Key key, Value val) {
        if (r == NULL)
            r = new RBNode(key, val, RED);
        
        if (isRed(r->lc) && isRed(r->rc))
            colorFlip(r);
        
        if (key == r->key)
            r->value = val;
        else if (key < r->key)
            insert(r->lc, key, val);
        else
            insert(r->rc, key, val);
        
        if (isRed(r->rc))
            leftRotate(r);
        
        if (isRed(r->lc) && isRed(r->lc->lc))
            rightRotate(r);
    }
    
    void pop(RBNode* &r, Key key) {
        if (key < r->key) {
            //if (!r->lc)
            //throw false;
            if (!isRed(r->lc) && !isRed(r->lc->lc))
                moveRedLeft(r);
            pop(r->lc, key);
        }
        else {
            if (isRed(r->lc))
                rightRotate(r);
            if (key == r->key && r->rc == NULL) {
                delete r;
                r = NULL;
                return;
            }
            //if (key > r->key && r->rc == NULL)
            //throw false;
            if (!isRed(r->rc) && !isRed(r->rc->lc))
                moveRedRight(r);
            if (key == r->key) {
                RBNode* min = getMin(r->rc);
                r->value = min->value;
                r->key = min->key;
                popMin(r->rc);
            } else
                pop(r->rc, key);
        }
        fixUp(r);
    }
    
    //For demo
    void InOrderPrint(RBNode *p, int level) {
        if (p) {
            InOrderPrint(p->rc, level + 1);
            for (int i = 0; i < level; ++i)
                cout << '\t';
            cout << p->key << '[' << p->value << ']' << (isRed(p) ? "*" : "") << endl;
            InOrderPrint(p->lc, level + 1);
        }
    }
    
public:
    RBTree() {
        root = NULL;
        BlackHeight = 0;
    }
    
    Value &get(Key key) {
        RBNode *p = root;
        //int level = 0; //for demo
        while (p) {
            if (p->key == key) {
                //cout << "Found at level " << level << endl;
                return p->value;
            }
            p = p->key < key ? p->rc : p->lc;
        }
        throw false;
    }
    
    void insert(Key key, Value val) {
        insert(root, key, val);
        if (root->color == RED) {
            root->color = BLACK; //the 2-3-4 tree grows higher up one level
            ++BlackHeight;
        }
    }
    
    void pop(Key key) {
        pop(root, key);
        if (root)
            root->color = BLACK;
    }
    
    bool contains(Key key) {
        try {
            get(key);
        } catch(bool) {
            return false;
        }
        return true;
    }
    
    void print() {
        cout << "The Red Black Tree is: " << endl;
        if (root)
            InOrderPrint(root, 0);
        else
            cout << "Empty!" << endl;
    }
};
//-------ListHash-------
template <class T> class ListStrHashTable{
    int B, factor;
    
    struct node{
        int no; //order in the list
        string* s;
        T value;
        node* next;
        node() : no(0), s(NULL), next(NULL) {}
        node(int NO, string* str, T val) : no(NO), s(str), next(NULL), value(val) {}
    };
    typedef node* hashlist;
    hashlist* ht2 = new hashlist[B];
    
    bool isPrime(int x) {
        if (x == 2)
            return true;
        if (x < 2)
            return false;
        for (int i = 2; i < x; ++i)
            if (x % i == 0)
                return false;
        return true;
    }
    
    unsigned int Hash(const char* s){ //BKDRhash
        unsigned int h = 0;
        while(*s)
            h = h * 31 + *s++;
        return (h & 0x7fffffff) % factor; //factor is the largest prime number smaller than 1280
    }
public:
    int crashcount;
    
    ListStrHashTable() { }
    
    ListStrHashTable(int b): B(b) {
        crashcount = 0;
        factor = b;
        while(!isPrime(factor))
            factor--;
    }
    
    void clearcrash() { crashcount = 0; }
    
    void insert(string &str, T val){
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        if(p == NULL) ht2[pos] = new node(0, &str, val);
        else { //insert into the list
            ++crashcount;
            while(p->next != NULL) {
                p = p->next;
                ++crashcount;
            }
            p->next = new node(p->no + 1, &str, val);
        }
        
    }
    
    T get(string& str) {
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        while(p != NULL && p->s != &str) {
            p = p->next;
            ++crashcount;
        }
        if(p == NULL)
            throw false; //not found exception
        return p->value;
    }
    
    bool hasKey(string& str) {
        int pos = Hash(str.c_str());
        node* p = ht2[pos];
        while(p != NULL && p->s != &str) p = p->next;
        if(p == NULL) return false; //not exist
        return true;
    }
};
//------OpenHash-------
template <class T> class OpenStrHashTable{
    int B, factor;
    string** ht = new string*[B];
    T* value = new T[B];
    bool isPrime(int x) {
        if (x == 2)
            return true;
        if (x < 2)
            return false;
        for (int i = 2; i < x; ++i)
            if (x % i == 0)
                return false;
        return true;
    }
    
    unsigned int Hash(const char* s){ //BKDRhash
        unsigned int h = 0;
        while(*s)
            h = h * 31 + *s++;
        return (h & 0x7fffffff) % factor; //factor is the largest prime number smaller than 1280
    }
public:
    int crashcount;
    
    OpenStrHashTable() { }
    
    OpenStrHashTable(int b): B(b) {
        crashcount = 0;
        factor = b;
        while(!isPrime(factor))
            factor--;
    }
    
    void clearcrash() { crashcount = 0; }
    
    void insert(string& str, T val){
        int pos = Hash(str.c_str());
        while(ht[pos] != NULL)
        {
            pos = (pos + 1) % B;
            ++crashcount;
        }
        ht[pos] = &str;
        value[pos] = val;
    }
    
    bool hasKey(string& str) {
        int pos = Hash(str.c_str()), p0 = pos;
        while(ht[pos] != &str) {
            pos = (pos + 1) % B;
            if(pos == p0) return false; //returned to original position, fail
        }
        return true;
    }
    
    T get(string& str) {
        int pos = Hash(str.c_str()), p0 = pos;
        while(ht[pos] != &str) {
            ++crashcount;
            pos = (pos + 1) % B;
            if(pos == p0)
                throw false; //throw an not-exist exception
        }
        return value[pos];
    }
};
//------Dictionary------
template<class Key, class Value> class Dict {
    RBTree<Key, Value> tree;
public:
    Value& operator [](Key key) {
        try {
            return tree.get(key);
        } catch(bool) {
            tree.insert(key, *(new Value));
            return tree.get(key);
        }
    }
    void pop(Key key) { tree.pop(key); }
};


#endif
