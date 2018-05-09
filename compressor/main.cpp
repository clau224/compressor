#include<iostream>
#include<fstream>
#include<conio.h>
#include<algorithm>
#include"hfmnode.h"
#include"compress.h"

using namespace std;

int main()
{
    cout<<"¹þ·òÂüÑ¹Ëõ½âÑ¹Ëõ³ÌÐò!\n1£ºÑ¹Ëõ \n2£º½âÑ¹Ëõ \n0£ºÍË³ö"<<endl;
    char ans=getch();
    switch(ans){
        case '1':
            GetPath();
    //getHFMCode(new HFMNode(HFMQueue.top()), "");
            Compress();
            break;
        case '2':
            break;
        default:
            break;
    }
    return 0;
}
