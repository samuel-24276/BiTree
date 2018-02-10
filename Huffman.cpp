#include "HuffmanTree.h"

int main()
{
    int weight[4] ={2,3,6,9};
    char code[4] = {'a', 'b', 'c', 'd'};
    Huffman H;
    H.CreateHTree(weight, 4);
    H.CreateCodeTable(code, 4);
    ///==================解码模块=======================
    char p[]="011101100";
    char temp[20] = {};
    char *q=temp;
    H.Decode(p, q);
    std::cout<<"解码后结果为：";
    while(*q!='\0')
        std::cout<<*q++;
    ///==================编码模块======================
    std::cout<<"\n编码结果为：";
    char a[6]="accdb";
    char Temp[40] = {};
    q = Temp;
    H.Encode(a, q);
    while(*q!='\0')
        std::cout<<*q++;
    std::cout<<"\n"<<sizeof(code);
   // std::cout<<"该哈夫曼树深度为："<<H.GetDeepth(2*sizeof(code)-1);
    return 0;
}




/// 2018.2.8
