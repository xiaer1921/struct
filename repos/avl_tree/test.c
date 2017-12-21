#include <stdio.h>
#include "avl_tree.h"

static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

void main()
{
    int i,ilen;
    AVLTree root=NULL;

    printf("== 高度: %d\n", getAVLTreeHeight(root));
    printf("== 依次添加: ");
    ilen = TBL_SIZE(arr);
    for(i=0; i<ilen; i++)
    {
        printf("%d ", arr[i]);
        root = avlTreeInsert(root, arr[i]);
    }
    printf("\n== 前序遍历: ");
    preorderAVLTree(root);

    printf("\n== 中序遍历: ");
    inorderAVLTree(root);

    printf("\n== 后序遍历: ");
    postorderAVLTree(root);
    printf("\n");

    printf("== 高度: %d\n", getAVLTreeHeight(root));
    printf("== 最小值: %d\n", avlTreeMinimum(root)->key);
    printf("== 最大值: %d\n", avlTreeMaximum(root)->key);
    printf("== 树的详细信息: \n");
    printAVLTree(root, root->key, 0);


    i = 8;
    printf("\n== 删除根节点: %d", i);
    root = avlTreeDelete(root, i);

    printf("\n== 高度: %d", getAVLTreeHeight(root));
    printf("\n== 中序遍历: ");
    inorderAVLTree(root);
    printf("\n== 树的详细信息: \n");
    printAVLTree(root, root->key, 0);

    // 销毁二叉树
    destroyAVLTree(root);
}
