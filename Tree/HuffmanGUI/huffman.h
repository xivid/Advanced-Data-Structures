#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string>
using namespace std;
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
    int nyt; //the index of NYT node in nodes[], starting at 1(root)
    const int root = 1;
public:
    HuffmanTree()
    {
        table = new int[256]();
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

        table[nodes[cur].data] = cur;
        table[nodes[i].data] = i;

        cur = i;
    }

    string toBinary(unsigned char c) {
        string s;
        for (int i = 0; i < 8; ++i, c/=2)
            s = (char)('0' + c%2) + s;
        return s;
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
            ret += (char)data;

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

    static string encode(const char* s)
    {
        HuffmanTree tree;
        string ret;
        while (*s)
        {
            ret += tree.insert(int((unsigned char)*s++));
        }
        return ret;
    }

    static string decode(const char* s)
    {
        HuffmanTree tree;
        string ret;
        ret += *s;
        tree.insert(int((unsigned char)*s++)); //first character

        int p = tree.root;
        while (*s)
        {
            if (*s++ == '0')
                p = tree.nodes[p].lc;
            else
                p = tree.nodes[p].rc;
            if (tree.nodes[p].lc || tree.nodes[p].rc) //not nyt and not leaf
                continue;
            if (p == tree.nyt)
            {
                ret += *s;
                tree.insert((int)(unsigned char)*s++);
            }
            else
            {
                ret += (char)tree.nodes[p].data;
                tree.insert(tree.nodes[p].data);
            }
            p = tree.root;
        }
        return ret;
    }
};

#endif // HUFFMAN_H

