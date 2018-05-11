#ifndef HFMNODE_H_INCLUDED
#define HFMNODE_H_INCLUDED

class HFMNode
{
public:
    char ascii;
    int num;
    HFMNode* lchild;
    HFMNode* rchild;

    HFMNode() {};
    HFMNode(char a, int b)
    {
        ascii=a;
        num=b;
        lchild=NULL;
        rchild=NULL;
    }
    friend bool operator < (HFMNode A, HFMNode B)
    {
        return A.num > B.num;
    }
};


#endif // HFMNODE_H_INCLUDED
