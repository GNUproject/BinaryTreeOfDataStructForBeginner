
// binary tree.h
// ��̬����ƽ�������AVL
/****************************************************************************************************************
����: ����
��������ǿ�� ���г�����������(ADT)��� ֧�ֱ�׼����������ı��ļ�����������������ļ��������
֧��x86��x64���ַ�ʽ����
���л�Windows��Linux��MacOS����ϵͳ
���߳�ŵ����ά��������
****************************************************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
// ��ǰ���� ������ѡһ
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

// ��	���ɴӸ�������ӽ���ָ�� ͬʱ���ɴ��ӽ���������ķ���ָ��
// ��	���ɴӸ�������ӽ���ָ��
// #define BACKWARD_POINTER

// ��	����AVLƽ�������	ע��:�����󲻵õ���DeleteNodeOfBinaryTree����
// ��	����AVLƽ�������
#define AVL

// ��	�Լ���������Ӷ�����Ԫ��
// ��	�Գ��������Ӷ�����Ԫ��
#define STDIN "ÿ������һ�����ݺ�س� ���������ظ����� �����а�Ctrl + %c��س�����ֹ����\n"

// ��	���ı��ļ�������� CreateBinaryTree�����еĲ���FileName����ΪNULL
// ��	�Զ������ļ�������� CreateBinaryTree�����еĲ���FileName����ΪNULL
#define READABLE

// ��	������־ģʽ ���ı��ļ���ʽ��������еĶ�ջ�����е����в��� ���뿪��READABLE����Ч
// ��	�ر���־ģʽ
#define LOG
/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { false, true } bool;

#ifdef WINDOWS_VISUALSTUDIO
	#define LEN 224 // Windows�ļ������������ַ���
#else
	#define LEN 255 // MacOS�� Linux�ļ������������ַ���
#endif

#ifdef READABLE
	#define	READ	"r" // �ı��ļ������� ����Сд
	#define	WRITE	"w" // �ı��ļ�д���� ����Сд
#else
	#define	READ	"rb" // �������ļ������� ����Сд
	#define	WRITE	"wb" // �������ļ�д���� ����Сд
#endif

#ifdef LOG
	#define APPEND	"a" // �ı��ļ�׷�Ӳ��� ����Сд
#endif
/******************************************* �� �� Ϊ A D T �� �� �� *******************************************/
// �������������˳��������������(ADT)���
#define INPUT_FORMAT "%d\n",&temp.KeyValue // �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define OUTPUT_FORMAT "%d%c",temp->Item.KeyValue // �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define NUMBER_OF_FORMAT 1 // �ṹ��TreeItem�ڵ���������Ŀ

typedef char ElemNumb; // ˳���������λ ElemNumb��Ϊchar��short��int��long ������Ϊlong long
typedef int Key;

typedef struct
{
	Key KeyValue; // �˴���Ԫ�����Զ��ı�
	// �˴������������������
} TreeItem;
/******************************************* �� �� Ϊ A D T �� �� �� *******************************************/
typedef struct Tnode
{
	TreeItem Item;
#ifdef BACKWARD_POINTER
	struct Tnode *Father;
#endif
	struct Tnode *Left, *Right;
#ifdef AVL
	ElemNumb Height; // �����ĸ߶�
#endif
} TreeNode;

typedef struct
{
	TreeNode *Root;
	ElemNumb Size; // �����������
	ElemNumb MaxSize; // ��������������ֵ
	char *DLRFileName; // ǰ������ļ���
	char *LDRFileName; // ��������ļ���
	char *LRDFileName; // ��������ļ���
	char *FileName; // ��������ļ���
} Tree;

typedef struct
{
	TreeNode *Parent; // ���ҳɹ���Ľ��ĸ�����ַ
	TreeNode *Child; // ���ҳɹ���Ľ���ַ
} Pair; 

extern const char * const SameTreeItem;
extern const char * const NoTreeItem;
extern const char * const InputError;
extern const char * const NullPointer;
extern const char * const OpenFileError;
extern const char * const CloseFileError;
extern const char * const FileOperationError;
extern const char * const FileNameTooLong;
extern const char * const FileNameError;
extern const char * const MemoryNotEnough;

/********************************����********************************/

// ����:				�����ն����� Ϊ�����������׸����õĺ���
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Max:			�������������
// ��ڲ���FileName:	�����������Ԫ�ص��ļ��� ��ΪNULL�����ļ������������
void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max, const char * const FileName);

// ����:				�ͷŶ���������ڴ�ռ� Ϊ���������������õĺ���
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
void DestroyBinaryTree(Tree * const BinaryTree);

// ����:				�������Ƿ�Ϊ��
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ����ֵ:				�ն���������true �ǿն���������false
const bool BinaryTreeIsEmpty(const Tree * const BinaryTree);

// ����:				��������������Ƿ�ﵽ���ֵ
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ����ֵ:				������������true ������δ������false
const bool BinaryTreeIsFull(const Tree * const BinaryTree);

// ����:				����Ԫ����������������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���pi:			��Ԫ�ص�ַ
void AddNodeOfBinaryTree(Tree * const BinaryTree, const TreeItem * const pi);

// ����:				ɾ�����������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���pi:			��ɾ��Ԫ�ص�ַ
void DeleteNodeOfBinaryTree(Tree * const BinaryTree, TreeItem * const pi);

// ����:				���Ҷ��������Ԫ��
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���pi:			��ɾ��Ԫ�ص�ַ
// ���ز���:			���ҳɹ�ParentΪ���ҽ��ĸ�����ַ ChildΪ���ҽ��ĵ�ַ	����ʧ��ChildΪNULL
Pair SearchItemOfBinaryTree(const Tree * const BinaryTree, const TreeItem * const pi);

// ����:				�Զ�����Ԫ��ִ���ļ�����/�������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Mode:		ΪREADִ���ļ�������� ΪWRITEִ���ļ��������
void FileOperationWithBinaryTree(Tree * const BinaryTree, const char * const Mode);

// ����:				�Ӽ���������������Ԫ��
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Stream:		�̶�Ϊstdin
void InputBinaryTreeFromKeyboard(Tree * const BinaryTree, FILE * const Stream);

// ����:				�����������Ԫ���������ʾ��
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Stream:		�̶�Ϊstdout
// ��ڲ���Str:			�̶�ΪNULL
void OutputBinaryTreeToScreen(const Tree * const BinaryTree, FILE * const Stream, const char * const Str);

// ����:				ȡ�ö�����������СԪ��ֵ
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���ap:			������������СԪ��ֵ
void GetMinNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// ����:				ȡ�ö������������Ԫ��ֵ
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���ap:			�������������Ԫ��ֵ
void GetMaxNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

extern void UnusualToExit(const char* const Str, const char* const FileName);

#endif
