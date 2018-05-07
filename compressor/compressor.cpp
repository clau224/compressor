#include<iostream>
#include<fstream>
#include<queue>
#include<algorithm>
#include"global.h"
#include"hfmnode.h"

using namespace std;

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

int main()
{
    priority_queue<HFMNode> HFMQueue;

    ifstream ToCompress("1.txt",ios::in);
    int ch;
    ch=ToCompress.get();
    while(ch!=EOF)
    {
        numch[ch]++;
        ch=ToCompress.get();
    }
    ToCompress.close();

    for(int i=0;i<256;i++)
    {
        HFMNode temp(i, numch[i]);
        if(numch[i]!=0)
            HFMQueue.push(temp);
    }

    /*
    cout<<HFMQueue.size()<<endl;
    cout<<(char)HFMQueue.top().ascii<<endl;
    HFMQueue.pop();
    cout<<(char)HFMQueue.top().ascii<<endl;
    */

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

    getHFMCode(new HFMNode(HFMQueue.top()), "");

    ifstream ToCompress1("1.txt",ios::in);
    ofstream HasCompress("a.dat", ios::binary|ios::out);
    ch=ToCompress1.get();
    while(ch!=EOF)
    {
        HasCompress.write((char*)&HFMcode[ch], sizeof(HFMcode[ch]));
        ch=ToCompress1.get();
    }
    ToCompress.close();
    HasCompress.close();

    return 0;
}
