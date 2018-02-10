#include "BiTree.h"

int main()
{
    int a[MAXSIZE] = {1, 2, 3, 4, 0, 6, 0, 8, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    BiTree<int> T(a);
    T.PreOrder1(T.root);
    std::cout<<std::endl;
    T.InOrder1(T.root);
    std::cout<<std::endl;
    T.PostOrder1(T.root);
    std::cout<<std::endl;
    T.PreOrder2(T.root);

    T.PreOrder3(T.root);

    T.InOrder2(T.root);

    T.InOrder3(T.root);

    T.PostOrder2(T.root);

    T.PostOrder3(T.root);

    T.LevelOrder(T.root);
    std::cout<<"该二叉树结点总数为："<<T.Count(T.root)<<std::endl;
    std::cout<<"该二叉树深度为："<<T.GetDeepth(T.root)<<std::endl;
    std::cout<<"该二叉树叶子结点总数为："<<T.LeafCount(T.root)<<std::endl;
    std::cout<<std::endl;

    ///无参构造二叉树
//    BiTree<char> B;
//    B.PreOrder1(B.root);
//    std::cout<<std::endl;
//    B.InOrder1(B.root);
//    std::cout<<std::endl;
//    B.PostOrder1(B.root);
    return 0;
}
