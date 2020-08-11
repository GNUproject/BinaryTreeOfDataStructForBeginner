
// 二叉树
// binary tree.c

#include "binary tree.h"
#include "queue of binary tree.h"
#include "stack of binary tree.h"

#define GetMax(x,y)	((x)>(y)?(x):(y))
#define GetTreeHeight(t) ((t) != NULL ? (t)->Height : -1)

#ifdef LOG
	static const char * const QueueFileName = "队列操作.txt";
#else
	static const char * const QueueFileName = NULL;
#endif

const char * const SameTreeItem = "添加重复数值项\n";
const char * const NoTreeItem = "二叉树中不存在该结点!\n";
const char * const InputError = "输入错误!\n";
const char * const NullPointer = "空指针\n";
const char * const OpenFileError = "打开文件%s失败!\n";
const char * const CloseFileError = "关闭文件%s失败!\n";
const char * const FileOperationError = "文件%s操作失败!\n";
const char * const MemoryNotEnough = "内存不足!\n";

static const char * const DLR = "的前序遍历";	// 前序遍历
static const char * const LDR = "的中序遍历";	// 中序遍历
static const char * const LRD = "的后序遍历";	// 后序遍历
static const char * const level = "的层序遍历"; // 层序遍历
static const char * const EmptyTree = "空树\n";
static const char * const FullTree = "已至数量最大值 请扩充Max或ElemNumb数据单位!\n";
static const char * const LengthError = "二叉树结点数非法\n";

#ifdef AVL
	static void RotateWithLeftChild(TreeNode ** const k2pt);
	static void RotateWithRightChild(TreeNode ** const k2pt);
	static void DoubleWithLeftChild(TreeNode ** const k1pt);
	static void DoubleWithRightChild(TreeNode ** const k1pt);
#endif

#ifdef BACKWARD_POINTER
	static void AddNodeWithBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi, TreeNode *Father);
#else
	static void AddNodeWithoutBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi);
#endif

#ifdef READABLE
	static const char * const ExtendFileName = ".txt";
#else
	static void OutputBinaryTreeToBinaryFile(Tree * const BinaryTree, FILE * const FilePointer);
	static void InputBinaryTreeFromBinaryFile(Tree * const BinaryTree, FILE * const FilePointer);
#endif

static void DeleteAllNodes(TreeNode * const Root);
static void MoreFileOperationByBinaryTree(Tree * const BinaryTree, const char * const FileName, const char * const Mode);
static void PreOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void InOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void PostOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void LevelOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void Traversal(void (*pf) (const Tree * const BinaryTree, FILE * const Stream), const Tree * const BinaryTree, FILE * const Stream);

extern void CreateStack(ArrayList * const Array, const ElemNumb Max, const char * const FileName);
extern void DestroyStack(ArrayList * const Array);
extern void Push(ArrayList * const Array, const ArrayItem * const NewItem);
extern void Pop(ArrayList * const Array, ArrayItem * const DelItem);
extern void CreateQueue(LinkList * const Link, const ElemNumb Max, const char * const FileName);
extern void DestroyQueue(LinkList * const Link);
extern void Enqueue(LinkList * const Link, const LinkItem NewItem);
extern void Dequeue(LinkList * const Link, LinkItem * const DelItem);

void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max, const char * const FileName)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
		UnusualToExit(NullPointer, NULL);
		
	if (Max <= 0)
		UnusualToExit(LengthError, NULL);

	BinaryTree->Root = NULL;
	BinaryTree->Size = 0;
	BinaryTree->MaxSize = Max;

	// if (FileName == NULL)
	if (!FileName)
		BinaryTree->DLRFileName = BinaryTree->LDRFileName = BinaryTree->LRDFileName = BinaryTree->FileName = NULL;

	// if (FileName != NULL)
	else
	{
		char TempDLR[LEN], TempLDR[LEN], TempLRD[LEN], TempFile[LEN];
#ifdef WINDOWS_VISUALSTUDIO
		strncpy_s(TempDLR, _countof(TempDLR), FileName, strlen(FileName) + 1);
		strncat_s(TempDLR, _countof(TempDLR), DLR, strlen(DLR) + 1);

		strncpy_s(TempLDR, _countof(TempLDR), FileName, strlen(FileName) + 1);
		strncat_s(TempLDR, _countof(TempLDR), LDR, strlen(LDR) + 1);

		strncpy_s(TempLRD, _countof(TempLRD), FileName, strlen(FileName) + 1);
		strncat_s(TempLRD, _countof(TempLRD), LRD, strlen(LRD) + 1);

		strncpy_s(TempFile, _countof(TempFile), FileName, strlen(FileName) + 1);
		strncat_s(TempFile, _countof(TempFile), level, strlen(level) + 1);

	#ifdef READABLE
		strncat_s(TempDLR, _countof(TempDLR), ExtendFileName, strlen(ExtendFileName) + 1);
		strncat_s(TempLDR, _countof(TempLDR), ExtendFileName, strlen(ExtendFileName) + 1);
		strncat_s(TempLRD, _countof(TempLRD), ExtendFileName, strlen(ExtendFileName) + 1);
		strncat_s(TempFile, _countof(TempFile), ExtendFileName, strlen(ExtendFileName) + 1);
	#endif
#else
		strncpy(TempDLR, FileName, strlen(FileName) + 1);
		strncat(TempDLR, DLR, strlen(DLR) + 1);

		strncpy(TempLDR, FileName, strlen(FileName) + 1);
		strncat(TempLDR, LDR, strlen(LDR) + 1);

		strncpy(TempLRD, FileName, strlen(FileName) + 1);
		strncat(TempLRD, LRD, strlen(LRD) + 1);

		strncpy(TempFile, FileName, strlen(FileName) + 1);
		strncat(TempFile, level, strlen(level) + 1);

	#ifdef READABLE
		strncat(TempDLR, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempLDR, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempLRD, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempFile, ExtendFileName, strlen(ExtendFileName) + 1);
	#endif
#endif

		const unsigned char FullDLRLen = (unsigned char)strlen(TempDLR) + 1;
		const unsigned char FullLDRLen = (unsigned char)strlen(TempLDR) + 1;
		const unsigned char FullLRDLen = (unsigned char)strlen(TempLRD) + 1;
		const unsigned char FullFileNameLen = (unsigned char)strlen(TempFile) + 1;

		BinaryTree->DLRFileName = (char *)malloc(FullDLRLen);
		BinaryTree->LDRFileName = (char *)malloc(FullLDRLen);
		BinaryTree->LRDFileName = (char *)malloc(FullLRDLen);
		BinaryTree->FileName = (char *)malloc(FullFileNameLen);

		// if (BinaryTree->DLRFileName == NULL || BinaryTree->LDRFileName == NULL || BinaryTree->LRDFileName == NULL || BinaryTree->FileName == NULL)
		if (!BinaryTree->DLRFileName || !BinaryTree->LDRFileName || !BinaryTree->LRDFileName || !BinaryTree->FileName)
			UnusualToExit(MemoryNotEnough, NULL);

#ifdef WINDOWS_VISUALSTUDIO
		_memccpy(BinaryTree->DLRFileName, TempDLR, 0, FullDLRLen);
		_memccpy(BinaryTree->LDRFileName, TempLDR, 0, FullLDRLen);
		_memccpy(BinaryTree->LRDFileName, TempLRD, 0, FullLRDLen);
		_memccpy(BinaryTree->FileName, TempFile, 0, FullFileNameLen);
#else
		memccpy(BinaryTree->DLRFileName, TempDLR, 0, FullDLRLen);
		memccpy(BinaryTree->LDRFileName, TempLDR, 0, FullLDRLen);
		memccpy(BinaryTree->LRDFileName, TempLRD, 0, FullLRDLen);
		memccpy(BinaryTree->FileName, TempFile, 0, FullFileNameLen);
#endif
	}
}

void DestroyBinaryTree(Tree * const BinaryTree)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
		UnusualToExit(NullPointer, NULL);

	DeleteAllNodes(BinaryTree->Root);
	BinaryTree->Root = NULL;
	BinaryTree->Size = BinaryTree->MaxSize = 0;
	free(BinaryTree->DLRFileName);
	free(BinaryTree->LDRFileName);
	free(BinaryTree->LRDFileName);
	free(BinaryTree->FileName);
	BinaryTree->DLRFileName = BinaryTree->LDRFileName = BinaryTree->LRDFileName = BinaryTree->FileName = NULL;
}

const bool BinaryTreeIsEmpty(const Tree * const BinaryTree)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, "%s", NullPointer);
		_getch();
#else
		fprintf(stderr, "%s", NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	return BinaryTree->Size == 0;
}

const bool BinaryTreeIsFull(const Tree * const BinaryTree)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, "%s", NullPointer);
		_getch();
#else
		fprintf(stderr, "%s", NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	return BinaryTree->Size == BinaryTree->MaxSize;
}

// 定位BinaryTree树中的pi位置
Pair SearchItemOfBinaryTree(const Tree * const BinaryTree, const TreeItem * const pi)
{
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, "%s", NullPointer);
		_getch();
#else
		fprintf(stderr, "%s", NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	Pair result = { NULL, BinaryTree->Root }; // 初始指向根

	// if (BinaryTree->Size == 0)
	if (!BinaryTree->Size) // 空树
		return result;

	// while (result.Child != NULL)
	while (result.Child) // 当前结点非空
	{
		if (pi->KeyValue < result.Child->Item.KeyValue)
		{
			result.Parent = result.Child;
			result.Child = result.Child->Left;
		}

		else if (pi->KeyValue > result.Child->Item.KeyValue)
		{
			result.Parent = result.Child;
			result.Child = result.Child->Right;
		}

		// if (pi->KeyValue == result.Child->Item.KeyValue)
		else // 若前两种情况均不满足,必定为当前结点与*pi相等
			break;
	}

	return result;
}

void AddNodeOfBinaryTree(Tree * const BinaryTree, const TreeItem * const pi)
{
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);
		
	// if (pi->KeyValue == 0)
	if (!pi->KeyValue) // 因为在二叉树里的数据0被认为是NULL故不能为0
		return;

	if (BinaryTree->Size == BinaryTree->MaxSize) // 结点数已至最大值
		UnusualToExit(FullTree, NULL);

#ifndef AVL
	Pair result = SearchItemOfBinaryTree(BinaryTree, pi);

	// if (result.Child != NULL)
	if (result.Child) // 若二叉树中已有*pi
		UnusualToExit(SameTreeItem, NULL);
#endif

#ifdef BACKWARD_POINTER
	AddNodeWithBackwardPointer(&BinaryTree->Root, pi, NULL);
#else
	AddNodeWithoutBackwardPointer(&BinaryTree->Root, pi);
#endif
	++BinaryTree->Size;
}

void DeleteNodeOfBinaryTree(Tree * const BinaryTree, TreeItem * const pi)
{
#ifdef AVL
	UnusualToExit("将程序微调区内的AVL设为关\n", NULL);
#else
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);

	Pair result = SearchItemOfBinaryTree(BinaryTree, pi);

	// if (result.Child == NULL)
	if (!result.Child) // 二叉树中不存在该结点
		UnusualToExit(NoTreeItem, NULL);

	// if (result.Child->Left != NULL && result.Child->Right != NULL)
	if (result.Child->Left && result.Child->Right) // 若欲删结点有两个子结点
	{
		TreeNode* q;

		// 以下2选1

		// 方法1
		// for (q = result.Child->Right; q->Left != NULL; q = q->Left) 本行为注释
		for (q = result.Child->Right; q->Left; q = q->Left)

		// 方法2
		// for (q = result.Child->Left; q->Right != NULL; q = q->Right) 本行为注释
		// for (q = result.Child->Left; q->Right; q = q->Right)
			;
	#ifdef BACKWARD_POINTER
		if (q->Item.KeyValue < q->Father->Item.KeyValue)
			q->Father->Left = NULL;

		// if (q->Item.KeyValue > q->Father->Item.KeyValue)
		else
			q->Father->Right = NULL;

		q->Father = result.Parent;
	#endif
		// if (result.Parent != NULL)
		if (result.Parent) // 欲删除的结点非根结点
		{
			if (result.Parent->Item.KeyValue > result.Child->Item.KeyValue)
				result.Parent->Left = q;

			// if (result.Parent->Item.KeyValue < result.Child->Item.KeyValue)
			else
				result.Parent->Right = q;
		}

		// if (result.Parent == NULL)
		else // 欲删除的结点为根结点
			BinaryTree->Root = q;

		q->Left = result.Child->Left;
		q->Right = result.Child->Right;

	#ifdef BACKWARD_POINTER
		result.Child->Left->Father = q;
		result.Child->Right->Father = q;
	#endif
	}

	// else if (result.Child->Left == NULL && result.Child->Right == NULL)
	else if (!result.Child->Left && !result.Child->Right) // 若欲删除结点无子结点
	{
		// if (result.Parent != NULL)
		if (result.Parent) // 若欲删除结点非根结点
		{
			if (result.Child->Item.KeyValue < result.Parent->Item.KeyValue)
				result.Parent->Left = NULL;

			// if (result.Child->Item.KeyValue > result.Parent->Item.KeyValue)
			else
				result.Parent->Right = NULL;
		}

		// if (result.Parent == NULL)
		else // 若欲除删除结点为根结点 即二叉树仅一个结点
		{
			BinaryTree->Root = NULL;
		}
	}

	else // 若欲删除结点仅一个子结点
	{
		// if (result.Child->Left != NULL)
		if (result.Child->Left) // 若欲删除结点仅一个左子结点
		{
			// if (result.Parent != NULL)
			if (result.Parent) // 若欲删除结点非根结点
			{

	#ifdef BACKWARD_POINTER
				result.Child->Left->Father = result.Parent;
	#endif
				if (result.Child->Item.KeyValue < result.Parent->Item.KeyValue)
					result.Parent->Left = result.Child->Left;
				// if (result.Child->Item.KeyValue > result.Parent->Item.KeyValue)
				else
					result.Parent->Right = result.Child->Left;
			}
			// if (result.Parent == NULL)
			else // 若欲删除结点为根结点
			{
	#ifdef BACKWARD_POINTER
				result.Child->Left->Father = NULL;
	#endif
				BinaryTree->Root = result.Child->Left;
			}
		}

		// if (result.chile->Right != NULL)
		else // 若欲删除结点仅一个右子结点
		{
			// if (result.Parent != NULL)
			if (result.Parent) // 若欲删除结点非根结点
			{
	#ifdef BACKWARD_POINTER
				result.Child->Right->Father = result.Parent;
	#endif
				if (result.Child->Item.KeyValue < result.Parent->Item.KeyValue)
					result.Parent->Left = result.Child->Right;
				// if (result.Child->Item.KeyValue > result.Parent->Item.KeyValue)
				else
					result.Parent->Right = result.Child->Right;
			}
			// if (result.Parent == NULL)
			else // 若欲除删除结点为根结点
			{
	#ifdef BACKWARD_POINTER
				result.Child->Right->Father = NULL;
	#endif
				BinaryTree->Root = result.Child->Right;
			}
		}
	}

	free(result.Child);
	--BinaryTree->Size;
#endif
}

// 文件输入/输出操作
void FileOperationWithBinaryTree(Tree * const BinaryTree, const char * const Mode)
{
	// if (BinaryTree == NULL || Mode == NULL)
	if (!BinaryTree || !Mode)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->FileName != NULL)
	if (BinaryTree->FileName)
	{
		// if (strcmp(Mode, WRITE) == 0)
		if (!strcmp(Mode, WRITE))
		{
#ifdef READABLE
			MoreFileOperationByBinaryTree(BinaryTree, BinaryTree->DLRFileName, Mode);
			MoreFileOperationByBinaryTree(BinaryTree, BinaryTree->LDRFileName, Mode);
			MoreFileOperationByBinaryTree(BinaryTree, BinaryTree->LRDFileName, Mode);
#endif
		}
		MoreFileOperationByBinaryTree(BinaryTree, BinaryTree->FileName, Mode);
	}
}

// 键盘输入
void InputBinaryTreeFromKeyboard(Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	if (Stream == stdin)
	{
#ifdef STDIN
	#ifdef WINDOWS_VISUALSTUDIO
		printf(STDIN, 'z');
	#else
		printf(STDIN, 'd');
	#endif
#endif
	}

	TreeItem temp;

	// while (feof(Stream) == 0)
	while (!feof(Stream))
	{
#ifdef WINDOWS_VISUALSTUDIO
		if (fscanf_s(Stream, INPUT_FORMAT) != NUMBER_OF_FORMAT)
#else
		if (fscanf(Stream, INPUT_FORMAT) != NUMBER_OF_FORMAT)
#endif
			UnusualToExit(InputError, NULL);

		// if (temp.KeyValue == 0)
		if (!temp.KeyValue)
			continue;

		AddNodeOfBinaryTree(BinaryTree, &temp);
	}
}

void OutputBinaryTreeToScreen(const Tree * const BinaryTree, FILE * const Stream, const char * const Str)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->DLRFileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->DLRFileName))))
	{
		// 以下3选1

		// 方法1
		// PreOrderTraversal(BinaryTree, Stream);

		// 方法2
		Traversal(PreOrderTraversal, BinaryTree, Stream);

		// 方法3
		// void(*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = PreOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->LDRFileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->LDRFileName))))
	{
		// 以下3选1

		// 方法1
		// InOrderTraversal(BinaryTree, Stream);

		// 方法2
		Traversal(InOrderTraversal, BinaryTree, Stream);

		// 方法3
		// void (*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = InOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->LRDFileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->LRDFileName))))
	{
		// 以下3选1

		// 方法1
		// PostOrderTraversal(BinaryTree, Stream);

		// 方法2
		Traversal(PostOrderTraversal, BinaryTree, Stream);

		// 方法3
		// void (*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = PostOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->FileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->FileName))))
	{
		// 以下3选1

		// 方法1
		// LevelOrderTraversal(BinaryTree, Stream);

		// 方法2
		Traversal(LevelOrderTraversal, BinaryTree, Stream);

		// 方法3
		// void (*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = LevelOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}
}

void GetMinNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const Item)
{
	// if (BinaryTree == NULL || Item == NULL)
	if (!BinaryTree || !Item)
		UnusualToExit(NullPointer, NULL);

	const TreeNode * pt = BinaryTree->Root;

	// if (pt == NULL)
	if (!pt) // 空树
		UnusualToExit(EmptyTree, NULL);

	// while (pt->Left != NULL)
	while (pt->Left)
		pt = pt->Left;
	* Item = pt->Item;
}

void GetMaxNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const Item)
{
	// if (BinaryTree == NULL || Item == NULL)
	if (!BinaryTree || !Item)
		UnusualToExit(NullPointer, NULL);

	const TreeNode * pt = BinaryTree->Root;

	// if (pt == NULL)
	if (!pt) // 空树
		UnusualToExit(EmptyTree, NULL);

	// while (pt->Right != NULL)
	while (pt->Right)
		pt = pt->Right;
	* Item = pt->Item;
}

void UnusualToExit(const char * const Str, const char * const FileName)
{
	// if (Str == NULL)
	if (!Str)
		UnusualToExit(NullPointer, NULL);

#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(stderr, Str, FileName);
	_getch();
#else
	fprintf(stderr, Str, FileName);
#endif
	exit(EXIT_FAILURE); // exit (1);
}

/********************************私有函数********************************/

static void DeleteAllNodes(TreeNode * const Root)
{
	// if (Root != NULL)
	if (Root)
	{
		TreeNode * const assist = Root->Right;
		DeleteAllNodes(Root->Left);
		free(Root);
		DeleteAllNodes(assist);
	}
}

#ifdef BACKWARD_POINTER
static void AddNodeWithBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi, TreeNode *Father)
{
	TreeNode *t = *ptr;

	// if (t == NULL)
	if (!t) // 空树
	{
		t = *ptr = (TreeNode *)malloc(sizeof(TreeNode));

		// if (t!= NULL)
		if (t)
		{
			t->Item = *pi;
			t->Father = Father;
			t->Left = t->Right = NULL;
		}

		// if (t == NULL)
		else
			UnusualToExit(MemoryNotEnough, NULL);
	}

	// 非空树
	// if (t != NULL)
	else if (pi->KeyValue < t->Item.KeyValue) // 若新元素 < 子树根
	{
		AddNodeWithBackwardPointer(&t->Left, pi, t); // 往左子树上插
	#ifdef AVL
		if (GetTreeHeight(t->Left) - GetTreeHeight(t->Right) == 2)
		{
			if (pi->KeyValue < t->Left->Item.KeyValue)
				RotateWithLeftChild(ptr); // 右单转

			// if (pi->KeyValue > t->Left->Item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->Item.KeyValue) // 若新元素 > 子树根
	{
		AddNodeWithBackwardPointer(&t->Right, pi, t); // 往右子树上插
	#ifdef AVL
		if (GetTreeHeight(t->Right) - GetTreeHeight(t->Left) == 2)
		{
			if (pi->KeyValue > t->Right->Item.KeyValue)
				RotateWithRightChild(ptr); // 左单转

			// if (pi->KeyValue < t->Right->Item.KeyValue)
			else
				DoubleWithRightChild(ptr); // 左转,后右转
		}
	#endif
	}

	else
		UnusualToExit(SameTreeItem, NULL); // 树中已有该结点
	#ifdef AVL
		t->Height = GetMax(GetTreeHeight(t->Left), GetTreeHeight(t->Right)) + 1;
	#endif
}

#else

static void AddNodeWithoutBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi)
{
	TreeNode * t = * ptr;

	// if (t == NULL)
	if (!t) // 空树
	{
		t = * ptr = (TreeNode *)malloc(sizeof(TreeNode));

		// if (t!= NULL)
		if (t)
		{
			t->Item = *pi;
			t->Left = t->Right = NULL;
		}

		// if (t == NULL)
		else
			UnusualToExit(MemoryNotEnough, NULL);
	}

	// 非空树
	// if (t != NULL)
	else if (pi->KeyValue < t->Item.KeyValue) // 若新元素 < 子树根
	{
		AddNodeWithoutBackwardPointer(&t->Left, pi); // 往左子树上插
	#ifdef AVL
		if (GetTreeHeight(t->Left) - GetTreeHeight(t->Right) == 2)
		{
			if (pi->KeyValue < t->Left->Item.KeyValue)
				RotateWithLeftChild(ptr); // 右单转

			// if (pi->KeyValue > t->Left->Item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->Item.KeyValue) // 若新元素 > 子树根
	{
		AddNodeWithoutBackwardPointer(&t->Right, pi); // 往右子树上插
	#ifdef AVL
		if (GetTreeHeight(t->Right) - GetTreeHeight(t->Left) == 2)
		{
			if (pi->KeyValue > t->Right->Item.KeyValue)
				RotateWithRightChild(ptr); // 左单转

			// if (pi->KeyValue < t->Right->Item.KeyValue)
			else
				DoubleWithRightChild(ptr); // 左转,后右转
		}
	#endif
	}

	else
		; // 树中已有该结点
	#ifdef AVL
		t->Height = GetMax(GetTreeHeight(t->Left), GetTreeHeight(t->Right)) + 1;
	#endif
}
#endif

static void MoreFileOperationByBinaryTree(Tree * const BinaryTree, const char * const FileName, const char * const Mode)
{
	// if (BinaryTree == NULL || Mode == NULL)
	if (!BinaryTree || !Mode)
		UnusualToExit(NullPointer, NULL);

#ifdef WINDOWS_VISUALSTUDIO
	FILE * FilePointer;
	const errno_t error = fopen_s(&FilePointer, FileName, Mode);

	// if (error != 0)
	if (error)
#else
	FILE * const restrict FilePointer = fopen(FileName, Mode);

	// if (FilePointer == NULL)
	if (!FilePointer)
#endif
		UnusualToExit(OpenFileError, FileName);

	// if (strcmp(Mode, WRITE) == 0)
	if (!strcmp(Mode, WRITE)) // 文件输出
#ifdef READABLE
		OutputBinaryTreeToScreen(BinaryTree, FilePointer, FileName); // 输出为文本文件
#else
		OutputBinaryTreeToBinaryFile(BinaryTree, FilePointer); // 输出为二进制文件
#endif

	// if (strcmp(Mode, READ) == 0)
	if (!strcmp(Mode, READ)) // 文件输入
#ifdef READABLE
		InputBinaryTreeFromKeyboard(BinaryTree, FilePointer); // 从文本文件输入
#else
		InputBinaryTreeFromBinaryFile(BinaryTree, FilePointer); // 从二进制文件输入
#endif

	// if (ferror(FilePointer) != 0)
	if (ferror(FilePointer))
		UnusualToExit(FileOperationError, FileName);

#ifdef WINDOWS_VISUALSTUDIO
	// if (FilePointer != NULL)
	if (FilePointer)
#endif
		// if (fclose(FilePointer) != 0)
		if (fclose(FilePointer))
			UnusualToExit(CloseFileError, FileName);
}

#ifndef READABLE
static void OutputBinaryTreeToBinaryFile(Tree * const BinaryTree, FILE * const FilePointer)
{
	// if (BinaryTree == NULL || FilePointer == NULL)
	if (!BinaryTree || !FilePointer)
		UnusualToExit(NullPointer, NULL);

	TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));

	// if (buffer == NULL)
	if (!buffer)
		UnusualToExit(MemoryNotEnough, NULL);

	// if (BinaryTree->Root != NULL) 
	if (BinaryTree->Root)
	{
		LinkList Link;
		CreateQueue(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), NULL);
		Enqueue(&Link, BinaryTree->Root); // 入队
		LinkItem temp;
		ElemNumb Size = 0, n = 2;
		TreeNode NullItem = {
								{ 0 },
#ifdef BACKWARD_POINTER
								NULL,
#endif
								NULL,
								NULL,
#ifdef AVL
								0
#endif 
		};

		do
		{
			Dequeue(&Link, &temp); // 出队
			buffer[Size++].KeyValue = temp->Item.KeyValue;

			// if (temp->Left != NULL)
			if (temp->Left)
				Enqueue(&Link, temp->Left);

			// if (temp->Left == NULL)
			else
				Enqueue(&Link, &NullItem);

			// if (temp->Right != NULL)
			if (temp->Right)
				Enqueue(&Link, temp->Right);

			// if (temp->Right == NULL)
			else
				Enqueue(&Link, &NullItem);

			if (Link.Size == n) // 队列中元素数量为2的n次幂
				n <<= 1; // n = 2 * n;
		} // while (QueueIsAllNull(&Link) == false);
		while (!QueueIsAllNull(&Link));
		DestroyQueue(&Link);
		fwrite(buffer, sizeof(TreeItem), Size, FilePointer);
	}
	free(buffer);
}

static void InputBinaryTreeFromBinaryFile(Tree * const BinaryTree, FILE * const FilePointer)
{
	// if (BinaryTree == NULL || FilePointer == NULL)
	if (!BinaryTree || !FilePointer)
		UnusualToExit(NullPointer, NULL);

	TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));

	// if (buffer == NULL)
	if (!buffer)
		UnusualToExit(MemoryNotEnough, NULL);

	const ElemNumb Size = (ElemNumb)fread(buffer, sizeof(TreeItem), ((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1), FilePointer);
	if (Size > 0)
	{
		ElemNumb i;
		for (i = 0; i < Size; ++i)
			AddNodeOfBinaryTree(BinaryTree, &buffer[i]);
	}
	free(buffer);
}
#endif

// 前序遍历
static void PreOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// 非递归算法
	ArrayList S;
#ifdef LOG
	const char * const FileName = "前序遍历用到的堆栈操作.txt";
#else
	const char * const FileName = NULL;
#endif
	// 创建并初始化堆栈S
	CreateStack(&S, BinaryTree->Size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\n前序遍历 (根->左子->右子)\n");
#else
	fprintf(Stream, "\n前序遍历 (根->左子->右子)\n");
#endif
	const TreeNode * temp = BinaryTree->Root; // 初始T为树根地址
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( temp != NULL || S.Size != 0 )
	while (temp || S.Size)
	{
		// while (temp != NULL)
		while (temp) // 一直向左并将沿途结点压入堆栈
		{
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif	
			++sum;
			Push(&S, temp);
#ifdef LOG
			TextFileAppendOperationWithStack(&S);
#endif
			temp = temp->Left;
		}

		// if (S.Size != 0)
		if (S.Size)
		{
			Pop(&S, &TEMP); // 结点弹出堆栈
#ifdef LOG
			TextFileAppendOperationWithStack(&S);
#endif
			temp = TEMP.Right; // 转向右子树
		}
	}
	DestroyStack(&S);
}

// 中序遍历
static void InOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// 非递归算法
	ArrayList S;
#ifdef LOG
	const char* const FileName = "中序遍历用到的堆栈操作.txt";
#else
	const char * const FileName = NULL;
#endif
	// 创建并初始化堆栈S
	CreateStack(&S, BinaryTree->Size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\n中序遍历 (左子->根->右子)\n");
#else
	fprintf(Stream, "\n中序遍历 (左子->根->右子)\n");
#endif
	const TreeNode * T = BinaryTree->Root;
	const TreeNode * temp;
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( T != NULL || S.Size != 0 )
	while (T || S.Size)
	{
		// while (T != NULL)
		while (T) // 一直向左并将沿途结点压入堆栈
		{
			Push(&S, T);
#ifdef LOG
			TextFileAppendOperationWithStack(&S);
#endif
			T = T->Left;
		}

		// if (S.Size != 0)
		if (S.Size)
		{
			Pop(&S, &TEMP); // 结点弹出堆栈
#ifdef LOG
			TextFileAppendOperationWithStack(&S);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
			++sum;
			T = temp->Right; // 转向右子树
		}
	}
	DestroyStack(&S);
}

// 后序遍历
static void PostOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->Size != 0)
	if (BinaryTree->Size)
	{
		// 非递归算法
		// 创建并初始化堆栈S Q
		ArrayList S;
		CreateStack(&S, BinaryTree->Size, NULL);
#ifdef LOG
		const char * const FileName = "后序遍历用到的堆栈操作.txt";
#else
		const char * const FileName = NULL;
#endif
		ArrayList Q;
		CreateStack(&Q, BinaryTree->Size, FileName); // 创建并初始化堆栈Q，用于反向输出
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(Stream, "\n后序遍历 (左子->右子->根)\n");
#else
		fprintf(Stream, "\n后序遍历 (左子->右子->根)\n");
#endif
		const TreeNode * T = BinaryTree->Root;
		TreeNode TEMP;
		const TreeNode * temp;
		ElemNumb sum = 0;

		// while ( T != NULL || S.Size != 0 )
		while (T || S.Size)
		{
			// while (T != NULL)
			while (T) // 一直向右并将沿途结点压入堆栈
			{
				Push(&S, T);
				Push(&Q, T); // 将遍历到的结点压栈，用于反向
#ifdef LOG
				TextFileAppendOperationWithStack(&Q);
#endif
				T = T->Right;
			}

			// if (S.Size != 0)
			if (S.Size)
			{
				Pop(&S, &TEMP); // 结点弹出堆栈
				T = TEMP.Left; // 转向左子树
			}
		}

		// while (Q.Size != 0)
		while (Q.Size)
		{
			Pop(&Q, &TEMP);
#ifdef LOG
			TextFileAppendOperationWithStack(&Q);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
			++sum;
		}
		DestroyStack(&S);
		DestroyStack(&Q);
	}
}

// 层序遍历
static void LevelOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->Size != 0)
	if (BinaryTree->Size)
	{
		if (Stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stdout, "\n层序遍历 (自上而下 从左至右)");
#else
			fprintf(stdout, "\n层序遍历 (自上而下 从左至右)");
#endif
		fputs("\n", Stream);
		LinkList Link;
		CreateQueue(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), QueueFileName);
		Enqueue(&Link, BinaryTree->Root); // 入队
#ifdef LOG
		TextFileAppendOperationWithQueue(&Link);
#endif
		LinkItem temp;
		ElemNumb n = 2;
		TreeNode NullItem = {
								{ 0 },
#ifdef BACKWARD_POINTER
									NULL,
#endif
									NULL,
									NULL,
#ifdef AVL
									0
#endif
		};
		do
		{
			Dequeue(&Link, &temp); // 出队
#ifdef LOG
			TextFileAppendOperationWithQueue(&Link);
#endif
			if (Stream == stdout)
			{
				// if (temp->Item.KeyValue != 0)
				if (temp->Item.KeyValue)
#ifdef WINDOWS_VISUALSTUDIO
					fprintf_s(stdout, "0x%p\t", &temp->Item);
#else
					fprintf(stdout, "%p\t", &temp->Item);
#endif

				// if (temp->Item.KeyValue == 0)
				else
					fputs("NULL\n", Stream);
			}

			// if (temp->Item.KeyValue != 0)
			if (temp->Item.KeyValue)
			{
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(Stream, OUTPUT_FORMAT, Stream == stdout ? '\t' : '\n');
#else
				fprintf(Stream, OUTPUT_FORMAT, Stream == stdout ? '\t' : '\n');
#endif
				// if (Stream == stdout)
				if (Stream == stdout)
				{
					// if (temp->Item.KeyValue != 0)
					if (temp->Item.KeyValue)
					{
#ifdef BACKWARD_POINTER
						fputs("父: ", stdout);

						// if (temp->Father != NULL)
						if (temp->Father)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p\t", temp->Father);
#else
							fprintf(stdout, "%p\t", temp->Father);
#endif
						// if (temp->Father == NULL)
						else
							fputs("NULL\t", stdout);
#endif

						fputs("左子: ", stdout);

						// if (temp->Left != NULL)
						if (temp->Left)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p", temp->Left);
#else
							fprintf(stdout, "%p", temp->Left);
#endif		

						// if (temp->Left == NULL)
						else
							fputs("NULL\t", stdout);
						fputs("  右子: ", stdout);

						// if (temp->Right != NULL)
						if (temp->Right)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p\n", temp->Right);
#else
							fprintf(stdout, "%p\n", temp->Right);
#endif

						// if (temp->Right == NULL)
						else
							fputs("NULL\n", stdout);
					}
				}
			}

			// if (temp->Item.KeyValue != 0)
			else if (Stream != stdout)
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(Stream, "%d\n", 0);
#else
				fprintf(Stream, "%d\n", 0);
#endif

			// if (temp->Left != NULL)
			if (temp->Left)
			{
				Enqueue(&Link, temp->Left);
#ifdef LOG
				TextFileAppendOperationWithQueue(&Link);
#endif
			}

			// if (temp->Left == NULL)
			else
			{
				Enqueue(&Link, &NullItem);
#ifdef LOG
				TextFileAppendOperationWithQueue(&Link);
#endif
			}

			// if (temp->Right != NULL)
			if (temp->Right)
			{
				Enqueue(&Link, temp->Right);
#ifdef LOG
				TextFileAppendOperationWithQueue(&Link);
#endif
			}

			// if (temp->Right == NULL)
			else
			{
				Enqueue(&Link, &NullItem);
#ifdef LOG
				TextFileAppendOperationWithQueue(&Link);
#endif
			}

			if (Link.Size == n) // 队列中元素数量为2的n次幂
				n <<= 1; // n = 2 * n;
		} // while (QueueIsAllNull(&Link) == false);
		while (!QueueIsAllNull(&Link));
		DestroyQueue(&Link);
	}

	if (Stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stdout, "\n当前共有%d个元素\n\n", BinaryTree->Size);
#else
		fprintf(stdout, "\n当前共有%d个元素\n\n", BinaryTree->Size);
#endif
}

#ifdef AVL

static void RotateWithLeftChild(TreeNode ** const k2pt)
{
	TreeNode * k1, * const k2 = * k2pt;
	k1 = k2->Left;
	k2->Left = k1->Right;
#ifdef BACKWARD_POINTER
	// if (k1->Right != NULL)
	if (k1->Right)
		k1->Right->Father = k2;
#endif
	k1->Right = k2;
#ifdef BACKWARD_POINTER
	k2->Father = k1;
#endif
	k2->Height = GetMax(GetTreeHeight(k2->Left), GetTreeHeight(k2->Right)) + 1;
	k1->Height = GetMax(GetTreeHeight(k1->Left), k2->Height) + 1;
#ifdef BACKWARD_POINTER
	k1->Father = (*k2pt)->Father;
#endif
	*k2pt = k1;
}

static void RotateWithRightChild(TreeNode ** const k2pt)
{
	TreeNode * k1, * const k2 = * k2pt;
	k1 = k2->Right;
	k2->Right = k1->Left;
#ifdef BACKWARD_POINTER
	// if (k1->Left != NULL)
	if (k1->Left)
		k1->Left->Father = k2;
#endif
	k1->Left = k2;
#ifdef BACKWARD_POINTER
	k2->Father = k1;
#endif
	k2->Height = GetMax(GetTreeHeight(k2->Left), GetTreeHeight(k2->Right)) + 1;
	k1->Height = GetMax(GetTreeHeight(k1->Right), k2->Height) + 1;
#ifdef BACKWARD_POINTER
	k1->Father = (* k2pt)->Father;
#endif
	* k2pt = k1;
}

static void DoubleWithLeftChild(TreeNode ** const k1pt)
{
	RotateWithRightChild(&(* k1pt)->Left);
	RotateWithLeftChild(k1pt);
}

static void DoubleWithRightChild(TreeNode ** const k1pt)
{
	RotateWithLeftChild(&(* k1pt)->Right);
	RotateWithRightChild(k1pt);
}

#endif

static void Traversal(void (* pf) (const Tree * const BinaryTree, FILE * const Stream), const Tree * const BinaryTree, FILE * const Stream)
{
	pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
}
