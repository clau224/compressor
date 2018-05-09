#include<iostream>
#include<fstream>
#include<conio.h>
#include"global.h"
#include"hfmnode.h"
#include<string.h>

using namespace std;

void GetPath()
{
    cout<<"输入待压缩文件路径!\n";
    cin>>PATH_IN;
}

void SetljwPath()
{
    strcpy(PATH_OUT_1, PATH_IN);
    strcat(strrchr(PATH_OUT_1,'.'), ".ljw");
}

void SetljwrcdPath()
{
    strcpy(PATH_OUT_2, PATH_IN);
    strcat(strrchr(PATH_OUT_2,'.'), ".ljwrcd");
}

//计数各个字符出现次数
void CountNum()
{
    ifstream ToCompress(PATH_IN,ios::in);
    int ch;
    FILELENGTH=0;
    ch=ToCompress.get();
    while(ch!=EOF)
    {
        FILELENGTH++;
        NUMCH[ch]++;
        ch=ToCompress.get();
    }
    ToCompress.close();
}


void CreateTree()
{
    for(int i=0; i<256; i++)
    {
        HFMNode temp(i, NUMCH[i]);
        if(NUMCH[i]!=0)
            HFMQueue.push(temp);
    }
    while(HFMQueue.size()>1)
    {
        HFMNode* templeft=new HFMNode(HFMQueue.top());
        HFMQueue.pop();
        HFMNode* tempright=new HFMNode(HFMQueue.top());
        HFMQueue.pop();
        HFMNode root(0, templeft->num+tempright->num);
        root.lchild=templeft;
        root.rchild=tempright;
        HFMQueue.push(root);
    }
}


//根据哈夫曼树计算哈夫曼编码
void getHFMCode(HFMNode* root, string HFMCode)
{
    if(root->lchild==NULL && root->rchild==NULL)
    {
        cout<<(char)root->ascii<<":"<<HFMCode<<endl;
        HFMcode[root->ascii]=HFMCode;
        return;
    }
    else if(root->lchild &&root->rchild)
    {
        getHFMCode(root->lchild, HFMCode+"0");
        getHFMCode(root->rchild, HFMCode+"1");
    }
}

void cmprs()
{
    ifstream ToCompress(PATH_IN,ios::in|ios::binary);
    ofstream HasCompress(PATH_OUT_1, ios::binary|ios::out);
    ofstream PSWCompress(PATH_OUT_2, ios::binary|ios::out);
    char ch=ToCompress.get();
    while(ch!=EOF)
    {
        int index=0;
        int length=HFMcode[ch].length();
        for(int i=0;i<length;i++)
        {

        }
        ch=ToCompress.get();
    }
    ToCompress.close();
    HasCompress.close();
}

void Compress()
{
    SetljwPath();
    SetljwrcdPath();
    CountNum();
    CreateTree();
    getHFMCode(new HFMNode(HFMQueue.top()), "");
}
