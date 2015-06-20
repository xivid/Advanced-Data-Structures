//
//  StreamBuffer.h
//  HfmDynDT
//
//  Created by 杨志飞 on 15/6/4.
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//

#ifndef HfmDynDT_StreamBuffer_h
#define HfmDynDT_StreamBuffer_h
#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Huffman.h"
#include <utility>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
struct packetInfo{
    int offset, bytes, compSize;
    char data[1500];
    packetInfo(int o, int b, int c, const char* pData): offset(o), bytes(b), compSize(c)
    {
        memcpy(data, pData, c);
    }
};
bool operator > (const packetInfo& a, const packetInfo& b) {
    return a.offset > b.offset;
}
class StreamBuffer
{
public:
    StreamBuffer();
    ~StreamBuffer();
    StreamBuffer(int iLen);
    int ReceiveData(unsigned int offset, unsigned int bytes, const char *pData, unsigned int compSize); //最后还要传入压缩后数据包的大小，不然不知道解压终点（因编码内部可能出现'\0'，故终点不能用'\0'判断）
    int ContinueBytes(unsigned int &iDataOffset, char* &pData);
    int RemoveData(int iBytes);
private:
    HuffmanTree decoder;
    char *m_pData;//存数据的buffer，也可以用指针
    int m_iBufferLen; //the size of buffer
    int head, headOffset; //head: index of the head of data in the buffer, headOffset: its offset
    int length; //length: continueBytes starting at head
    int tail;  //tail: the end index of the whole data in the buffer
    priority_queue<packetInfo, vector<packetInfo>, greater<packetInfo> > packetQueue;
    //packetQueue: 优先队列，其元素为每次接收到的数据块的头部偏移量和长度组成的pair，队首元素为偏移量最小的那个
};

int max(int a, int b) {return a > b ? a : b; }
int min(int a, int b) {return a < b ? a : b; }
//-------------------
StreamBuffer::StreamBuffer()
{
    //默认申请512kb的缓冲区
    m_pData = new char[512*1024];
    m_iBufferLen = 512*1024;
    head = headOffset = length = tail = 0;
}
StreamBuffer::StreamBuffer(int iLen)
{
    //申请指定长度的缓冲区
    m_pData = new char[iLen];
    m_iBufferLen = iLen;
    head = headOffset = length = tail = 0;
}
StreamBuffer::~StreamBuffer()
{
    //析构时清空缓冲区数据
    if( NULL !=  m_pData)
        delete []m_pData;
    
}
int StreamBuffer::ReceiveData(unsigned int offset, unsigned int bytes, const char *pData, unsigned int compSize)
{
    // receive data: save to buffer
    int iBytes = 0;
    //memcpy(m_pData+head+offset-headOffset, pData, compSize); //将数据存入缓冲区对应位置，暂不解压（要等前面的解压过后才能解压）
    /*
    string ori;
    ori = decoder.decodePacket(pData, compSize);
    cout << "receive " << compSize << "->" << ori.length() << endl;
    if (ori.length() != bytes) {cout << "error!" << endl; exit(0); }
    memcpy(m_pData+head+offset-headOffset, ori.c_str(), bytes);
    */
    iBytes = bytes; //读到的字节数
    packetQueue.push(packetInfo(offset, iBytes, compSize, pData)); //此次读到的数据块的偏移量和长度信息进入优先队列
    while(headOffset + length == packetQueue.top().offset) {
        //更新从头部开始的连续数据的长度（相当于合并连接连续的数据块，将已连接上的数据块信息出队）
        //1. 解压数据到缓冲区
        string ori;
        ori = decoder.decodePacket(packetQueue.top().data, packetQueue.top().compSize);
        memcpy(m_pData+head+packetQueue.top().offset-headOffset, ori.c_str(), packetQueue.top().bytes);
        
        //2. 更新记录
        length += packetQueue.top().bytes;
        packetQueue.pop();
    }
    tail = max(tail, head+offset-headOffset+iBytes); //更新缓冲区数据尾部的下标
    if(m_iBufferLen - tail < 20480) { //若尾部后面的剩余可用空间不足20480
        //20480是考虑最坏情况：当第0个数据包后面紧接着第19个数据包时。（19*1024约等于20*1024）
        memcpy(m_pData, m_pData+head, tail-head);//将现存数据移到缓冲区开头
        tail -= head; //更新下标记录
        head = 0;
    }
    return iBytes;// bytes the buffer saved
}

int StreamBuffer::ContinueBytes(unsigned int &iDataOffset, char* &pData)
{//返回缓冲区中，排好序的数据的长度（单位字节数）。并通过引用参数返回如下信息
    //iDataOffset: 排好序的数据块中第一个字节的偏移量数值
    //pData：数据指针
    int iContinueBytes = 0;
    iContinueBytes = length; //length就是记录的从开头开始的连续数据的长度
    iDataOffset = headOffset; //头部数据的偏移量
    pData = m_pData + head; //头部数据在内存中的地址
    return iContinueBytes;
}


int StreamBuffer::RemoveData(int iBytes)
{//从缓冲区中把数据"删除",返回删除的字节数
    int iBytesRemoved=0;
    iBytesRemoved = min(iBytes, length); //防止要删除的字节数多于总连续字节数（实际按给定框架不会出现这种情况，只是为严密）
    //更新头部下标变量、偏移量和连续长度
    head += iBytesRemoved;
    headOffset += iBytesRemoved;
    length -= iBytesRemoved;
    
    //从缓冲区中把数据"删除"
    return iBytesRemoved;
}
#endif
