
// main.c
// 本文件为动态搜索平衡二叉树接口测试程序 不理解没关系 仅供参考

#include "binary tree.h"

// ((2 ^ (sizeof(ElemNumb) * 8 - 1)) - 1)
static const ElemNumb Max = (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1);
// 此为算法 即ElemNumb为某种数据类型 则Max自动生成该类型可表示的最大值

int main(const int argc, const char * const argv[ ])
{

	Tree BinaryTree;
	printf("\n二叉搜索%s平衡树\t%s\t本例中以0x起始的数字均为内存地址\n", 
#ifdef AVL
		"",
#else
		"非",
#endif
		sizeof(void *) == 4 ? "x86" : "x64");
	CreateBinaryTree(&BinaryTree, Max);


#ifdef STDIN
	InputBinaryTreeFromKeyboard(&BinaryTree, stdin);
#else
	const TreeItem BinaryTreeElement[] = {{ 16 }, { 8 }, { 24 }, { 4 }, { 12 }, { 20 }, { 28 }, { 2 }, { 6 }, { 10 }, { 14 }, { 18 }, { 22 }, { 26 }, { 30 }, { 1 }, { 3 }, { 5 }, { 7 }, { 9 }, { 11 }, { 13 }, { 15 }, { 17 }, { 19 }, { 21 }, { 23 }, { 25 }, { 27 }, { 29 }, { 31 }};
	ElemNumb index;
	for (index = 0; index < sizeof(BinaryTreeElement) / sizeof(BinaryTreeElement[0]); ++index)
		AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[index]);
#endif

/*
	// LL旋转
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[3]); // 4
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[4]); // 12
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[5]); // 6


	// LR旋转
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[3]); // 4
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[4]); // 12
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[9]); // 10


	// RL旋转
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[5]); // 20
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[11]); // 18


	// RR旋转
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[6]); // 28
	AddNodeOfBinaryTree(&BinaryTree, &BinaryTreeElement[14]); // 30
*/
	
	FileOperationWithBinaryTree(&BinaryTree, "binary tree", WRITE);
	DestroyBinaryTree(&BinaryTree);


	CreateBinaryTree(&BinaryTree, Max);
	FileOperationWithBinaryTree(&BinaryTree, "binary tree", READ);
	OutputBinaryTreeToScreen(&BinaryTree, stdout, NULL); // 调用OutputBinaryTreeToScreen函数时参数3固定为NULL
	DestroyBinaryTree(&BinaryTree);

#ifdef WINDOWS_VISUALSTUDIO
	_getch();
#endif

	return 0;
}
