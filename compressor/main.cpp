#include<iostream>
#include<fstream>
#include<conio.h>
#include<algorithm>
#include"hfmnode.h"
#include"compress.h"

using namespace std;

int main()
{
    while(true)
    {
        cout<<"哈夫曼压缩解压缩程序!\n1：压缩 \n2：解压缩 \n0：退出"<<endl;
        char ans=getch();
        if(ans=='1'){
            GetPath();
            Compress();
            Init();
        }
        else if(ans=='2');

        else if(ans=='0')
            break;
        else
            cout<<"无法识别的输入！"<<endl;
        cout<<"按任意键继续..."<<endl;
        ans=getch();
        system("cls");
    }
    return 0;
}
