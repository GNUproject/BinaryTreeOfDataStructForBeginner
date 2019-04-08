
// 二叉树
// binary tree.c

#include "binary tree.h"
#include "queue of binary tree.h"
#include "stack Of binary tree.h"

#define GetMax(x,y)	((x)>(y)?(x):(y))
#define GetTreeHeight(t) ((t) != NULL ? (t)->height : -1)

#ifdef WINDOWS_VISUALSTUDIO
	static const char * const WhiteList = " !#$%&`()+,-.;=@{|}[]^_'{}~"; // 文件名特殊字符白名单
#else
	static const char * const WhiteList = " !\"#$%&`()*+,-./:;<=>\?@{|}[\\]^_\'{|}~"; // 文件名特殊字符白名单
#endif

#ifdef CAN_OPEN_FILE
	static const char * const ExtendFileName = ".txt";
#endif

#ifdef DEBUG
	static const char * const QueueFileName = "queue.txt";
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

static const char * const EmptyTree = "空树\n";
static const char * const FullTree = "已至数量最大值 请扩充Max或ElemNumb数据单位!\n";
static const char * const LengthError = "二叉树结点数非法\n";
static const char * const DLR = " of DLR"; // 前序遍历
static const char * const LDR = " of LDR"; // 中序遍历
static const char * const LRD = " of LRD"; // 后序遍历
static const char * const level = " with LEVEL"; // 层序遍历

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
static void DeleteAllNodes(TreeNode * const root);
static void MoreFileOperationByBinaryTree(Tree * const tree, const char * const FileName, const char * const mode);
static void PreOrderTraversal(const Tree * const tree, FILE * const stream);
static void InOrderTraversal(const Tree * const tree, FILE * const stream);
static void PostOrderTraversal(const Tree * const tree, FILE * const stream);
static void LevelOrderTraversal(const Tree * const tree, FILE * const stream);
static void Traversal(void (*pf) (const Tree * const tree, FILE * const stream), const Tree * const tree, FILE * const stream);

extern void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName);
extern void DestroyListByArray(ArrayList * const Array);
extern void Push(ArrayList * const Array, const ArrayItem * const NewItem);
extern void Pop(ArrayList * const Array, ArrayItem * const DelItem);
extern void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);
extern void DestroyListByLink(LinkList * const Link);
extern void EnQueue(LinkList * const Link, const LinkItem NewItem);
extern void DeQueue(LinkList * const Link, LinkItem * const DelItem);

void CreateBinaryTree(Tree * const tree, const ElemNumb Max, const char * const FileName)
{
	// if (tree != NULL)
	if (tree)
	{
		tree->root = NULL;
		tree->size = 0;
		if (Max > 0)
		{
			tree->MaxSize = Max;
			printf("\n动态搜索平衡二叉树\t%s\t本例中以0x起始的数字均为内存地址\n", sizeof(void *) == 4 ? "x86" : "x64");

			// if (FileName != NULL)
			if (FileName)
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
				CheckFileName(TempDLR);
				CheckFileName(TempLDR);
				CheckFileName(TempLRD);
				CheckFileName(TempFile);

				const unsigned char FullDLRLen = (unsigned char)strlen(TempDLR) + 1;
				const unsigned char FullLDRLen = (unsigned char)strlen(TempLDR) + 1;
				const unsigned char FullLRDLen = (unsigned char)strlen(TempLRD) + 1;
				const unsigned char FullFileNameLen = (unsigned char)strlen(TempFile) + 1;

				tree->DLRFileName = (char *)malloc(FullDLRLen);
				tree->LDRFileName = (char *)malloc(FullLDRLen);
				tree->LRDFileName = (char *)malloc(FullLRDLen);
				tree->FileName = (char *)malloc(FullFileNameLen);

				// if (tree->DLRFileName != NULL && tree->LDRFileName != NULL && tree->LRDFileName != NULL && tree->FileName != NULL)
				if (tree->DLRFileName && tree->LDRFileName && tree->LRDFileName && tree->FileName)
				{
#ifdef WINDOWS_VISUALSTUDIO
					_memccpy(tree->DLRFileName, TempDLR, 0, FullDLRLen);
					_memccpy(tree->LDRFileName, TempLDR, 0, FullLDRLen);
					_memccpy(tree->LRDFileName, TempLRD, 0, FullLRDLen);
					_memccpy(tree->FileName, TempFile, 0, FullFileNameLen);
#else
					memccpy(tree->DLRFileName, TempDLR, 0, FullDLRLen);
					memccpy(tree->LDRFileName, TempLDR, 0, FullLDRLen);
					memccpy(tree->LRDFileName, TempLRD, 0, FullLRDLen);
					memccpy(tree->FileName, TempFile, 0, FullFileNameLen);
#endif
				}

				// if (tree->DLRFileName == NULL || tree->LDRFileName == NULL || tree->LRDFileName == NULL && tree->FileName == NULL)
				else
					UnusualToExit(MemoryNotEnough, NULL);
			}

			// if (FileName == NULL)
			else
				tree->DLRFileName = tree->LDRFileName = tree->LRDFileName = tree->FileName = NULL;
		}

		// if (Max <= 0)
		else
			UnusualToExit(LengthError, NULL);
	}

	// if (tree == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void DestroyBinaryTree(Tree * const tree)
{
	// if (tree != NULL)
	if (tree)
	{
		// if (tree->size != 0)
		if (tree->size) // 二叉树非空
		{
			DeleteAllNodes(tree->root);
			tree->root = NULL;
			tree->size = tree->MaxSize = 0;
			free(tree->DLRFileName);
			free(tree->LDRFileName);
			free(tree->LRDFileName);
			free(tree->FileName);
		}
	}

	// if (tree == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

const bool BinaryTreeIsEmpty(const Tree * const tree)
{
	// if (tree != NULL)
	if (tree)
		return tree->root == NULL;

	// if (tree == NULL)
	else
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer, NULL);
		_getch();
#else
		fprintf(stderr, NullPointer, NULL);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}
}

const bool BinaryTreeIsFull(const Tree * const tree)
{
	// if (tree != NULL)
	if (tree)
		return tree->size == tree->MaxSize;

	// if (tree == NULL)
	else
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer, NULL);
		_getch();
#else
		fprintf(stderr, NullPointer, NULL);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}
}

// 定位tree树中的pi位置
Pair SearchBinaryTreeItem(const Tree * const tree, const TreeItem * const pi)
{
	// if (tree != NULL && pi != NULL)
	if (tree && pi)
	{
		Pair result = { NULL, tree->root }; // 初始指向根

		// if (tree->size != 0)
		if (tree->size) // 非空树
		{
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

		// if (tree->size == 0)
		else // 空树
			return result;
	}

	// if (tree == NULL || pi == NULL)
	else
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer, NULL);
		_getch();
#else
		fprintf(stderr, NullPointer, NULL);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}
}

void AddBinaryTreeNode(Tree * const tree, const TreeItem * const pi)
{
	// if (tree != NULL && pi != NULL)
	if (tree && pi)
	{
		// if (pi->KeyValue != 0)
		if (pi->KeyValue) // 因为在二叉树里的数据0被认为是NULL故不能为0
		{
			if (tree->size != tree->MaxSize)
			{
#ifndef AVL_BINARY_TREE
				Pair result = SearchBinaryTreeItem(tree, pi);

				// if (result.child == NULL)
				if (!result.child) // 若二叉树中不存在*pi
				{
#endif

#ifdef BACKWARD_POINTER
					AddNodeWithBackwardPointer(&tree->root, pi, NULL);
#else
					AddNodeWithoutBackwardPointer(&tree->root, pi);
#endif
					++tree->size;

#ifndef AVL_BINARY_TREE
				}

				// if (result.child != NULL)
				else // 若二叉树中已有*pi
					UnusualToExit(SameTreeItem, NULL);
#endif
			}

			// if (tree->size == tree->MaxSize)
			else // 结点数已至最大值
				UnusualToExit(FullTree, NULL);
		}

		// if (pi->KeyValue == 0)
		else
			return;
	}

	// if (tree == NULL || pi == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void DelBinaryTreeNode(Tree * const tree, TreeItem * const pi)
{
#ifndef AVL_BINARY_TREE
	// if (tree != NULL && pi != NULL)
	if (tree && pi)
	{
		Pair result = SearchBinaryTreeItem(tree, pi);
		
		// if (result.child != NULL)
		if (result.child) // 二叉树中存在该结点
		{
			// if (result.child->left != NULL && result.child->right != NULL)
			if (result.child->left && result.child->right) // 若欲删结点有两个子结点
			{
				TreeNode *q;

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
					tree->root = q;

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
					tree->root = NULL;
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
						tree->root = result.child->left;
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
						tree->root = result.child->right;
					}
				}
			}

			free(result.child);
			--tree->size;
		}

		// if (result.child == NULL)
			else // 二叉树中不存在该结点
		UnusualToExit(NoTreeItem, NULL);
	}

	// if (tree == NULL || pi == NULL)
	else
		UnusualToExit(NullPointer, NULL);
#else
	UnusualToExit("将程序微调区内的AVL_BINARY_TREE设为关\n", NULL);
#endif
}

// 文件输入/输出操作
void FileOperationByBinaryTree(Tree * const tree, const char * const mode)
{
	// if (tree != NULL && mode != NULL)
	if (tree && mode)
	{
		// if (tree->FileName != NULL)
		if (tree->FileName)
		{
			// if (strcmp(mode, WRITE == 0)
			if (!strcmp(mode, WRITE))
			{
#ifdef CAN_OPEN_FILE
				MoreFileOperationByBinaryTree(tree, tree->DLRFileName, mode);
				MoreFileOperationByBinaryTree(tree, tree->LDRFileName, mode);
				MoreFileOperationByBinaryTree(tree, tree->LRDFileName, mode);
#endif
			}
			MoreFileOperationByBinaryTree(tree, tree->FileName, mode);
		}
	}

	// if (tree == NULL || mode == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// 键盘输入
void InputBinaryTreeFromKeyboard(Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		if (stream == stdin)
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

		// while (feof(stream) == 0)
		while (!feof(stream))
		{
#ifdef WINDOWS_VISUALSTUDIO
			if (fscanf_s(stream, INPUT_FORMAT) == NUMBER_OF_FORMAT)
#else
			if (fscanf(stream, INPUT_FORMAT) == NUMBER_OF_FORMAT)
#endif
			{
				// if (temp.KeyValue != 0)
				if (temp.KeyValue)
					AddBinaryTreeNode(tree, &temp);

				// if (temp.KeyValue == 0)
				else
					continue;
			}

			else
				UnusualToExit(InputError, NULL);
		}
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void OutputBinaryTreeToMonitor(const Tree * const tree, FILE * const stream, const char * const str)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->DLRFileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->DLRFileName))))
		{
			// 以下3选1

			// 方法1
			// PreOrderTraversal(tree, stream);

			// 方法2
			Traversal(PreOrderTraversal, tree, stream);

			// 方法3
			// void(*pf) (const Tree * const tree, FILE * const stream);
			// pf = PreOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->LDRFileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->LDRFileName))))
		{
			// 以下3选1

			// 方法1
			// InOrderTraversal(tree, stream);

			// 方法2
			Traversal(InOrderTraversal, tree, stream);

			// 方法3
			// void (*pf) (const Tree * const tree, FILE * const stream);
			// pf = InOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->LRDFileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->LRDFileName))))
		{
			// 以下3选1

			// 方法1
			// PostOrderTraversal(tree, stream);

			// 方法2
			Traversal(PostOrderTraversal, tree, stream);

			// 方法3
			// void (*pf) (const Tree * const tree, FILE * const stream);
			// pf = PostOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->FileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->FileName))))
		{
			// 以下3选1

			// 方法1
			// LevelOrderTraversal(tree, stream);

			// 方法2
			Traversal(LevelOrderTraversal, tree, stream);

			// 方法3
			// void (*pf) (const Tree * const tree, FILE * const stream);
			// pf = LevelOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void GetMinOfBinaryTree(const Tree * const tree, TreeItem * const item)
{
	// if (tree != NULL && item != NULL)
	if (tree && item)
	{
		const TreeNode *pt = tree->root;

		// if (pt != NULL)
		if (pt) // 树非空
		{
			// while (pt->left != NULL)
			while (pt->left)
				pt = pt->left;
			*item = pt->item;
		}

		// if (pt == NULL)
		else // 空树
			UnusualToExit(EmptyTree, NULL);
	}

	// if (tree == NULL || item == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void GetMaxOfBinaryTree(const Tree * const tree, TreeItem * const item)
{
	// if (tree != NULL && item != NULL)
	if (tree && item)
	{
		const TreeNode *pt = tree->root;

		// if (pt != NULL)
		if (pt) // 树非空
		{
			// while (pt->right != NULL)
			while (pt->right)
				pt = pt->right;
			*item = pt->item;
		}

		// if (pt == NULL)
		else // 空树
			UnusualToExit(EmptyTree, NULL);
	}

	// if (tree == NULL || item == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void UnusualToExit(const char * const str, const char * const FileName)
{
	// if (str != NULL)
	if (str)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, str, FileName);
		_getch();
#else
		fprintf(stderr, str, FileName);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	// if (str == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void CheckFileName(const char * const FullFileName)
{
	// if (FullFileName != NULL)
	if (FullFileName)
	{
		const unsigned char count = (unsigned char)strlen(FullFileName);
		if (count < LEN)
		{
			unsigned char i;
			for (i = 0; i < count; ++i)

				// if (isalnum(FullFileName[i]) == 0 && strrchr(WhiteList, FullFileName[i]) == NULL)
				if (!isalnum(FullFileName[i]) && !strrchr(WhiteList, FullFileName[i]))
				{
					char ErrorChar[2] = { FullFileName[i],  0 };
					UnusualToExit(FileNameError, ErrorChar);
				}
		}

		// if (count >= LEN)
		else
			UnusualToExit(FileNameTooLong, NULL);
	}

	// if (FullFileName == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

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
	TreeNode *t = *ptr;

	// if (t == NULL)
	if (!t) // 空树
	{
		t = *ptr = (TreeNode *)malloc(sizeof(TreeNode));

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

static void MoreFileOperationByBinaryTree(Tree * const tree, const char * const FileName, const char * const mode)
{
	// if (tree != NULL && mode != NULL)
	if (tree && mode)
	{
#ifdef WINDOWS_VISUALSTUDIO	
		FILE *FilePointer;
		const errno_t err = fopen_s(&FilePointer, FileName, mode);

		// if (err == 0)
		if (!err)
#else
		FILE * const FilePointer = fopen(FileName, mode);

		// if (FilePointer != NULL)
		if (FilePointer)
#endif
		{
			// if (strcmp(mode, WRITE) == 0)
			if (!strcmp(mode, WRITE)) // 文件输出
#ifdef CAN_OPEN_FILE
				OutputBinaryTreeToMonitor(tree, FilePointer, FileName);
#else
			{
				// 输出为二进制文件
				TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));
				
				// if (buffer != NULL)
				if (buffer)
				{
					// if (tree->root != NULL) 
					if (tree->root)
					{
						LinkList Link;
						CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), NULL);
						EnQueue(&Link, tree->root); // 入队
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

				// if (buffer == NULL)
				else
					UnusualToExit(MemoryNotEnough, NULL);
			}
#endif

			// if (strcmp(mode, READ) == 0)
			if (!strcmp(mode, READ)) // 文件输入
#ifdef CAN_OPEN_FILE
				InputBinaryTreeFromKeyboard(tree, FilePointer);
#else
			{
				// 从二进制文件输入
				TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));
				
				// if (buffer != NULL)
				if (buffer)
				{
					const ElemNumb size = (ElemNumb)fread(buffer, sizeof(TreeItem), ((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1), FilePointer);
					if (size > 0)
					{
						ElemNumb i;
						for (i = 0; i < size; ++i)
							AddBinaryTreeNode(tree, &buffer[i]);
					}
					free(buffer);
				}

				// if (buffer == NULL)
				else
					UnusualToExit(MemoryNotEnough, NULL);
			}
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

		else
			UnusualToExit(OpenFileError, FileName);
	}

	// if (tree == NULL || mode == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// 前序遍历
static void PreOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// 非递归算法
		ArrayList S;
#ifdef DEBUG
		const char * const FileName = "DLR with stack.txt";
#else
		const char * const FileName = NULL;
#endif
		// 创建并初始化堆栈S
		CreateListByArray(&S, tree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stream, "\n前序遍历 (根->左子->右子)\n");
#else
		fprintf(stream, "\n前序遍历 (根->左子->右子)\n");
#endif
		const TreeNode *temp = tree->root; // 初始T为树根地址
		TreeNode TEMP;
		ElemNumb sum = 0;
		
		// while ( temp != NULL || S.size != 0 )
		while (temp || S.size)
		{
			// while (temp != NULL)
			while (temp) // 一直向左并将沿途结点压入堆栈
			{
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // 输出结点
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

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// 中序遍历
static void InOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// 非递归算法
		ArrayList S;
#ifdef DEBUG
		const char * const FileName = "LDR with stack.txt";
#else
		const char * const FileName = NULL;
#endif
		// 创建并初始化堆栈S
		CreateListByArray(&S, tree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stream, "\n中序遍历 (左子->根->右子)\n");
#else
		fprintf(stream, "\n中序遍历 (左子->根->右子)\n");
#endif
		const TreeNode *T = tree->root;
		const TreeNode *temp;
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
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
				++sum;
				T = temp->right; // 转向右子树
			}
		}
		DestroyListByArray(&S);
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// 后序遍历
static void PostOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// if (tree->size != 0)
		if (tree->size)
		{
			// 非递归算法
			// 创建并初始化堆栈S Q
			ArrayList S;
			CreateListByArray(&S, tree->size, NULL);
#ifdef DEBUG
			const char * const FileName = "LRD with stack.txt";
#else
			const char * const FileName = NULL;
#endif
			ArrayList Q;
			CreateListByArray(&Q, tree->size, FileName); // 创建并初始化堆栈Q，用于反向输出
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stream, "\n后序遍历 (左子->右子->根)\n");
#else
			fprintf(stream, "\n后序遍历 (左子->右子->根)\n");
#endif
			const TreeNode *T = tree->root;
			TreeNode TEMP;
			const TreeNode *temp;
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
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // 输出结点
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // 输出结点
#endif
				++sum;
			}
			DestroyListByArray(&S);
			DestroyListByArray(&Q);
		}
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// 层序遍历
static void LevelOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// if (tree->size != 0)
		if (tree->size)
		{
			if (stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(stdout, "\n层序遍历 (自上而下 从左至右)");
#else
				fprintf(stdout, "\n层序遍历 (自上而下 从左至右)");
#endif
			fputs("\n", stream);
			LinkList Link;
			CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), QueueFileName);
			EnQueue(&Link, tree->root); // 入队
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
				if (stream == stdout)
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
						fputs("NULL\n", stream);
				}

				// if (temp->item.KeyValue != 0)
				if (temp->item.KeyValue)
				{
#ifdef WINDOWS_VISUALSTUDIO
					fprintf_s(stream, OUTPUT_FORMAT, stream == stdout ? '\t' : '\n');
#else
					fprintf(stream, OUTPUT_FORMAT, stream == stdout ? '\t' : '\n');
#endif
					// if (stream == stdout)
					if (stream == stdout)
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
				else if (stream != stdout)
#ifdef WINDOWS_VISUALSTUDIO
					fprintf_s(stream, "%d\n", 0);
#else
					fprintf(stream, "%d\n", 0);
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
		if (stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stdout, "\n当前共有%d个元素\n\n", tree->size);
#else
			fprintf(stdout, "\n当前共有%d个元素\n\n", tree->size);
#endif
	}
	
	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

#ifdef AVL_BINARY_TREE

static void RotateWithLeftChild(TreeNode ** const k2pt)
{
	TreeNode *k1, * const k2 = *k2pt;
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
	TreeNode *k1, * const k2 = *k2pt;
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
	k1->father = (*k2pt)->father;
#endif
	*k2pt = k1;
}

static void DoubleWithLeftChild(TreeNode ** const k1pt)
{
	RotateWithRightChild(&(*k1pt)->left);
	RotateWithLeftChild(k1pt);
}

static void DoubleWithRightChild(TreeNode ** const k1pt)
{
	RotateWithLeftChild(&(*k1pt)->right);
	RotateWithRightChild(k1pt);
}

#endif

static void Traversal(void (*pf) (const Tree * const tree, FILE * const stream), const Tree * const tree, FILE * const stream)
{
	pf(tree, stream); // (*pf)(tree, stream);
}
