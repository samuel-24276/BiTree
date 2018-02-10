#include<iostream>

const int MAXSIZE=20;

template<class T>
struct BiTNode
{
    T data;
    struct BiTNode<T> *lch;
    struct BiTNode<T> *rch;
};

template<class T>
class BiTree
{
    void Create(BiTNode<T>* &R, T a[], int i);
    void Destroy(BiTNode<T>* R);
public:
    BiTNode<T> *root;
    BiTree();
    BiTree(T a[]);
    ~BiTree();
    int GetDeepth(BiTNode<T> *R);
    int LeafCount(BiTNode<T> *R);       ///求叶子节点数量
    int Count(BiTNode<T> *R);           ///求结点总数
    void PreOrder1(BiTNode<T> *R);
    void InOrder1(BiTNode<T> *R);
    void PostOrder1(BiTNode<T> *R);
    void LevelOrder(BiTNode<T> *R);
    void PreOrder2(BiTNode<T> *R);
    void PreOrder3(BiTNode<T> *R);
    void InOrder2(BiTNode<T> *R);
    void InOrder3(BiTNode<T> *R);
    void PostOrder2(BiTNode<T> *R);
    void PostOrder3(BiTNode<T> *R);
};

///=======================================函数的具体实现================================
template<class T>
void BiTree<T>::Create(BiTNode<T>* &R, T a[], int i)
{
    if(a[i-1] != '0' && a[i-1] != 0)
    {
        R = new BiTNode<T>;
        R->data = a[i-1];
        R->lch = R->rch = NULL;
        Create(R->lch, a, 2*i);
        Create(R->rch, a, 2*i+1);
    }
}

template<class T>
void BiTree<T>::Destroy(BiTNode<T>* R)
{
    if(R)
    {
        Destroy(R->lch);
        Destroy(R->rch);
        delete R;
    }
}

template<class T>
BiTree<T>::BiTree(T a[])
{
    Create(root, a, 1);
}

template<class T>
BiTree<T>::BiTree()
{
    std::cout<<"请输入二叉树所有结点个数（包含空结点）：";
    int size;
    std::cin>>size;
    if(size>MAXSIZE)    throw"二叉树结点过多，请适当减少";
    std::cout<<"开始输入(以0表示空结点)：";
    T a[size];
    for(int i=0; i<size; ++i)
    {
        std::cin>>a[i];
    }
    Create(root, a, 1);
}

template<class T>
BiTree<T>::~BiTree()
{
    Destroy(root);
}

///=============================================递归实现的遍历算法=================================
template<class T>
void BiTree<T>::PreOrder1(BiTNode<T> *R)
{
    if(R != NULL)
    {
        std::cout<<R->data<<" ";
        PreOrder1(R->lch);
        PreOrder1(R->rch);
    }
}

template<class T>
void BiTree<T>::InOrder1(BiTNode<T> *R)
{
    if(R!=NULL)
    {
        InOrder1(R->lch);
        std::cout<<R->data<<" ";
        InOrder1(R->rch);
    }
}

template<class T>
void BiTree<T>::PostOrder1(BiTNode<T> *R)
{
    if(R!=NULL)
    {
        PostOrder1(R->lch);
        PostOrder1(R->rch);
        std::cout<<R->data<<" ";
    }
}

///=============================================用队列实现的层次遍历================================
template<class T>
void BiTree<T>::LevelOrder(BiTNode<T> *R)
{
    std::cout<<"层次遍历：";
    BiTNode<T>* queue[MAXSIZE];         ///指针数组的应用
    int f=0, r=0;
    if(R!=NULL)
        queue[++r] = R;
    while(f!=r)
    {
        BiTNode<T> *p = queue[++f];
        std::cout<<p->data<<" ";
        if(p->lch!=NULL)
            queue[++r] = p->lch;
        if(p->rch!=NULL)
            queue[++r] = p->rch;
    }
    std::cout<<std::endl;
}

///========================================非递归进行二叉树遍历=====================================================
///区分是左子树遍历结束还是右子树遍历结束
template<class T>
class SNode
{
public:
    BiTNode<T> *ptr;
    int tag;                ///左子树标识为1，右子树标识为2
};

template<class T>
void BiTree<T>::PreOrder2(BiTNode<T> *R)
{
    std::cout<<"前序遍历非递归：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    do
    {
        while(R != NULL)            ///入栈，访问左子树
        {
            S[++top].ptr = R;
            S[top].tag = 1;
            std::cout<<R->data<<" ";
            R = R->lch;
        }
        while((top!=-1) && S[top].tag==2)
            top--;      ///出栈为访问右子树做准备

        if((top!=-1) && S[top].tag==1)         ///设置栈顶，访问右子树
        {
            R = S[top].ptr->rch;
            S[top].tag = 2;
        }
    }
    while(top != -1);
    std::cout<<std::endl;
}

template<class T>
void BiTree<T>::InOrder2(BiTNode<T> *R)
{
    std::cout<<"中序遍历非递归：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    do
    {
        while(R!=NULL)
        {
            S[++top].ptr = R;
            S[top].tag = 1;
            R= R->lch;
        }
        while(top!=-1 && S[top].tag==2)
            top--;      ///出栈为访问右子树做准备
        if((top!=-1) && S[top].tag==1)
        {
            std::cout<<S[top].ptr->data<<" ";
            R = S[top].ptr->rch;
            S[top].tag = 2;
        }
    }while(top!=-1);
    std::cout<<std::endl;
}

template<class T>
void BiTree<T>::PostOrder2(BiTNode<T> *R)
{
    std::cout<<"后序遍历非递归：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    do
    {
        while(R!=NULL)
        {
            S[++top].ptr = R;
            S[top].tag = 1;
            R= R->lch;
        }
        while(top!=-1 && S[top].tag==2)
        {
            std::cout<<S[top].ptr->data<<" ";
            top--;      ///出栈
        }

        if((top!=-1) && S[top].tag==1)
        {
            R = S[top].ptr->rch;
            S[top].tag = 2;
        }
    }while(top!=-1);
    std::cout<<std::endl;
}

///==========================非递归遍历的改进算法==============================================================
template<class T>
void BiTree<T>::PreOrder3(BiTNode<T> *R)        //简化后
{
    std::cout<<"前序遍历非递归改进：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    while((top!=-1) || (R!=NULL))
    {
        if(R!=NULL)
        {
            std::cout<<R->data<<" ";
            S[++top].ptr = R;
            R= R->lch;
        }
        else
        {
            R = S[top--].ptr;
            R = R->rch;
        }
    }
    std::cout<<std::endl;
}

template<class T>
void BiTree<T>::InOrder3(BiTNode<T> *R)        //简化后
{
    std::cout<<"中序遍历非递归改进：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    while((top!=-1) || (R!=NULL))
    {
        if(R!=NULL)
        {
            S[++top].ptr = R;
            R= R->lch;
        }
        else
        {
            R = S[top--].ptr;
            std::cout<<R->data<<" ";
            R = R->rch;
        }
    }
    std::cout<<std::endl;
}

template<class T>
void BiTree<T>::PostOrder3(BiTNode<T> *R)        //简化后
{
    std::cout<<"后序遍历非递归改进：";
    SNode<T> S[100];       ///栈
    int top = -1;       ///栈顶指针
    while((top!=0) || (R!=NULL))
    {
        if(R!=NULL)
        {
            S[++top].ptr = R;
            R= R->lch;
        }
        else
        {
            R = S[top--].ptr;
            std::cout<<R->data<<" ";
            R = R->rch;
        }
    }
    while((top!=-1) || (R!=NULL))
    {
        if(R!=NULL)
        {
            S[++top].ptr = R;
            R= R->lch;
        }
        else
        {
            R = S[top--].ptr;
            std::cout<<R->data<<" ";
            R = R->rch;
        }
    }
    std::cout<<std::endl;
}

///=============================递归求结点总数，深度，叶子结点总数=====================================
///求二叉树结点总数
template<class T>
int BiTree<T>::Count(BiTNode<T> *R)
{
    if(R==NULL) return 0;
    else
    {
        int m = Count(R->lch);
        int n = Count(R->rch);
        return m+n+1;
    }
}

///求二叉树深度
template<class T>
int BiTree<T>::GetDeepth(BiTNode<T> *R)
{
    int deep = 0;
    if (R != NULL)
    {
        int leftdeep = GetDeepth(R->lch);
        int rightdeep = GetDeepth(R->rch);
        deep = leftdeep >= rightdeep?leftdeep+1:rightdeep+1;
    }
    return deep;
}

///求二叉树叶子结点总数
template<class T>
int BiTree<T>::LeafCount(BiTNode<T> *R)
{
    if(R==NULL)     return 0;           ///重要条件
    else if(R->lch==NULL && R->rch==NULL) return 1;
    else
    {
        int m = LeafCount(R->lch);
        int n = LeafCount(R->rch);
        return m+n;
    }
}