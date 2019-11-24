
// ������
// binary tree.c

#include "binary tree.h"
#include "queue of binary tree.h"
#include "stack of binary tree.h"

#define GetMax(x,y)	((x)>(y)?(x):(y))
#define GetTreeHeight(t) ((t) != NULL ? (t)->height : -1)

#ifdef LOG
	static const char * const QueueFileName = "���в���.txt";
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
const char * const MemoryNotEnough = "�ڴ治��!\n";

static const char * const DLR = "��ǰ�����";	// ǰ�����
static const char * const LDR = "���������";	// �������
static const char * const LRD = "�ĺ������";	// �������
static const char * const level = "�Ĳ������"; // �������
static const char * const EmptyTree = "����\n";
static const char * const FullTree = "�����������ֵ ������Max��ElemNumb���ݵ�λ!\n";
static const char * const LengthError = "������������Ƿ�\n";

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

#ifdef READABLE
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

// ��λBinaryTree���е�piλ��
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

	Pair result = { NULL, BinaryTree->root }; // ��ʼָ���

	// if (BinaryTree->size == 0)
	if (!BinaryTree->size) // ����
		return result;

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

void AddBinaryTreeNode(Tree * const BinaryTree, const TreeItem * const pi)
{
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);
		
	// if (pi->KeyValue == 0)
	if (!pi->KeyValue) // ��Ϊ�ڶ������������0����Ϊ��NULL�ʲ���Ϊ0
		return;

	if (BinaryTree->size == BinaryTree->MaxSize) // ������������ֵ
		UnusualToExit(FullTree, NULL);

#ifndef AVL_BINARY_TREE
	Pair result = SearchBinaryTreeItem(BinaryTree, pi);

	// if (result.child != NULL)
	// if (result.child != NULL)
	if (result.child) // ��������������*pi
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
	UnusualToExit("������΢�����ڵ�AVL_BINARY_TREE��Ϊ��\n", NULL);
#else
	// if (BinaryTree == NULL || pi == NULL)
	if (!BinaryTree || !pi)
		UnusualToExit(NullPointer, NULL);

	Pair result = SearchBinaryTreeItem(BinaryTree, pi);

	// if (result.child == NULL)
	if (!result.child) // �������в����ڸý��
		UnusualToExit(NoTreeItem, NULL);

	// if (result.child->left != NULL && result.child->right != NULL)
	if (result.child->left && result.child->right) // ����ɾ����������ӽ��
	{
		TreeNode* q;

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
			BinaryTree->root = q;

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
			BinaryTree->root = NULL;
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
				BinaryTree->root = result.child->left;
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
				BinaryTree->root = result.child->right;
			}
		}
	}

	free(result.child);
	--BinaryTree->size;
#endif
}

// �ļ�����/�������
void FileOperationByBinaryTree(Tree * const BinaryTree, const char * const Mode)
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

// ��������
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
		// ����3ѡ1

		// ����1
		// PreOrderTraversal(BinaryTree, Stream);

		// ����2
		Traversal(PreOrderTraversal, BinaryTree, Stream);

		// ����3
		// void(*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = PreOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->LDRFileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->LDRFileName))))
	{
		// ����3ѡ1

		// ����1
		// InOrderTraversal(BinaryTree, Stream);

		// ����2
		Traversal(InOrderTraversal, BinaryTree, Stream);

		// ����3
		// void (*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = InOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->LRDFileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->LRDFileName))))
	{
		// ����3ѡ1

		// ����1
		// PostOrderTraversal(BinaryTree, Stream);

		// ����2
		Traversal(PostOrderTraversal, BinaryTree, Stream);

		// ����3
		// void (*pf) (const Tree * const BinaryTree, FILE * const Stream);
		// pf = PostOrderTraversal;
		// pf(BinaryTree, Stream); // (*pf)(BinaryTree, Stream);
	}

	// if (Stream == stdout || (Stream != stdout && (strcmp(Str, BinaryTree->FileName)== 0)))
	if (Stream == stdout || (Stream != stdout && (!strcmp(Str, BinaryTree->FileName))))
	{
		// ����3ѡ1

		// ����1
		// LevelOrderTraversal(BinaryTree, Stream);

		// ����2
		Traversal(LevelOrderTraversal, BinaryTree, Stream);

		// ����3
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
	if (!pt) // ����
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
	if (!pt) // ����
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
	TreeNode * t = * ptr;

	// if (t == NULL)
	if (!t) // ����
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
	if (!strcmp(Mode, WRITE)) // �ļ����
#ifdef READABLE
		OutputBinaryTreeToMonitor(BinaryTree, FilePointer, FileName); // ���Ϊ�ı��ļ�
#else
		OutputBinaryTreeToBinaryFile(BinaryTree, FilePointer); // ���Ϊ�������ļ�
#endif

	// if (strcmp(Mode, READ) == 0)
	if (!strcmp(Mode, READ)) // �ļ�����
#ifdef READABLE
		InputBinaryTreeFromKeyboard(BinaryTree, FilePointer); // ���ı��ļ�����
#else
		InputBinaryTreeFromBinaryFile(BinaryTree, FilePointer); // �Ӷ������ļ�����
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
	TreeItem * const buffer = (TreeItem *)malloc(((1 << ((sizeof(ElemNumb) << 3) - 1)) - 1) * sizeof(TreeItem));

	// if (buffer == NULL)
	if (!buffer)
		UnusualToExit(MemoryNotEnough, NULL);

	// if (BinaryTree->root != NULL) 
	if (BinaryTree->root)
	{
		LinkList Link;
		CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), NULL);
		EnQueue(&Link, BinaryTree->root); // ���
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

// ǰ�����
static void PreOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// �ǵݹ��㷨
	ArrayList S;
#ifdef LOG
	const char * const FileName = "ǰ������õ��Ķ�ջ����.txt";
#else
	const char * const FileName = NULL;
#endif
	// ��������ʼ����ջS
	CreateListByArray(&S, BinaryTree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\nǰ����� (��->����->����)\n");
#else
	fprintf(Stream, "\nǰ����� (��->����->����)\n");
#endif
	const TreeNode * temp = BinaryTree->root; // ��ʼTΪ������ַ
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( temp != NULL || S.size != 0 )
	while (temp || S.size)
	{
		// while (temp != NULL)
		while (temp) // һֱ���󲢽���;���ѹ���ջ
		{
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // ������
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // ������
#endif	
			++sum;
			Push(&S, temp);
#ifdef LOG
			TextFileAppendOperationByArray(&S);
#endif
			temp = temp->left;
		}

		// if (S.size != 0)
		if (S.size)
		{
			Pop(&S, &TEMP); // ��㵯����ջ
#ifdef LOG
			TextFileAppendOperationByArray(&S);
#endif
			temp = TEMP.right; // ת��������
		}
	}
	DestroyListByArray(&S);
}

// �������
static void InOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// �ǵݹ��㷨
	ArrayList S;
#ifdef LOG
	const char* const FileName = "��������õ��Ķ�ջ����.txt";
#else
	const char * const FileName = NULL;
#endif
	// ��������ʼ����ջS
	CreateListByArray(&S, BinaryTree->size, FileName);
#ifdef WINDOWS_VISUALSTUDIO
	fprintf_s(Stream, "\n������� (����->��->����)\n");
#else
	fprintf(Stream, "\n������� (����->��->����)\n");
#endif
	const TreeNode * T = BinaryTree->root;
	const TreeNode * temp;
	TreeNode TEMP;
	ElemNumb sum = 0;

	// while ( T != NULL || S.size != 0 )
	while (T || S.size)
	{
		// while (T != NULL)
		while (T) // һֱ���󲢽���;���ѹ���ջ
		{
			Push(&S, T);
#ifdef LOG
			TextFileAppendOperationByArray(&S);
#endif
			T = T->left;
		}

		// if (S.size != 0)
		if (S.size)
		{
			Pop(&S, &TEMP); // ��㵯����ջ
#ifdef LOG
			TextFileAppendOperationByArray(&S);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // ������
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // ������
#endif
			++sum;
			T = temp->right; // ת��������
		}
	}
	DestroyListByArray(&S);
}

// �������
static void PostOrderTraversal(const Tree * const BinaryTree, FILE * const Stream)
{
	// if (BinaryTree == NULL || Stream == NULL)
	if (!BinaryTree || !Stream)
		UnusualToExit(NullPointer, NULL);

	// if (BinaryTree->size != 0)
	if (BinaryTree->size)
	{
		// �ǵݹ��㷨
		// ��������ʼ����ջS Q
		ArrayList S;
		CreateListByArray(&S, BinaryTree->size, NULL);
#ifdef LOG
		const char * const FileName = "��������õ��Ķ�ջ����.txt";
#else
		const char * const FileName = NULL;
#endif
		ArrayList Q;
		CreateListByArray(&Q, BinaryTree->size, FileName); // ��������ʼ����ջQ�����ڷ������
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(Stream, "\n������� (����->����->��)\n");
#else
		fprintf(Stream, "\n������� (����->����->��)\n");
#endif
		const TreeNode * T = BinaryTree->root;
		TreeNode TEMP;
		const TreeNode * temp;
		ElemNumb sum = 0;

		// while ( T != NULL || S.size != 0 )
		while (T || S.size)
		{
			// while (T != NULL)
			while (T) // һֱ���Ҳ�����;���ѹ���ջ
			{
				Push(&S, T);
				Push(&Q, T); // ���������Ľ��ѹջ�����ڷ���
#ifdef LOG
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
#ifdef LOG
			TextFileAppendOperationByArray(&Q);
#endif
			temp = &TEMP;
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, OUTPUT_FORMAT, '\n'); // ������
#else
			fprintf(Stream, OUTPUT_FORMAT, '\n'); // ������
#endif
			++sum;
		}
		DestroyListByArray(&S);
		DestroyListByArray(&Q);
	}
}

// �������
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
			fprintf_s(stdout, "\n������� (���϶��� ��������)");
#else
			fprintf(stdout, "\n������� (���϶��� ��������)");
#endif
		fputs("\n", Stream);
		LinkList Link;
		CreateListByLink(&Link, (ElemNumb)(((long long)(1 << ((sizeof(ElemNumb) << 3) - 1))) - 1), QueueFileName);
		EnQueue(&Link, BinaryTree->root); // ���
#ifdef LOG
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
#ifdef LOG
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
#ifdef LOG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->left == NULL)
			else
			{
				EnQueue(&Link, &NullItem);
#ifdef LOG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->right != NULL)
			if (temp->right)
			{
				EnQueue(&Link, temp->right);
#ifdef LOG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			// if (temp->right == NULL)
			else
			{
				EnQueue(&Link, &NullItem);
#ifdef LOG
				TextFileAppendOperationByLink(&Link);
#endif
			}

			if (Link.size == n) // ������Ԫ������Ϊ2��n����
				n <<= 1; // n = 2 * n;
		} // while (QueueIsAllNull(&Link) == false);
		while (!QueueIsAllNull(&Link));
		DestroyListByLink(&Link);
	}

	if (Stream == stdout)
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stdout, "\n��ǰ����%d��Ԫ��\n\n", BinaryTree->size);
#else
		fprintf(stdout, "\n��ǰ����%d��Ԫ��\n\n", BinaryTree->size);
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
