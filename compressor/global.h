#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include<queue>
#include"hfmnode.h"

//记录输入输出路径
char PATH_IN[255];
char PATH_OUT_1[255];
char PATH_OUT_2[255];
//记录每个字符出现的顺序
int NUMCH[255];
//记录哈夫曼编码
std::string HFMcode[255];
//记录文件中字符个数
long long int FILELENGTH;
//使用优先队列生成哈夫曼树
std::priority_queue<HFMNode> HFMQueue;

#endif // GLOBAL_H_INCLUDED
