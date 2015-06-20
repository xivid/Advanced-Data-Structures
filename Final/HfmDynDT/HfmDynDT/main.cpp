//
//  main.cpp
//  HfmDynDT - Dynamic Data Transfer based on Huffman Coding
//
//  Modified by 杨志飞 on 15/6/4.
//  Copyright (c) 杨志飞；2014年夏_HIT_C++语言程序设计课程组.
//  本程序中模拟打乱、发送和接收数据包的框架修改自C++课程大作业所给框架，对数据包进行处理、排序、编解码的数据结构和算法为完全自主设计。

#include<iostream>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "StreamBuffer.h"
using namespace std;

//#define TEST_FRAME  //用于测试代码框架的正确性

void GenDisOrder(int iSendOrder[],int iPacketNum)
{
    int i,j,k;
    
    for(i=0;i<iPacketNum;i++)//先产生顺序的序列：0，1,2，.....iPacketNum-1
        iSendOrder[i] = i;
    
    if( iPacketNum < 5)
        return;
    
    int n,temp;
    n =  rand()%(iPacketNum/5) +1;    //置乱的次数，最多20%*2个数据包
    for(i=0;i< n; i++)
    {//交换j、k两个数据包的顺序
        j = rand()%(iPacketNum/2) + 1;
        k = rand()%( iPacketNum - j);
        temp =  iSendOrder[j];
        iSendOrder[j] = iSendOrder[k];
        iSendOrder[k]=temp;
    }
}

int main()
{
    char srcfileName[500]="./song.mp3";
    char dstfileName[500]="./result.mp3"; //结果有一定错误
    FILE* fpSrcFile = NULL;
    FILE* fpDstFile = NULL;
    const int MTU =  1500;//最大传输单元，网络术语，表示一个数据包大最大尺寸，单位：字节
    unsigned int iOffset;
    int iReadBytes = 0, iWantReadBytes;
    HuffmanTree tree;
    //tree.insert('a');
    int  iContinueBytes;
    int iUseBytes;
    unsigned int iOutDataOffset;
    char  *pOutData;
    HuffmanTree encoder;
    StreamBuffer MyBuffer;
    
    const int iMaxPacketNum = 20; //每次读入20个数据包，然后以乱序的形式发给排序模块（StreamBuffer类）
    int iSendOrder[iMaxPacketNum];//记录下发数据包的顺序
    unsigned int iPacketOffset[iMaxPacketNum];//记录每个数据包中第一个字节数据的偏移量
    unsigned int iPacketLen[iMaxPacketNum];//记录每个数据包中的数据长度
    unsigned int iCompSize[iMaxPacketNum]; //记录每个数据包压缩后的大小（字节数）
    char       (*pDataBuf)[MTU]; //数据包缓冲区。创建方法1：指向一维数组的指针，下一步会为它一次性申请一个二维数组
    //char     *pDataBuf[iMaxPacketNum];//  创建方法2，指针数组，一步会为它多次申请空间，每次申请一个一维数组，释放也要多次
    int   iPacketNum;
    int i;
    int iPackNo;
    
    srand(100);//用固定值初始化，会生成固定的随机数序列，方便测试程序，否则用srand( (unsigned)time( NULL ) );
    
    pDataBuf = new char[iMaxPacketNum][MTU];//方法1
    /*for( i=0;i<iMaxPacketNum;i++)//方法2
     {
     pDataBuf[i] = new char[MTU];
     }*/
    
    
    fpSrcFile = fopen(srcfileName, "rb");
    if( fpSrcFile == NULL )
    {
        cout<<"Cann't open file: "<<srcfileName<<endl;
        return 1;
    }
    
    fpDstFile = fopen(dstfileName, "wb");
    if( fpDstFile == NULL )
    {
        cout<<"Cann't create file: "<< dstfileName <<endl;
        return 2;
    }
    
    iWantReadBytes = 1024;
    do
    {
        iPacketNum = 0;
        for( i=0;i<iMaxPacketNum;i++)//初始化数据包长度为0，表示没有读入数据
            iPacketLen[i] = iCompSize[i] = 0;//2014.07.11  iPacketNum->i
        //	iReadBytes = fread(pDataBuf[iPacketNum], 1, iWantReadBytes, fpSrcFile);
        do
        {
            string enc;
            iPacketOffset[iPacketNum] = ftell(fpSrcFile);
            iReadBytes = fread(pDataBuf[iPacketNum], 1, iWantReadBytes, fpSrcFile);
            iPacketLen[iPacketNum] = iReadBytes; //当前数据包读取成功，记录数据包长度，否则依旧是0
            enc = encoder.encodePacket(pDataBuf[iPacketNum], iReadBytes);
            iCompSize[iPacketNum] = enc.length();
            memcpy(pDataBuf[iPacketNum], enc.c_str(), iCompSize[iPacketNum]);
            iWantReadBytes =  (iPacketOffset[iPacketNum]+iPacketNum*iPacketNum)%500+400;//下一个数据包读取长度
            iPacketNum++;
        }  while( iReadBytes > 0 && iPacketNum < iMaxPacketNum );//读入一组数据包，如果文件结束：iReadBytes<1
        
        //把刚刚已经读入一组数据包，乱序下发给排序模块
        GenDisOrder(iSendOrder,iMaxPacketNum);
        for(i=0;i<iMaxPacketNum;i++)//只要长度不为0，就发给排序模块
        {
            iPackNo = iSendOrder[i];
            if(iPacketLen[iPackNo] > 0 )//有数据，给给排序模块
            {
#ifdef TEST_FRAME
                iUseBytes = iPacketLen[iPackNo];
                pOutData = pDataBuf[iPackNo];
                iOutDataOffset = iPacketOffset[iPackNo];
#else
                MyBuffer.ReceiveData(iPacketOffset[iPackNo],iPacketLen[iPackNo],pDataBuf[iPackNo], iCompSize[iPackNo]);
                iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
                iUseBytes = iContinueBytes - 100;//假设用了一部分
                if( iContinueBytes  > 1024) //示例数值，可以调整
#endif
                {
                    fseek(fpDstFile,iOutDataOffset,SEEK_SET);
                    fwrite(pOutData,iUseBytes,1,fpDstFile);
                    MyBuffer.RemoveData(iUseBytes);
                }
            }
        }
    }while(iReadBytes>0);//说明输入文件还有数据，继续....
    
    //输入结束，把缓冲区中剩余排好序的数据取出
    iContinueBytes = MyBuffer.ContinueBytes(iOutDataOffset, pOutData);
    if( iContinueBytes > 0 )
    {
        fseek(fpDstFile,iOutDataOffset,SEEK_SET);
        fwrite(pOutData,iContinueBytes,1,fpDstFile);
    }
    
    fclose(fpDstFile);
    fclose(fpSrcFile);
    
    
    
    delete []pDataBuf;//方法1
    /*for( i=0;i<iMaxPacketNum;i++) //方法2
     {
     delete []pDataBuf[i];
     }*/
    //★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
    //   可用的文件比对软件： BCompare，很好用，强烈推荐
    //★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
    return 0;
}
