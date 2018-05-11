#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include<queue>
#include"hfmnode.h"

//记录输入路径
char PATH_IN[256];
//记录输出路径
char PATH_OUT[256];
//记录每个字符出现的顺序
int NUMCH[256];
//记录哈夫曼编码
std::string HFMcode[256];
//记录文件中字符个数
long long int FILELENGTH;
//使用优先队列生成哈夫曼树
std::priority_queue<HFMNode> HFMQueue;
//记录字节的8位bit
char BIT[8]= {1,2,4,8,16,32,64,(char)128};

#endif // GLOBAL_H_INCLUDED
