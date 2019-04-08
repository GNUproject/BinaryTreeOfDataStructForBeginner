
// main.c
// ���ļ�Ϊ��̬����ƽ��������ӿڲ��Գ��� �����û��ϵ �����ο�

#include "binary tree.h"

// ( ( 2 ^ ( sizeof ( ElemNumb ) * 8 - 1 ) ) - 1 )
static const ElemNumb Max = (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1);

int main(const int argc, const char * const argv[ ])
{
	Tree BinaryTree;
	const char * const FileName = "binary tree"; // �ļ��� ����ΪNULL�����ļ������������

	CreateBinaryTree(&BinaryTree, Max, FileName);

#ifndef STDIN
	const TreeItem BinaryTreeElement[] = { { 16 }, { 8 }, { 24 }, { 4 }, { 12 }, { 20 }, { 28 }, { 2 }, { 6 }, { 10 }, { 14 }, { 18 }, { 22 }, { 26 }, { 30 }, { 1 }, { 3 }, { 5 }, { 7 }, { 9 }, { 11 }, { 13 }, { 15 }, { 17 }, { 19 }, { 21 }, { 23 }, { 25 }, { 27 }, { 29 }, { 31 } };
	ElemNumb index;
	for (index = 0; index < sizeof(BinaryTreeElement) / sizeof(BinaryTreeElement[0]); ++index)
		AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[index]);

	const TreeItem SearchItem = { 18 };
	Pair result = SearchBinaryTreeItem(&BinaryTree, &SearchItem); // ���Ҷ��������

	// TreeItem DelNode = { 23 };
	// DelBinaryTreeNode(&BinaryTree, &DelNode);

// #ifdef STDIN
#else	
	InputBinaryTreeFromKeyboard(&BinaryTree, stdin);
#endif

/*
	// LL��ת
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[3]); // 4
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[4]); // 12
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[5]); // 6
*/

/*
	// LR��ת
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[3]); // 4
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[4]); // 12
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[9]); // 10
*/

/*
	// RL��ת
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[5]); // 20
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[11]); // 18
*/

/*
	// RR��ת
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[0]); // 16
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[1]); // 8
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[2]); // 24
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[6]); // 28
	AddBinaryTreeNode(&BinaryTree, &BinaryTreeElement[14]); // 30
*/

	// if (FileName != NULL)
	if (FileName)
	{
		FileOperationByBinaryTree(&BinaryTree, WRITE);
		DestroyBinaryTree(&BinaryTree);

		CreateBinaryTree(&BinaryTree, Max, FileName);
		FileOperationByBinaryTree(&BinaryTree, READ);
	}
	OutputBinaryTreeToMonitor(&BinaryTree, stdout, NULL); // ����OutputBinaryTreeToMonitor����ʱ����3��ԶΪNULL
	DestroyBinaryTree(&BinaryTree);

#ifdef WINDOWS_VISUALSTUDIO
	_getch();
#endif

	return 0;
}
