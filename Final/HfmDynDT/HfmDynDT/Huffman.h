//
//  Huffman.h
//  HfmDynDT
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef HfmDynDT_Huffman_h
#define HfmDynDT_Huffman_h
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
    
    string encodePacket(const char* s, size_t length)
    {
        string ret; //用于存储字符形式的二进制串
        for (int i = 0; i < length; i++)
        {
            ret += insert(int((unsigned char)*s++));
        }
        return toByteCode(ret); //返回真正的二进制串
    }
    
    string decodePacket(const char* s, size_t length)
    {
        string ret, tmp;
        int spos = 0, p = root;
        unsigned char chr;
        
        for(int i = 0; i < length; i++) //字符串s内部可能会出现字符'\0'，但不能视为结束，该多长就要读多长
            tmp += toBinary(*s++);
        
        while(tmp[spos]) {
            if (p == nyt) {
                chr = ByteToChar(tmp.substr(spos, spos+8));
                spos += 8;
                if (table[chr]) break; //end-of-input sign
                ret += chr;
                insert(chr);
                p = root;
            }
            else if (!nodes[p].lc && !nodes[p].rc) {
                ret += nodes[p].data;
                insert(nodes[p].data);
                p = root;
            }
            else if (tmp[spos++] == '0')
                p = nodes[p].lc;
            else
                p = nodes[p].rc;
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

#endif
