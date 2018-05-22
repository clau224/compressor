#include<iostream>
#include<fstream>
#include<conio.h>
#include"global.h"
#include<string.h>

using namespace std;

void GetPath()
{
    cout<<"输入待压缩文件路径!\n";
    cin>>PATH_IN;
}

//计数各个字符出现次数
void CountNum()
{
    ifstream ToCompress(PATH_IN, ios::binary);
    char ch;
    FILELENGTH=0;
    ch=ToCompress.get();
    while(!ToCompress.eof())
    {
        FILELENGTH++;
        NUMCH[ch+128]++;
        ch=ToCompress.get();
    }
    ToCompress.close();
}

//创建哈夫曼树
void CreateTree()
{
    for(int i=0; i<256; i++)
    {
        if(NUMCH[i]!=0)
        {
            HFMNode temp(i-128, NUMCH[i]);
            HFMQueue.push(temp);
        }
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
        HFMcode[root->ascii+128]=HFMCode;
        return;
    }
    else if(root->lchild &&root->rchild)
    {
        getHFMCode(root->lchild, HFMCode+"0");
        getHFMCode(root->rchild, HFMCode+"1");
    }
}

/*
char getASCII(int choose)
{
    static HFMNode record=HFMQueue.top();
    if(choose==0){
        record=*record.lchild;
    }
    else{
        record=*record.rchild;
    }
    if(record.lchild==NULL && record.rchild==NULL){
        char ans=record.ascii;
        record=HFMQueue.top();
        return ans;
    }
    return -1;
}
*/

//保存密码本
void savePSW()
{
    strcpy(PATH_OUT, PATH_IN);
    strcpy(strrchr(PATH_OUT,'.'), ".ljwrcd");

    ofstream PSWCompress(PATH_OUT, ios::binary);

    PSWCompress.write(strrchr(PATH_IN,'.'),sizeof(char)*10);
    PSWCompress.write((char *)&FILELENGTH,sizeof(long long int));
    for(int i=0; i<256; i++)
        PSWCompress.write((char *)&NUMCH[i],sizeof(int));
    PSWCompress.close();
}

//读取密码本
void readPSW()
{
    strcpy(strrchr(PATH_IN,'.'), ".ljwrcd");

    ifstream PSWDeCompress(PATH_IN, ios::binary);

    PSWDeCompress.read((char*)suffix, sizeof(char)*10);
    PSWDeCompress.read((char*)&FILELENGTH,sizeof(long long int));
    for(int i=0; i<256; i++)
        PSWDeCompress.read((char *)&NUMCH[i],sizeof(int));
    PSWDeCompress.close();
}

//保存被压缩文件
void saveNOTE()
{
    strcpy(PATH_OUT, PATH_IN);
    strcpy(strrchr(PATH_OUT,'.'), ".ljw");

    ifstream ToCompress(PATH_IN, ios::binary);
    ofstream HasCompress(PATH_OUT, ios::binary);

    char ch=ToCompress.get();
    int index=0;
    char ans_temp;
    while(!ToCompress.eof())
    {
        //cout<<ch<<endl;
        int length=HFMcode[ch+128].length();
        for(int i=0; i<length; i++)
        {
            if(HFMcode[ch+128][i]=='1')
                ans_temp=ans_temp|BIT[index];
            index++;
            if(index==8)
            {
                //cout<<ans_temp<<"----"<<endl;
                HasCompress.write((char*)&ans_temp,sizeof(char));
                index=0;
                ans_temp=0;
            }
        }
        ch=ToCompress.get();
    }
    if(index>0)
        HasCompress.write(&ans_temp,sizeof(char));
    ToCompress.close();
    HasCompress.close();
}

//读取被压缩文件
void readNOTE()
{
    strcpy(strrchr(PATH_IN, '.'), ".ljw");
    strcpy(PATH_OUT, PATH_IN);
    strcpy(strrchr(PATH_OUT, '.'), suffix);

    ifstream ToDeCompress(PATH_IN, ios::binary);
    ofstream HasDeCompress(PATH_OUT, ios::binary);

    char ch=0;
    ToDeCompress.read((char*)&ch, sizeof(char));
    int index=0;
    while(FILELENGTH--)
    {
        HFMNode record=HFMQueue.top();
        while(true)
        {
            if(record.lchild==NULL && record.rchild==NULL)
            {
                HasDeCompress.write((char*)&record.ascii, sizeof(char));
                record=HFMQueue.top();
                break;
            }
            if(ch&BIT[index])
            {
                record=*record.rchild;
            }
            else
            {
                record=*record.lchild;
            }
            index++;
            if(index==8)
            {
                ToDeCompress.read((char*)&ch, sizeof(char));
                index=0;
            }
        }
    }

    ToDeCompress.close();
    HasDeCompress.close();
}

//压缩过程
void Compress()
{
    GetPath();
    CountNum();
    CreateTree();
    getHFMCode(new HFMNode(HFMQueue.top()), "");
    savePSW();
    saveNOTE();
}

//解压缩过程
void DeCompress()
{
    GetPath();
    readPSW();
    CreateTree();
    getHFMCode(new HFMNode(HFMQueue.top()), "");
    readNOTE();
}

/*
void Look()
{
    char Path[256];
    cout<<"请输入测试路径"<<endl;
    cin>>Path;
    ifstream check(Path, ios::in);
    char temp=0;
    check.read((char*)&temp, sizeof(char));
    int COUNT=30;
    while(COUNT--)
    {
        cout<<(int)temp<<endl;
        check.read((char*)&temp, sizeof(char));
    }
    check.close();
}
*/

void Init()
{
    for(int i=0; i<256; i++)
    {
        PATH_IN[i]='0';
        PATH_OUT[i]='0';
        PATH_OUT[i]='0';
        NUMCH[i]=0;
        HFMcode[i]="";
    }
    FILELENGTH=0;
    while(!HFMQueue.empty())
        HFMQueue.pop();
}
