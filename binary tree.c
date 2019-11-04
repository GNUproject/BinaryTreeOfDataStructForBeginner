
// 二叉树
// binary tree.c

#include "binary tree.h"
#include "queue of binary tree.h"
#include "stack of binary tree.h"

#define GetMax(x,y)	((x)>(y)?(x):(y))
#define GetTreeHeight(t) ((t) != NULL ? (t)->height : -1)

#ifdef WINDOWS_VISUALSTUDIO
	static const char * const WhiteList = " !#$%&`()+,-.;=@{|}[]^_'{}~"; // 文件名特殊字符白名单
#else
	static const char * const WhiteList = " !\"#$%&`()*+,-./:;<=>\?@{|}[\\]^_\'{|}~"; // 文件名特殊字符白名单
#endif

#ifdef DEBUG
	#ifdef FILENAME_LIMIT
		static const char * const QueueFileName = "queue.txt";
	#else
		static const char * const QueueFileName = "队列操作.txt";
	#endif
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
const char * const FileNameTooLong = "文件名过长\n";
const char * const FileNameError = "文件名包含非法字符: %s\n";
const char * const MemoryNotEnough = "内存不足!\n";

#ifdef FILENAME_LIMIT
	static const char * const DLR = " with DLR"; // 前序遍历
	static const char * const LDR = " with LDR"; // 中序遍历
	static const char * const LRD = " with LRD"; // 后序遍历
	static const char * const level = " with LEVEL"; // 层序遍历
#else
	static const char * const DLR = "的前序遍历"; // 前序遍历
	static const char * const LDR = "的中序遍历"; // 中序遍历
	static const char * const LRD = "的后序遍历"; // 后序遍历
	static const char * const level = "的层序遍历"; // 层序遍历
#endif

static const char * const EmptyTree = "空树\n";
static const char * const FullTree = "已至数量最大值 请扩充Max或ElemNumb数据单位!\n";
static const char * const LengthError = "二叉树结点数非法\n";

#ifdef AVL_BINARY_TREE
	static void RotateWithLeftChild(TreeNode ** const k2pt);
	static void RotateWithRightChild(TreeNode ** const k2pt);
	static void DoubleWithLeftChild(TreeNode ** const k1pt);
	static void DoubleWithRightChild(TreeNode ** const k1pt);
#endif

#ifdef BACKWARD_POINTER
	static void AddNodeWithBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi, TreeNode *father);
#else
	static void AddNodeWithoutBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi);
#endif

#ifdef CAN_OPEN_FILE
	static const char * const ExtendFileName = ".txt";
#else
	static void OutputBinaryTreeToBinaryFile(Tree * const BinaryTree, FILE * const FilePointer);
	static void InputBinaryTreeFromBinaryFile(Tree * const BinaryTree, FILE * const FilePointer);
#endif

static void DeleteAllNodes(TreeNode * const root);
static void MoreFileOperationByBinaryTree(Tree * const BinaryTree, const char * const FileName, const char * const Mode);
static void PreOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void InOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void PostOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void LevelOrderTraversal(const Tree * const BinaryTree, FILE * const Stream);
static void Traversal(void (*pf) (const Tree * const BinaryTree, FILE * const Stream), const Tree * const BinaryTree, FILE * const Stream);

extern void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName);
extern void DestroyListByArray(ArrayList * const Array);
extern void Push(ArrayList * const Array, const ArrayItem * const NewItem);
extern void Pop(ArrayList * const Array, ArrayItem * const DelItem);
extern void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);
extern void DestroyListByLink(LinkList * const Link);
extern void EnQueue(LinkList * const Link, const LinkItem NewItem);
extern void DeQueue(LinkList * const Link, LinkItem * const DelItem);

void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max, const char * const FileName)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
		UnusualToExit(NullPointer, NULL);
		
	if (Max <= 0)
		UnusualToExit(LengthError, NULL);

	BinaryTree->root = NULL;
	BinaryTree->size = 0;
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

	#ifdef CAN_OPEN_FILE
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

	#ifdef CAN_OPEN_FILE
		strncat(TempDLR, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempLDR, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempLRD, ExtendFileName, strlen(ExtendFileName) + 1);
		strncat(TempFile, ExtendFileName, strlen(ExtendFileName) + 1);
	#endif
#endif

#ifdef FILENAME_LIMIT
		CheckFileName(TempDLR);
		CheckFileName(TempLDR);
		CheckFileName(TempLRD);
		CheckFileName(TempFile);
#endif

		const unsigned char FullDLRLen = (unsigned char)strlen(TempDLR) + 1;
		const unsigned char FullLDRLen = (unsigned char)strlen(TempLDR) + 1;
		const unsigned char FullLRDLen = (unsigned char)strlen(TempLRD) + 1;
		const unsigned char FullFileNameLen = (unsigned char)strlen(TempFile) + 1;

		BinaryTree->DLRFileName = (char *)malloc(FullDLRLen);
		BinaryTree->LDRFileName = (char *)malloc(FullLDRLen);
		BinaryTree->LRDFileName = (char *)malloc(FullLRDLen);
		BinaryTree->FileName = (char *)malloc(FullFileNameLen);

		// if (BinaryTree->DLRFileName == NULL || BinaryTree->LDRFileName == NULL || BinaryTree->LRDFileName == NULL && BinaryTree->FileName == NULL)
		if (!BinaryTree->DLRFileName || !BinaryTree->LDRFileName || !BinaryTree->LRDFileName && !BinaryTree->FileName)
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

	DeleteAllNodes(BinaryTree->root);
	BinaryTree->root = NULL;
	BinaryTree->size = BinaryTree->MaxSize = 0;
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
		fprintf_s(stderr, NullPointer);
		_getch();
#else
		fprintf(stderr, NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	return BinaryTree->size == 0;
}

const bool BinaryTreeIsFull(const Tree * const BinaryTree)
{
	// if (BinaryTree == NULL)
	if (!BinaryTree)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer);
		_getch();
#else
		fprintf(stderr, NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	return BinaryTree->size == BinaryTree->MaxSize;
}

// 定位BinaryTree树中的pi位置
Pair SearchBinaryTreeItem(const Tree * const BinaryTree, const TreeItem * const pi)
{
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer);
		_getch();
#else
		fprintf(stderr, NullPointer);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	Pair result = { NULL, BinaryTree->root }; // 初始指向根

	// if (BinaryTree->size == 0)
	if (!BinaryTree->size) // 空树
		return result;

	// while (result.child != NULL)
	while (result.child) // 当前结点非空
	{
		if (pi->KeyValue < result.child->item.KeyValue)
		{
			result.parent = result.child;
			result.child = result.child->left;
		}

		else if (pi->KeyValue > result.child->item.KeyValue)
		{
			result.parent = result.child;
			result.child = result.child->right;
		}

		// if (pi->KeyValue == result.child->item.KeyValue)
		else // 若前两种情况均不满足,必定为当前结点与*pi相等
			break;
	}

	return result;
}

void AddBinaryTreeNode(Tree * const BinaryTree, const TreeItem * const pi)
{
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);
		
	// if (pi->KeyValue == 0)
	if (!pi->KeyValue) // 因为在二叉树里的数据0被认为是NULL故不能为0
		return;

	if (BinaryTree->size == BinaryTree->MaxSize) // 结点数已至最大值
		UnusualToExit(FullTree, NULL);

#ifndef AVL_BINARY_TREE
	Pair result = SearchBinaryTreeItem(BinaryTree, pi);

	// if (result.child != NULL)
	// if (result.child != NULL)
	if (result.child) // 若二叉树中已有*pi
		UnusualToExit(SameTreeItem, NULL);
#endif

#ifdef BACKWARD_POINTER
	AddNodeWithBackwardPointer(&BinaryTree->root, pi, NULL);
#else
	AddNodeWithoutBackwardPointer(&BinaryTree->root, pi);
#endif
	++BinaryTree->size;
}

void DelBinaryTreeNode(Tree * const BinaryTree, TreeItem * const pi)
{
#ifdef AVL_BINARY_TREE
	UnusualToExit("将程序微调区内的AVL_BINARY_TREE设为关\n", NULL);
#else
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);

	Pair result = SearchBinaryTreeItem(BinaryTree, pi);

	// if (result.child == NULL)
	if (!result.child) // 二叉树中不存在该结点
		UnusualToExit(NoTreeItem, NULL);

	// if (result.child->left != NULL && result.child->right != NULL)
	if (result.child->left && result.child->right) // 若欲删结点有两个子结点
	{
		TreeNode* q;

		// 以下2选1

		// 方法1
		// for (q = result.child->right; q->left != NULL; q = q->left) 本行为注释
		for (q = result.child->right; q->left; q = q->left)

			// 方法2
			// for (q = result.child->left; q->right != NULL; q = q->right) 本行为注释
			// for (q = result.child->left; q->right; q = q->right)
			;
	#ifdef BACKWARD_POINTER
		if (q->item.KeyValue < q->father->item.KeyValue)
			q->father->left = NULL;

		// if (q->item.KeyValue > q->father->item.KeyValue)
		else
			q->father->right = NULL;

		q->father = result.parent;
	#endif
		// if (result.parent != NULL)
		if (result.parent) // 欲删除的结点非根结点
		{
			if (result.parent->item.KeyValue > result.child->item.KeyValue)
				result.parent->left = q;

			// if (result.parent->item.KeyValue < result.child->item.KeyValue)
			else
				result.parent->right = q;
		}

		// if (result.parent == NULL)
		else // 欲删除的结点为根结点
			BinaryTree->root = q;

		q->left = result.child->left;
		q->right = result.child->right;

	#ifdef BACKWARD_POINTER
		result.child->left->father = q;
		result.child->right->father = q;
	#endif
	}

	// else if (result.child->left == NULL && result.child->right == NULL)
	else if (!result.child->left && !result.child->right) // 若欲删除结点无子结点
	{
		// if (result.parent != NULL)
		if (result.parent) // 若欲删除结点非根结点
		{
			if (result.child->item.KeyValue < result.parent->item.KeyValue)
				result.parent->left = NULL;

			// if (result.child->item.KeyValue > result.parent->item.KeyValue)
			else
				result.parent->right = NULL;
		}

		// if (result.parent == NULL)
		else // 若欲除删除结点为根结点 即二叉树仅一个结点
		{
			BinaryTree->root = NULL;
		}
	}

	else // 若欲删除结点仅一个子结点
	{
		// if (result.child->left != NULL)
		if (result.child->left) // 若欲删除结点仅一个左子结点
		{
			// if (result.parent != NULL)
			if (result.parent) // 若欲删除结点非根结点
			{

	#ifdef BACKWARD_POINTER
				result.child->left->father = result.parent;
	#endif
				if (result.child->item.KeyValue < result.parent->item.KeyValue)
					result.parent->left = result.child->left;
				// if (result.child->item.KeyValue > result.parent->item.KeyValue)
				else
					result.parent->right = result.child->left;
			}
			// if (result.parent == NULL)
			else // 若欲删除结点为根结点
			{
	#ifdef BACKWARD_POINTER
				result.child->left->father = NULL;
	#endif
				BinaryTree->root = result.child->left;
			}
		}

		// if (result.chile->right != NULL)
		else // 若欲删除结点仅一个右子结点
		{
			// if (result.parent != NULL)
			if (result.parent) // 若欲删除结点非根结点
			{
	#ifdef BACKWARD_POINTER
				result.child->right->father = result.parent;
	#endif
				if (result.child->item.KeyValue < result.parent->item.KeyValue)
					result.parent->left = result.child->right;
				// if (result.child->item.KeyValue > result.parent->item.KeyValue)
				else
					result.parent->right = result.child->right;
			}
			// if (result.parent == NULL)
			else // 若欲除删除结点为根结点
			{
	#ifdef BACKWARD_POINTER
				result.child->right->father = NULL;
	#endif
				BinaryTree->root = result.child->right;
			}
		}
	}

	free(result.child);
	--BinaryTree->size;
#endif
}

// 文件输入/输出操作
void FileOperationByBinaryTree(Tree * const BinaryTree, const char * const Mode)
{
	// if (BinaryTree == NULL || Mode == NULL)
	if (!BinaryTree || !Mode)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->FileName != NULL)
	if (BinaryTree->FileName)
	{
		// if (strcmp(Mode, WRITE == 0)
		if (!strcmp(Mode, WRITE))
		{
#ifdef CAN_OPEN_FILE
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
#ifdef WINDOWS_VISUALSTUDIO
	#ifdef STDIN
		printf(STDIN, 'z');
	#endif
#else
	#ifdef STDIN
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

		AddBinaryTreeNode(BinaryTree, &temp);
	}
}

void OutputBinaryTreeToMonitor(const Tree * const BinaryTree, FILE * const Stream, const char * const Str)
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

void GetMinOfBinaryTree(const Tree * const BinaryTree, TreeItem * const item)
{
	// if (BinaryTree == NULL || item == NULL)
	if (!BinaryTree || !item)
		UnusualToExit(NullPointer, NULL);

	const TreeNode * pt = BinaryTree->root;

	// if (pt == NULL)
	if (!pt) // 空树
		UnusualToExit(EmptyTree, NULL);

	// while (pt->left != NULL)
	while (pt->left)
		pt = pt->left;
	* item = pt->item;
}

void GetMaxOfBinaryTree(const Tree * const BinaryTree, TreeItem * const item)
{
	// if (BinaryTree == NULL || item == NULL)
	if (!BinaryTree || !item)
		UnusualToExit(NullPointer, NULL);

	const TreeNode * pt = BinaryTree->root;

	// if (pt == NULL)
	if (!pt) // 空树
		UnusualToExit(EmptyTree, NULL);

	// while (pt->right != NULL)
	while (pt->right)
		pt = pt->right;
	* item = pt->item;
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

#ifdef FILENAME_LIMIT
void CheckFileName(const char * const FullFileName)
{
	// if (FullFileName == NULL)
	if (!FullFileName)
		UnusualToExit(NullPointer, NULL);

	const unsigned char count = (unsigned char)strlen(FullFileName);

	if (count >= LEN)
		UnusualToExit(FileNameTooLong, NULL);

	unsigned char i;
	for (i = 0; i < count; ++i)

		// if (isalnum(FullFileName[i]) == 0 && strrchr(WhiteList, FullFileName[i]) == NULL)
		if (!isalnum(FullFileName[i]) && !strrchr(WhiteList, FullFileName[i]))
		{
			char ErrorChar[2] = { FullFileName[i],  0 };
			UnusualToExit(FileNameError, ErrorChar);
		}
}
#endif

/********************************私有函数********************************/

static void DeleteAllNodes(TreeNode * const root)
{
	// if (root != NULL)
	if (root)
	{
		TreeNode * const assist = root->right;
		DeleteAllNodes(root->left);
		free(root);
		DeleteAllNodes(assist);
	}
}

#ifdef BACKWARD_POINTER
static void AddNodeWithBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi, TreeNode *father)
{
	TreeNode *t = *ptr;

	// if (t == NULL)
	if (!t) // 空树
	{
		t = *ptr = (TreeNode *)malloc(sizeof(TreeNode));

		// if (t!= NULL)
		if (t)
		{
			t->item = *pi;
			t->father = father;
			t->left = t->right = NULL;
		}

		// if (t == NULL)
		else
			UnusualToExit(MemoryNotEnough, NULL);
	}

	// 非空树
	// if (t != NULL)
	else if (pi->KeyValue < t->item.KeyValue) // 若新元素 < 子树根
	{
		AddNodeWithBackwardPointer(&t->left, pi, t); // 往左子树上插
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->left) - GetTreeHeight(t->right) == 2)
		{
			if (pi->KeyValue < t->left->item.KeyValue)
				RotateWithLeftChild(ptr); // 右单转

			// if (pi->KeyValue > t->left->item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->item.KeyValue) // 若新元素 > 子树根
	{
		AddNodeWithBackwardPointer(&t->right, pi, t); // 往右子树上插
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->right) - GetTreeHeight(t->left) == 2)
		{
			if (pi->KeyValue > t->right->item.KeyValue)
				RotateWithRightChild(ptr); // 左单转

			// if (pi->KeyValue < t->right->item.KeyValue)
			else
				DoubleWithRightChild(ptr); // 左转,后右转
		}
	#endif
	}

	else
		UnusualToExit(SameTreeItem, NULL); // 树中已有该结点
	#ifdef AVL_BINARY_TREE
		t->height = GetMax(GetTreeHeight(t->left), GetTreeHeight(t->right)) + 1;
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
			t->item = *pi;
			t->left = t->right = NULL;
		}

		// if (t == NULL)
		else
			UnusualToExit(MemoryNotEnough, NULL);
	}

	// 非空树
	// if (t != NULL)
	else if (pi->KeyValue < t->item.KeyValue) // 若新元素 < 子树根
	{
		AddNodeWithoutBackwardPointer(&t->left, pi); // 往左子树上插
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->left) - GetTreeHeight(t->right) == 2)
		{
			if (pi->KeyValue < t->left->item.KeyValue)
				RotateWithLeftChild(ptr); // 右单转

			// if (pi->KeyValue > t->left->item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->item.KeyValue) // 若新元素 > 子树根
	{
		AddNodeWithoutBackwardPointer(&t->right, pi); // 往右子树上插
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->right) - GetTreeHeight(t->left) == 2)
		{
			if (pi->KeyValue > t->right->item.KeyValue)
				RotateWithRightChild(ptr); // 左单转

			// if (pi->KeyValue < t->right->item.KeyValue)
			else
				DoubleWithRightChild(ptr); // 左转,后右转
		}
	#endif
	}

	else
		; // 树中已有该结点
	#ifdef AVL_BINARY_TREE
		t->height = GetMax(GetTreeHeight(t->left), GetTreeHeight(t->right)) + 1;
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
	FILE * const FilePointer = fopen(FileName, Mode);

	// if (FilePointer == NULL)
	if (!FilePointer)
#endif
		UnusualToExit(OpenFileError, FileName);

	// if (strcmp(Mode, WRITE) == 0)
	if (!strcmp(Mode, WRITE)) // 文件输出
#ifdef CAN_OPEN_FILE
		OutputBinaryTreeToMonitor(BinaryTree, FilePointer, FileName); // 输出为文本文件
#else
		OutputBinaryTreeToBinaryFile(BinaryTree, FilePointer); // 输出为二进制文件
#endif

	// if (strcmp(Mode, READ) == 0)
	if (!strcmp(Mode, READ)) // 文件输入
#ifdef CAN_OPEN_FILE
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

#ifndef CAN_OPEN_FILE
static void OutputBinaryTreeToBinaryFile(Tree * const BinaryTree, FILE * const FilePointer)
{
	TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));

	// if (buffer == NULL)
	if (!buffer)
		UnusualToExit(MemoryNotEnough, NULL);

	// if (BinaryTree->root != NULL) 
	if (BinaryTree->root)
	{
		LinkList Link;
		CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), NULL);
		EnQueue(&Link, BinaryTree->root); // 入队
		LinkItem temp;
		ElemNumb size = 0, n = 2;
		TreeNode NullItem = {
								{ 0 },
#ifdef BACKWARD_POINTER
								NULL,
#endif
								NULL,
								NULL,
#ifdef AVL_BINARY_TREE
								0
#endif 
		};

		do
		{
			DeQueue(&Link, &temp); // 出队
			buffer[size++].KeyValue = temp->item.KeyValue;

			// if (temp->left != NULL)
			if (temp->left)
				EnQueue(&Link, temp->left);

			// if (temp->left == NULL)
			else
				EnQueue(&Link, &NullItem);

			// if (temp->right != NULL)
			if (temp->right)
				EnQueue(&Link, temp->right);

			// if (temp->right == NULL)
			else
				EnQueue(&Link, &NullItem);

			if (Link.size == n) // 队列中元素数量为2的n次幂
				n <<= 1; // n = 2 * n;
		} // while (QueueIsAllNull(&Link) == false);
		while (!QueueIsAllNull(&Link));
		DestroyListByLink(&Link);
		fwrite(buffer, sizeof(TreeItem), size, FilePointer);
	}
	free(buffer);
}

static void InputBinaryTreeFromBinaryFile(Tree * const BinaryTree, FILE * const FilePointer)
{
	TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));

	// if (buffer == NULL)
	if (!buffer)
		UnusualToExit(MemoryNotEnough, NULL);

	const ElemNumb size = (ElemNumb)fread(buffer, sizeof(TreeItem), ((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1), FilePointer);
	if (size > 0)
	{
		ElemNumb i;
		for (i = 0; i < size; ++i)
			AddBinaryTreeNode(BinaryTree, &buffer[i]);
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
#ifdef DEBUG
	#ifdef FILENAME_LIMIT
		const char * const FileName = "DLR with stack.txt";
	#else
		const char * const FileName = "前序遍历涉及的堆栈操作.txt";
	#endif
#else
	const char * const FileName = NULL;
#endif
	// 创建并初始化堆栈S
	CreateListByArray(&S, BinaryTree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\n前序遍历 (根->左子->右子)\n");
#else
	fprintf(Stream, "\n前序遍历 (根->左子->右子)\n");
#endif
	const TreeNode * temp = BinaryTree->root; // 初始T为树根地址
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( temp != NULL || S.size != 0 )
	while (temp || S.size)
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
#ifdef DEBUG
			TextFileAppendOperationByArray(&S);
#endif
			temp = temp->left;
		}

		// if (S.size != 0)
		if (S.size)
		{
			Pop(&S, &TEMP); // 结点弹出堆栈
#ifdef DEBUG
			TextFileAppendOperationByArray(&S);
#endif
			temp = TEMP.right; // 转向右子树
		}
	}
	DestroyListByArray(&S);
}

// 中序遍历
static void InOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// 非递归算法
	ArrayList S;
#ifdef DEBUG
	#ifdef FILENAME_LIMIT
		const char * const FileName = "LDR with stack.txt";
	#else
		const char* const FileName = "中序遍历涉及的堆栈操作.txt";
	#endif
#else
	const char * const FileName = NULL;
#endif
	// 创建并初始化堆栈S
	CreateListByArray(&S, BinaryTree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\n中序遍历 (左子->根->右子)\n");
#else
	fprintf(Stream, "\n中序遍历 (左子->根->右子)\n");
#endif
	const TreeNode * T = BinaryTree->root;
	const TreeNode * temp;
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( T != NULL || S.size != 0 )
	while (T || S.size)
	{
		// while (T != NULL)
		while (T) // 一直向左并将沿途结点压入堆栈
		{
			Push(&S, T);
#ifdef DEBUG
			TextFileAppendOperationByArray(&S);
#endif
			T = T->left;
		}

		// if (S.size != 0)
		if (S.size)
		{
			Pop(&S, &TEMP); // 结点弹出堆栈
#ifdef DEBUG
			TextFileAppendOperationByArray(&S);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
			++sum;
			T = temp->right; // 转向右子树
		}
	}
	DestroyListByArray(&S);
}

// 后序遍历
static void PostOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->size != 0)
	if (BinaryTree->size)
	{
		// 非递归算法
		// 创建并初始化堆栈S Q
		ArrayList S;
		CreateListByArray(&S, BinaryTree->size, NULL);
#ifdef DEBUG
	#ifdef FILENAME_LIMIT
		const char * const FileName = "LRD with stack.txt";
	#else
		const char * const FileName = "后序遍历涉及的堆栈操作.txt";
	#endif
#else
		const char * const FileName = NULL;
#endif
		ArrayList Q;
		CreateListByArray(&Q, BinaryTree->size, FileName); // 创建并初始化堆栈Q，用于反向输出
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(Stream, "\n后序遍历 (左子->右子->根)\n");
#else
		fprintf(Stream, "\n后序遍历 (左子->右子->根)\n");
#endif
		const TreeNode * T = BinaryTree->root;
		TreeNode TEMP;
		const TreeNode * temp;
		ElemNumb sum = 0;

		// while ( T != NULL || S.size != 0 )
		while (T || S.size)
		{
			// while (T != NULL)
			while (T) // 一直向右并将沿途结点压入堆栈
			{
				Push(&S, T);
				Push(&Q, T); // 将遍历到的结点压栈，用于反向
#ifdef DEBUG
				TextFileAppendOperationByArray(&Q);
#endif
				T = T->right;
			}

			// if (S.size != 0)
			if (S.size)
			{
				Pop(&S, &TEMP); // 结点弹出堆栈
				T = TEMP.left; // 转向左子树
			}
		}

		// while (Q.size != 0)
		while (Q.size)
		{
			Pop(&Q, &TEMP);
#ifdef DEBUG
			TextFileAppendOperationByArray(&Q);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
			++sum;
		}
		DestroyListByArray(&S);
		DestroyListByArray(&Q);
	}
}

// 层序遍历
static void LevelOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->size != 0)
	if (BinaryTree->size)
	{
		if (Stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stdout, "\n层序遍历 (自上而下 从左至右)");
#else
			fprintf(stdout, "\n层序遍历 (自上而下 从左至右)");
#endif
		fputs("\n", Stream);
		LinkList Link;
		CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), QueueFileName);
		EnQueue(&Link, BinaryTree->root); // 入队
#ifdef DEBUG
		TextFileAppendOperationByLink(&Link);
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
#ifdef AVL_BINARY_TREE
									0
#endif
		};
		do
		{
			DeQueue(&Link, &temp); // 出队
#ifdef DEBUG
			TextFileAppendOperationByLink(&Link);
#endif
			if (Stream == stdout)
			{
				// if (temp->item.KeyValue != 0)
				if (temp->item.KeyValue)
#ifdef WINDOWS_VISUALSTUDIO
					fprintf_s(stdout, "0x%p\t", &temp->item);
#else
					fprintf(stdout, "%p\t", &temp->item);
#endif

				// if (temp->item.KeyValue == 0)
				else
					fputs("NULL\n", Stream);
			}

			// if (temp->item.KeyValue != 0)
			if (temp->item.KeyValue)
			{
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(Stream, OUTPUT_FORMAT, Stream == stdout ? '\t' : '\n');
#else
				fprintf(Stream, OUTPUT_FORMAT, Stream == stdout ? '\t' : '\n');
#endif
				// if (Stream == stdout)
				if (Stream == stdout)
				{
					// if (temp->item.KeyValue != 0)
					if (temp->item.KeyValue)
					{
#ifdef BACKWARD_POINTER
						fputs("父: ", stdout);

						// if (temp->father != NULL)
						if (temp->father)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p\t", temp->father);
#else
							fprintf(stdout, "%p\t", temp->father);
#endif
						// if (temp->father == NULL)
						else
							fputs("NULL\t", stdout);
#endif

						fputs("左子: ", stdout);

						// if (temp->left != NULL)
						if (temp->left)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p", temp->left);
#else
							fprintf(stdout, "%p", temp->left);
#endif		

						// if (temp->left == NULL)
						else
							fputs("NULL\t", stdout);
						fputs("  右子: ", stdout);

						// if (temp->right != NULL)
						if (temp->right)
#ifdef WINDOWS_VISUALSTUDIO
							fprintf_s(stdout, "0x%p\n", temp->right);
#else
							fprintf(stdout, "%p\n", temp->right);
#endif

						// if (temp->right == NULL)
						else
							fputs("NULL\n", stdout);
					}
				}
			}

			// if (temp->item.KeyValue != 0)
			else if (Stream != stdout)
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(Stream, "%d\n", 0);
#else
				fprintf(Stream, "%d\n", 0);
#endif

			// if (temp->left != NULL)
			if (temp->left)
			{
				EnQueue(&Link, temp->left);
#ifdef DEBUG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->left == NULL)
			else
			{
				EnQueue(&Link, &NullItem);
#ifdef DEBUG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->right != NULL)
			if (temp->right)
			{
				EnQueue(&Link, temp->right);
#ifdef DEBUG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->right == NULL)
			else
			{
				EnQueue(&Link, &NullItem);
#ifdef DEBUG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			if (Link.size == n) // 队列中元素数量为2的n次幂
				n <<= 1; // n = 2 * n;
		} // while (QueueIsAllNull(&Link) == false);
		while (!QueueIsAllNull(&Link));
		DestroyListByLink(&Link);
	}

	if (Stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stdout, "\n当前共有%d个元素\n\n", BinaryTree->size);
#else
		fprintf(stdout, "\n当前共有%d个元素\n\n", BinaryTree->size);
#endif
}

#ifdef AVL_BINARY_TREE

static void RotateWithLeftChild(TreeNode ** const k2pt)
{
	TreeNode * k1, * const k2 = * k2pt;
	k1 = k2->left;
	k2->left = k1->right;
#ifdef BACKWARD_POINTER
	// if (k1->right != NULL)
	if (k1->right)
		k1->right->father = k2;
#endif
	k1->right = k2;
#ifdef BACKWARD_POINTER
	k2->father = k1;
#endif
	k2->height = GetMax(GetTreeHeight(k2->left), GetTreeHeight(k2->right)) + 1;
	k1->height = GetMax(GetTreeHeight(k1->left), k2->height) + 1;
#ifdef BACKWARD_POINTER
	k1->father = (*k2pt)->father;
#endif
	*k2pt = k1;
}

static void RotateWithRightChild(TreeNode ** const k2pt)
{
	TreeNode * k1, * const k2 = * k2pt;
	k1 = k2->right;
	k2->right = k1->left;
#ifdef BACKWARD_POINTER
	// if (k1->left != NULL)
	if (k1->left)
		k1->left->father = k2;
#endif
	k1->left = k2;
#ifdef BACKWARD_POINTER
	k2->father = k1;
#endif
	k2->height = GetMax(GetTreeHeight(k2->left), GetTreeHeight(k2->right)) + 1;
	k1->height = GetMax(GetTreeHeight(k1->right), k2->height) + 1;
#ifdef BACKWARD_POINTER
	k1->father = (* k2pt)->father;
#endif
	* k2pt = k1;
}

static void DoubleWithLeftChild(TreeNode ** const k1pt)
{
	RotateWithRightChild(&(* k1pt)->left);
	RotateWithLeftChild(k1pt);
}

static void DoubleWithRightChild(TreeNode ** const k1pt)
{
	RotateWithLeftChild(&(* k1pt)->right);
	RotateWithRightChild(k1pt);
}

#endif

static void Traversal(void (* pf) (const Tree * const BinaryTree, FILE * const Stream), const Tree * const BinaryTree, FILE * const Stream)
{
	pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
}
