
// ������
// binary tree.c

#include "binary tree.h"
#include "queue of binary tree.h"
#include "stack Of binary tree.h"

#define GetMax(x,y)	((x)>(y)?(x):(y))
#define GetTreeHeight(t) ((t) != NULL ? (t)->height : -1)

#ifdef WINDOWS_VISUALSTUDIO
	static const char * const WhiteList = " !#$%&`()+,-.;=@{|}[]^_'{}~"; // �ļ��������ַ�������
#else
	static const char * const WhiteList = " !\"#$%&`()*+,-./:;<=>\?@{|}[\\]^_\'{|}~"; // �ļ��������ַ�������
#endif

#ifdef CAN_OPEN_FILE
	static const char * const ExtendFileName = ".txt";
#endif

#ifdef DEBUG
	static const char * const QueueFileName = "queue.txt";
#else
	static const char * const QueueFileName = NULL;
#endif

const char * const SameTreeItem = "����ظ���ֵ��\n";
const char * const NoTreeItem = "�������в����ڸý��!\n";
const char * const InputError = "�������!\n";
const char * const NullPointer = "��ָ��\n";
const char * const OpenFileError = "���ļ�%sʧ��!\n";
const char * const CloseFileError = "�ر��ļ�%sʧ��!\n";
const char * const FileOperationError = "�ļ�%s����ʧ��!\n";
const char * const FileNameTooLong = "�ļ�������\n";
const char * const FileNameError = "�ļ��������Ƿ��ַ�: %s\n";
const char * const MemoryNotEnough = "�ڴ治��!\n";

static const char * const EmptyTree = "����\n";
static const char * const FullTree = "�����������ֵ ������Max��ElemNumb���ݵ�λ!\n";
static const char * const LengthError = "������������Ƿ�\n";
static const char * const DLR = " of DLR"; // ǰ�����
static const char * const LDR = " of LDR"; // �������
static const char * const LRD = " of LRD"; // �������
static const char * const level = " with LEVEL"; // �������

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
			printf("\n��̬����ƽ�������\t%s\t��������0x��ʼ�����־�Ϊ�ڴ��ַ\n", sizeof(void *) == 4 ? "x86" : "x64");

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
		if (tree->size) // �������ǿ�
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

// ��λtree���е�piλ��
Pair SearchBinaryTreeItem(const Tree * const tree, const TreeItem * const pi)
{
	// if (tree != NULL && pi != NULL)
	if (tree && pi)
	{
		Pair result = { NULL, tree->root }; // ��ʼָ���

		// if (tree->size != 0)
		if (tree->size) // �ǿ���
		{
			// while (result.child != NULL)
			while (result.child) // ��ǰ���ǿ�
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
				else // ��ǰ���������������,�ض�Ϊ��ǰ�����*pi���
					break;
			}

			return result;
		}

		// if (tree->size == 0)
		else // ����
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
		if (pi->KeyValue) // ��Ϊ�ڶ������������0����Ϊ��NULL�ʲ���Ϊ0
		{
			if (tree->size != tree->MaxSize)
			{
#ifndef AVL_BINARY_TREE
				Pair result = SearchBinaryTreeItem(tree, pi);

				// if (result.child == NULL)
				if (!result.child) // ���������в�����*pi
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
				else // ��������������*pi
					UnusualToExit(SameTreeItem, NULL);
#endif
			}

			// if (tree->size == tree->MaxSize)
			else // ������������ֵ
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
		if (result.child) // �������д��ڸý��
		{
			// if (result.child->left != NULL && result.child->right != NULL)
			if (result.child->left && result.child->right) // ����ɾ����������ӽ��
			{
				TreeNode *q;

				// ����2ѡ1

				// ����1
				// for (q = result.child->right; q->left != NULL; q = q->left) ����Ϊע��
				for (q = result.child->right; q->left; q = q->left)

				// ����2
				// for (q = result.child->left; q->right != NULL; q = q->right) ����Ϊע��
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
				if (result.parent) // ��ɾ���Ľ��Ǹ����
				{
					if (result.parent->item.KeyValue > result.child->item.KeyValue)
						result.parent->left = q;

					// if (result.parent->item.KeyValue < result.child->item.KeyValue)
					else
						result.parent->right = q;
				}

				// if (result.parent == NULL)
				else // ��ɾ���Ľ��Ϊ�����
					tree->root = q;

				q->left = result.child->left;
				q->right = result.child->right;

	#ifdef BACKWARD_POINTER
				result.child->left->father = q;
				result.child->right->father = q;
	#endif
			}

			// else if (result.child->left == NULL && result.child->right == NULL)
			else if (!result.child->left && !result.child->right) // ����ɾ��������ӽ��
			{
				// if (result.parent != NULL)
				if (result.parent) // ����ɾ�����Ǹ����
				{
					if (result.child->item.KeyValue < result.parent->item.KeyValue)
						result.parent->left = NULL;

					// if (result.child->item.KeyValue > result.parent->item.KeyValue)
					else
						result.parent->right = NULL;
				}

				// if (result.parent == NULL)
				else // ������ɾ�����Ϊ����� ����������һ�����
				{
					tree->root = NULL;
				}
			}

			else // ����ɾ������һ���ӽ��
			{
				// if (result.child->left != NULL)
				if (result.child->left) // ����ɾ������һ�����ӽ��
				{
					// if (result.parent != NULL)
					if (result.parent) // ����ɾ�����Ǹ����
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
					else // ����ɾ�����Ϊ�����
					{
	#ifdef BACKWARD_POINTER
						result.child->left->father = NULL;
	#endif
						tree->root = result.child->left;
					}
				}

				// if (result.chile->right != NULL)
				else // ����ɾ������һ�����ӽ��
				{
					// if (result.parent != NULL)
					if (result.parent) // ����ɾ�����Ǹ����
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
					else // ������ɾ�����Ϊ�����
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
			else // �������в����ڸý��
		UnusualToExit(NoTreeItem, NULL);
	}

	// if (tree == NULL || pi == NULL)
	else
		UnusualToExit(NullPointer, NULL);
#else
	UnusualToExit("������΢�����ڵ�AVL_BINARY_TREE��Ϊ��\n", NULL);
#endif
}

// �ļ�����/�������
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

// ��������
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
			// ����3ѡ1

			// ����1
			// PreOrderTraversal(tree, stream);

			// ����2
			Traversal(PreOrderTraversal, tree, stream);

			// ����3
			// void(*pf) (const Tree * const tree, FILE * const stream);
			// pf = PreOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->LDRFileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->LDRFileName))))
		{
			// ����3ѡ1

			// ����1
			// InOrderTraversal(tree, stream);

			// ����2
			Traversal(InOrderTraversal, tree, stream);

			// ����3
			// void (*pf) (const Tree * const tree, FILE * const stream);
			// pf = InOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->LRDFileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->LRDFileName))))
		{
			// ����3ѡ1

			// ����1
			// PostOrderTraversal(tree, stream);

			// ����2
			Traversal(PostOrderTraversal, tree, stream);

			// ����3
			// void (*pf) (const Tree * const tree, FILE * const stream);
			// pf = PostOrderTraversal;
			// pf(tree, stream); // (*pf)(tree, stream);
		}

		// if (stream == stdout || (stream != stdout && (strcmp(str, tree->FileName)== 0)))
		if (stream == stdout || (stream != stdout && (!strcmp(str, tree->FileName))))
		{
			// ����3ѡ1

			// ����1
			// LevelOrderTraversal(tree, stream);

			// ����2
			Traversal(LevelOrderTraversal, tree, stream);

			// ����3
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
		if (pt) // ���ǿ�
		{
			// while (pt->left != NULL)
			while (pt->left)
				pt = pt->left;
			*item = pt->item;
		}

		// if (pt == NULL)
		else // ����
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
		if (pt) // ���ǿ�
		{
			// while (pt->right != NULL)
			while (pt->right)
				pt = pt->right;
			*item = pt->item;
		}

		// if (pt == NULL)
		else // ����
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

/********************************˽�к���********************************/

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
	if (!t) // ����
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

	// �ǿ���
	// if (t != NULL)
	else if (pi->KeyValue < t->item.KeyValue) // ����Ԫ�� < ������
	{
		AddNodeWithBackwardPointer(&t->left, pi, t); // ���������ϲ�
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->left) - GetTreeHeight(t->right) == 2)
		{
			if (pi->KeyValue < t->left->item.KeyValue)
				RotateWithLeftChild(ptr); // �ҵ�ת

			// if (pi->KeyValue > t->left->item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->item.KeyValue) // ����Ԫ�� > ������
	{
		AddNodeWithBackwardPointer(&t->right, pi, t); // ���������ϲ�
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->right) - GetTreeHeight(t->left) == 2)
		{
			if (pi->KeyValue > t->right->item.KeyValue)
				RotateWithRightChild(ptr); // ��ת

			// if (pi->KeyValue < t->right->item.KeyValue)
			else
				DoubleWithRightChild(ptr); // ��ת,����ת
		}
	#endif
	}

	else
		UnusualToExit(SameTreeItem, NULL); // �������иý��
	#ifdef AVL_BINARY_TREE
		t->height = GetMax(GetTreeHeight(t->left), GetTreeHeight(t->right)) + 1;
	#endif
}

#else

static void AddNodeWithoutBackwardPointer(TreeNode ** const ptr, const TreeItem * const pi)
{
	TreeNode *t = *ptr;

	// if (t == NULL)
	if (!t) // ����
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

	// �ǿ���
	// if (t != NULL)
	else if (pi->KeyValue < t->item.KeyValue) // ����Ԫ�� < ������
	{
		AddNodeWithoutBackwardPointer(&t->left, pi); // ���������ϲ�
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->left) - GetTreeHeight(t->right) == 2)
		{
			if (pi->KeyValue < t->left->item.KeyValue)
				RotateWithLeftChild(ptr); // �ҵ�ת

			// if (pi->KeyValue > t->left->item.KeyValue)
			else
				DoubleWithLeftChild(ptr);
		}
	#endif
	}

	else if (pi->KeyValue > t->item.KeyValue) // ����Ԫ�� > ������
	{
		AddNodeWithoutBackwardPointer(&t->right, pi); // ���������ϲ�
	#ifdef AVL_BINARY_TREE
		if (GetTreeHeight(t->right) - GetTreeHeight(t->left) == 2)
		{
			if (pi->KeyValue > t->right->item.KeyValue)
				RotateWithRightChild(ptr); // ��ת

			// if (pi->KeyValue < t->right->item.KeyValue)
			else
				DoubleWithRightChild(ptr); // ��ת,����ת
		}
	#endif
	}

	else
		; // �������иý��
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
			if (!strcmp(mode, WRITE)) // �ļ����
#ifdef CAN_OPEN_FILE
				OutputBinaryTreeToMonitor(tree, FilePointer, FileName);
#else
			{
				// ���Ϊ�������ļ�
				TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));
				
				// if (buffer != NULL)
				if (buffer)
				{
					// if (tree->root != NULL) 
					if (tree->root)
					{
						LinkList Link;
						CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), NULL);
						EnQueue(&Link, tree->root); // ���
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
							DeQueue(&Link, &temp); // ����
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

							if (Link.size == n) // ������Ԫ������Ϊ2��n����
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
			if (!strcmp(mode, READ)) // �ļ�����
#ifdef CAN_OPEN_FILE
				InputBinaryTreeFromKeyboard(tree, FilePointer);
#else
			{
				// �Ӷ������ļ�����
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

// ǰ�����
static void PreOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// �ǵݹ��㷨
		ArrayList S;
#ifdef DEBUG
		const char * const FileName = "DLR with stack.txt";
#else
		const char * const FileName = NULL;
#endif
		// ��������ʼ����ջS
		CreateListByArray(&S, tree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stream, "\nǰ����� (��->����->����)\n");
#else
		fprintf(stream, "\nǰ����� (��->����->����)\n");
#endif
		const TreeNode *temp = tree->root; // ��ʼTΪ������ַ
		TreeNode TEMP;
		ElemNumb sum = 0;
		
		// while ( temp != NULL || S.size != 0 )
		while (temp || S.size)
		{
			// while (temp != NULL)
			while (temp) // һֱ���󲢽���;���ѹ���ջ
			{
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // ������
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // ������
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
				Pop(&S, &TEMP); // ��㵯����ջ
#ifdef DEBUG
				TextFileAppendOperationByArray(&S);
#endif
				temp = TEMP.right; // ת��������
			}
		}
		DestroyListByArray(&S);
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// �������
static void InOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// �ǵݹ��㷨
		ArrayList S;
#ifdef DEBUG
		const char * const FileName = "LDR with stack.txt";
#else
		const char * const FileName = NULL;
#endif
		// ��������ʼ����ջS
		CreateListByArray(&S, tree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stream, "\n������� (����->��->����)\n");
#else
		fprintf(stream, "\n������� (����->��->����)\n");
#endif
		const TreeNode *T = tree->root;
		const TreeNode *temp;
		TreeNode TEMP;
		ElemNumb sum = 0;
		
		// while ( T != NULL || S.size != 0 )
		while (T || S.size)
		{
			// while (T != NULL)
			while (T) // һֱ���󲢽���;���ѹ���ջ
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
				Pop(&S, &TEMP); // ��㵯����ջ
#ifdef DEBUG
				TextFileAppendOperationByArray(&S);
#endif
				temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // ������
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // ������
#endif
				++sum;
				T = temp->right; // ת��������
			}
		}
		DestroyListByArray(&S);
	}

	// if (tree == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// �������
static void PostOrderTraversal(const Tree * const tree, FILE * const stream)
{
	// if (tree != NULL && stream != NULL)
	if (tree && stream)
	{
		// if (tree->size != 0)
		if (tree->size)
		{
			// �ǵݹ��㷨
			// ��������ʼ����ջS Q
			ArrayList S;
			CreateListByArray(&S, tree->size, NULL);
#ifdef DEBUG
			const char * const FileName = "LRD with stack.txt";
#else
			const char * const FileName = NULL;
#endif
			ArrayList Q;
			CreateListByArray(&Q, tree->size, FileName); // ��������ʼ����ջQ�����ڷ������
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stream, "\n������� (����->����->��)\n");
#else
			fprintf(stream, "\n������� (����->����->��)\n");
#endif
			const TreeNode *T = tree->root;
			TreeNode TEMP;
			const TreeNode *temp;
			ElemNumb sum = 0;
			
			// while ( T != NULL || S.size != 0 )
			while (T || S.size)
			{
				// while (T != NULL)
				while (T) // һֱ���Ҳ�����;���ѹ���ջ
				{
					Push(&S, T);
					Push(&Q, T); // ���������Ľ��ѹջ�����ڷ���
#ifdef DEBUG
					TextFileAppendOperationByArray(&Q);
#endif
					T = T->right;
				}

				// if (S.size != 0)
				if (S.size)
				{
					Pop(&S, &TEMP); // ��㵯����ջ
					T = TEMP.left; // ת��������
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
				fprintf_s(stream, OUTPUT_FORMAT, '\n'); // ������
#else
				fprintf(stream, OUTPUT_FORMAT, '\n'); // ������
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

// �������
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
				fprintf_s(stdout, "\n������� (���϶��� ��������)");
#else
				fprintf(stdout, "\n������� (���϶��� ��������)");
#endif
			fputs("\n", stream);
			LinkList Link;
			CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), QueueFileName);
			EnQueue(&Link, tree->root); // ���
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
				DeQueue(&Link, &temp); // ����
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
							fputs("��: ", stdout);

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

							fputs("����: ", stdout);
							
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
							fputs("  ����: ", stdout);

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

				if (Link.size == n) // ������Ԫ������Ϊ2��n����
					n <<= 1; // n = 2 * n;
			} // while (QueueIsAllNull(&Link) == false);
			while (!QueueIsAllNull(&Link));
			DestroyListByLink(&Link);
		}
		if (stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stdout, "\n��ǰ����%d��Ԫ��\n\n", tree->size);
#else
			fprintf(stdout, "\n��ǰ����%d��Ԫ��\n\n", tree->size);
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
