#include<iostream>

const int MAXSIZE=10;

///静态三叉链表
struct HNode
{
    size_t weight;          ///结点权值
    size_t parent;
    size_t lchild;
    size_t rchild;
    bool tag;               ///标识是否已经被选作过最小值与次小值，即是否做过底层结点,true表示未做过
};

///哈夫曼编码表
struct HCode
{
    char data;
    char code[MAXSIZE];
};

class Huffman
{
    int leaf;                               ///叶子结点个数，即编码字符的种类
    HNode* HTree;                           ///哈夫曼树
    HCode* HCodeTable;                      ///哈夫曼编码表
public:
    int GetDeepth(int root);
    int GetWPL();
    void SelectMin(int &x, int a, int b);
    void SelectMin(int &x, int &y, int a, int b);
    void CreateHTree(int a[], int n);                   ///创建哈夫曼树
    void CreateCodeTable(char b[], int n);              ///创建编码表
    void Encode(char *p, char *q);                      ///编码
    void Decode(char* p, char *q);                      ///解码,p,q一定要有明确的数组指向
    void Reverse(char* code);                    ///字符串逆置
    ~Huffman();
};


///输入参数a[]存储每种字符的权值，n为字符的种类
void Huffman::CreateHTree(int a[], int n)
{
    ///由二叉树性质得一棵有n个叶子的哈夫曼树共有2n-1个结点
    HTree = new HNode[2*n-1];
    leaf = n;
    //根据权重数组a[]初始化哈夫曼树
    for(int i=0; i<n; ++i)
    {
        HTree[i].weight = a[i];
        HTree[i].lchild = -1;
        HTree[i].rchild = -1;
        HTree[i].parent = -1;
        HTree[i].tag = true;
    }
    int x, y;
    for(int i=n; i<2*n-1; ++i)
    {
        ///***************************************
        HTree[i].tag = true;                        ///忘记这一步导致出了大错，找了一上午BUG
        ///**************************************

        ///从1-i中选出两个权值最小的结点，读者自行实现

        SelectMin(x, y, 0, i);
//        SelectMin(x, 0, i);
//        SelectMin(y, 0, i);
//        std::cout<<x<<"&"<<y<<std::endl;
        HTree[x].parent = HTree[y].parent = i;
        HTree[i].weight = HTree[x].weight + HTree[y].weight;
        std::cout<<"权值："<<HTree[i].weight<<"\n";
        HTree[i].lchild = x;
        HTree[i].rchild = y;
        HTree[i].parent = -1;
    }
}

///===========================生成编码表===============================
void Huffman::CreateCodeTable(char b[], int n)
{
    std::cout<<"========================字符编码对照表==========================\n";
    std::cout<<"字符  ";
    std::cout<<"|编码\n";
    HCodeTable = new HCode[n];
    for(int i=0; i<n; ++i)
    {
        HCodeTable[i].data = b[i];
        int child = i;
        int parent = HTree[i].parent;
        int k=0;
        while(parent!=-1)
        {
            if(child==HTree[parent].lchild)        //左孩子标0
                HCodeTable[i].code[k] = '0';
            else
                HCodeTable[i].code[k] = '1';
            ++k;
            child = parent;
            parent = HTree[child].parent;
        }
        HCodeTable[i].code[k] = '\0';
        std::cout<<HCodeTable[i].data<<"     |";
        ///测试部分，逆置前反了的，即错误的编码
//        std::cout<<HCodeTable[i].code<<"\n";
        Reverse(HCodeTable[i].code);
    }
    std::cout<<"============================================================\n ";
}


///编码算法，遇到无法编码的字符会跳过去
void Huffman::Encode(char *p, char *q)              ///p为字符，q为编码
{
    int i;
    while( *p!='\0')            ///判断字符是否结束
    {
        for(i=0; i<leaf; ++i)           ///寻找对应字符的编码，找到则指针指向下一个字符
        {
            if(HCodeTable[i].data == *p)          ///此处绝不能p++，找了好长时间错误
            {
                int j=0;
                while(HCodeTable[i].code[j]!='\0')
                {
                    *q = HCodeTable[i].code[j++];
                    q++;
                }
            }
        }
        ++p;
    }
}

///解码算法
void Huffman::Decode(char* p, char *q)          ///p为编码，q为字符
{
    while(*p!='\0')
    {
        int parent = 2*leaf-1-1;           ///根节点在HTree中的下标
        while(HTree[parent].lchild!=-1)
        {
            if(*p=='0')
                parent = HTree[parent].lchild;
            else
                parent = HTree[parent].rchild;
            p++;
        }
        *q = HCodeTable[parent].data;
        q++;
    }
}

int Huffman::GetDeepth(int root)//=2*leaf-1-1)
{

}

int Huffman::GetWPL()
{

}

Huffman::~Huffman()
{
    delete [] HTree;
    delete [] HCodeTable;
}

void Huffman::Reverse(char* code)               ///被注释掉的是测试验证正确性的部分
{
    char temp[MAXSIZE];
    int i, j, k;
    for(i=0; ; ++i)
    {
        if(code[i]!='\0')
            temp[i] = code[i];
        else break;
    }
    k = i;
    //std::cout<<"逆置后（正确的编码）："<<i<<"\n";
    for(j=0; i>0; ++j)
        code[j] = temp[--i];
    code[j] = '\0';

    for(j=0; j<k; ++j)
        std::cout<<code[j];
    std::cout<<std::endl;
}

///=================求哈夫曼树中的最小的权值所在结点在静态链表中的下标========================
void Huffman::SelectMin(int &x, int a, int b)
{
    if(a>=b)        throw"范围错误";
    for(int j=a; j<b; ++j)        ///找到第一个未做过最小值的结点下标
    {
        if(HTree[j].tag)
        {
            x = j;
            break;
        }
    }
    ///求最小值
    for(int j=x; j<b ; ++j)
    {
        if(HTree[j].tag)
            if(HTree[x].weight>HTree[j].weight)
                x = j;
    }
    HTree[x].tag = false;
}

///=================求哈夫曼树中的最小的两个权值所在结点在静态链表中的下标========================
void Huffman::SelectMin(int &x, int &y, int a, int b)
{
    if(a>=b)        throw"范围错误";
    for(int j=a; j<b; ++j)        ///找到第一个未做过最小值的结点下标
    {
        if(HTree[j].tag)
        {
            x = j;
            break;
        }
    }
    ///求最小值
    for(int j=x; j<b ; ++j)
    {
        if(HTree[j].tag)
            x = (HTree[x].weight<HTree[j].weight)?x:j;
    }
    HTree[x].tag = false;

    for(int j=a; ; ++j)        ///找到第一个未做过次小值的结点下标
    {
        if(HTree[j].tag)
        {
            y = j;
            break;
        }
    }

    ///两个for循环求次小值
    for(int j=y; j<x; ++j)
    {
        if(HTree[j].tag)
        {
            y = (HTree[y].weight<HTree[j].weight)?y:j;
        }
    }
    for(int j=x+1; j<b; ++j)
    {
        if(HTree[j].tag)
        {
            y = (HTree[y].weight<HTree[j].weight)?y:j;
        }
    }
    HTree[y].tag = false;
}