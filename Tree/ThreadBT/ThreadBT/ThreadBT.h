#ifndef THREADBT_H
#define THREADBT_H
#include <iostream> //use standard IO for debugging
#include <stack> //use stack to reverse output
using namespace std;

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

#endif // THREADBT_H
