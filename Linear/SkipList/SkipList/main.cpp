#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
class SkipNode{
    friend class SkipList;
private:
    int data;
    int lev;
    SkipNode* *next;
    SkipNode(int D, int level) {
        data = D;
        lev = level;
        next = new SkipNode*[level+1];
    }
};
class SkipList{
private:
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
        Min = new SkipNode(1<<31, maxlevel);
        maxE = Large + 1;
        Max = new SkipNode(maxE, -1);
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
            while(p->next[level]->data < x)
                p = p->next[level];
        if(p->next[0]->data == x) cout << "Level = " << p->next[0]->lev << endl;
        return p->next[0]->data == x;
    }
    bool savesearch(int x) {
        if(x >= maxE) return false;
        SkipNode *p = Min;
        for (int level = levels - 1; level >= 0; level--) {
            while (p->next[level]->data < x)
                p = p->next[level];
            path[level] = p;
        }
        return p->next[0]->data == x;
    }
    SkipList& insert(int x) {
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
            
            SkipNode *p = new SkipNode(x, lev);
            for (int level = lev; level >= 0; level--) {
                p->next[level] = path[level]->next[level];
                path[level]->next[level] = p;
            }
            
            cout << "数据" << x << "成功插入第" << lev << "层。" << endl;
        }
        return *this;
    }
    
    SkipList& del(int x) {
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
                cout << p->next[lev]->data << " -> ";
                p = p->next[lev];
            }
            cout << "Max" << endl;
        }
    }
};
int main(){
    int n, t;
    cout << "请输入预计的数据个数：" << endl; //实际数据个数允许超过预计个数，但平均性能会变差
    cin >> n;
    cout << "请输入数据的上界（<2147483647）：" << endl;
    cin >> t;
    SkipList mylist(n, t);
    
    while(1) {
        cout << "请选择操作（1：插入，2：查询，3：删除，0：退出）：" << endl;
        cin >> t;
        if(!t) break;
        switch(t) {
            case 1:
                cout << "请输入要插入的元素值：" << endl;
                cin >> n;
                mylist.insert(n).print();
                break;
            case 2:
                cout << "请输入要查询的元素值：" << endl;
                cin >> n;
                cout << (mylist.search(n) ? "存在此元素。" : "不存在此元素。") << endl;
                break;
            case 3:
                cout << "请输入要删除的元素值：" << endl;
                cin >> n;
                mylist.del(n).print();
                break;
            default:
                cout << "输入错误。请重新选择。" << endl;
        }
    }
    
    return 0;
}