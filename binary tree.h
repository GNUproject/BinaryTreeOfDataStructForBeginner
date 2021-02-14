
// binary tree.h
// ��̬����ƽ�������AVL
/****************************************************************************************************************
����: ����
��������ǿ�� ���г�����������(ADT)��� ֧�ֱ�׼����������ı��ļ�����������������ļ��������
֧��x86��x64���ַ�ʽ����
���л�Windows��Linux��MacOS����ϵͳ
���߳�ŵ����ά��������
�����޶� ������ʱɱ���������ʵΪ��
****************************************************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
// ��ǰ���� ������ѡһ
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

// ��	�Լ���������Ӷ���������
// ��	�Գ��������Ӷ���������
#define STDIN

// ��	����AVLƽ�������
// ��	����AVLƽ�������
// #define AVL

// ��	���ı��ļ��������		�Զ������չ��.txt
// ��	�Զ������ļ��������	�ļ�����չ��
#define READABLE

// ��	������־ģʽ ���ı��ļ���ʽ�Զ���������еĶ�ջ�����е����в��� ���뿪��READABLE����Ч ���ڵ��� 
// ��	�ر���־ģʽ
#define LOG

// ��	���ɴӸ�������ӽ���ָ�� ͬʱ���ɴ��ӽ���������ķ���ָ��
// ��	���ɴӸ�������ӽ���ָ��
// #define BACKWARD_POINTER

/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { false, true } bool;

#ifdef READABLE
	#define	READ	"r"		// �ı��ļ������� ����Сд
	#define WRITE	"w"		// �ı��ļ�д���� ����Сд
#else
	#define READ	"rb"	// �������ļ������� ����Сд
	#define WRITE	"wb"	// �������ļ�д���� ����Сд
#endif

#ifdef LOG
	#define APPEND	"a"		// �ı��ļ�׷��д���� ����Сд
#endif

/******************************************* �� �� Ϊ A D T �� �� �� *******************************************/
// �������������˳��������������(ADT)���
#define INPUT_FORMAT "%d\n",&temp.KeyValue			// �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define OUTPUT_FORMAT "%d%c",temp->Item.KeyValue	// �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define NUMBER_OF_FORMAT 1							// �ṹ��TreeItem�ڵ���������Ŀ

typedef char ElemNumb;	// ˳���������λ ElemNumb��Ϊchar��short��int��long ������Ϊlong long
typedef int Key;

typedef struct
{
	Key KeyValue; // �˴����������Զ��ı�
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
	ElemNumb Height;	// �����ĸ߶�
#endif
} TreeNode;

typedef struct
{
	TreeNode *Root;		// �����ָ��
	ElemNumb Size;		// �����������
	ElemNumb MaxSize;	// ��������������ֵ
} Tree;

typedef struct
{
	TreeNode *Parent;	// ���ҳɹ���Ľ��ĸ�����ַ
	TreeNode *Child;	// ���ҳɹ���Ľ���ַ
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
void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max);

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

// ����:				����������������������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���pi:			�����ݵ�ַ
void AddNodeOfBinaryTree(Tree * const BinaryTree, const TreeItem * const pi);

// ����:				ɾ�����������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���pi:			��ɾ�����ݵ�ַ
void DeleteNodeOfBinaryTree(Tree * const BinaryTree, TreeItem * const pi);

// ����:				���Ҷ������������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���pi:			��ɾ�����ݵ�ַ
// ���ز���:			���ҳɹ�ParentΪ���ҽ��ĸ�����ַ ChildΪ���ҽ��ĵ�ַ	����ʧ��ChildΪNULL
Pair SearchItemOfBinaryTree(const Tree * const BinaryTree, const TreeItem * const pi);

// ����:				�Զ���������ִ���ļ�����/�������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���FileName:	��������������ݵ��ļ���
// ��ڲ���Mode:		ΪREADִ���ļ�������� ΪWRITEִ���ļ��������
void FileOperationWithBinaryTree(Tree * const BinaryTree, const char * const FileName, const char * const Mode);

// ����:				�Ӽ�������������������
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Stream:		�̶�Ϊstdin
void InputBinaryTreeFromKeyboard(Tree * const BinaryTree, FILE * const Stream);

// ����:				����������������������ʾ��
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ��ڲ���Stream:		�̶�Ϊstdout
// ��ڲ���Str:			�̶�ΪNULL
void OutputBinaryTreeToScreen(const Tree * const BinaryTree, FILE * const Stream, const char * const FileName);

// ����:				ȡ�ö�����������С����ֵ
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���ap:			������������С����ֵ
void GetMinNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// ����:				ȡ�ö����������������ֵ
// ��ڲ���BinaryTree:	�ṹ��Tree��������ַ
// ���ڲ���ap:			�����������������ֵ
void GetMaxNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// ����:					�쳣�˳����� �������쳣������ñ��������˳�����
// ��ڲ���str:				�쳣�˳�ԭ���ַ���
// ��ڲ���FileName:		�ļ�����ʧ��ʱ���ļ����ַ��� ���ļ�����ʱΪNULL
void UnusualToExit(const char * const Str, const char * const FileName);

#endif
