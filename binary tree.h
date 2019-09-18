
// binary tree.h
// ��̬����ƽ�������
/****************************************************************************************************************
����: ����
��������ǿ�� ���г�����������(ADT)��� ֧�ֱ�׼����������ı��ļ�����������������ļ��������
֧��x86��x64���ַ�ʽ����
���л�Windows��Linux��MacOS����ϵͳ
****************************************************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
/************************
���������		// ��ʾ��
// ���������	// ��ʾ��
************************/

// ��ǰϵͳ ������ѡһ
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

// ��	���ɴӸ�������ӽ���ָ�� ͬʱ���ɴ��ӽ���������ķ���ָ��
// ��	���ɴӸ�������ӽ���ָ��
// #define BACKWARD_POINTER

// ��	����AVLƽ�������	ע��:�����󲻵õ���DelBinaryTreeNode����
// ��	����AVLƽ�������
// #define AVL_BINARY_TREE

// ��	�Լ���������Ӷ�����Ԫ��
// ��	�Գ��������Ӷ�����Ԫ��
#define STDIN "ÿ������һ�����ݺ�س� �����а�Ctrl + %c��س�����ֹ����\n"

// ��	���ı��ļ�������� ǰ������CreateBinaryTree�����еĲ���FileName��ΪNULL
// ��	�Զ������ļ�������� ǰ������CreateBinaryTree�����еĲ���FileName��ΪNULL
#define CAN_OPEN_FILE

// ��	��������ģʽ ���ı��ļ���ʽ��������еĶ�ջ�����е����в��� ע:���뿪��CAN_OPEN_FILE����Ч
// ��	�رյ���ģʽ
#define DEBUG
/******************************************* �� �� Ϊ �� �� ΢ �� �� *******************************************/
#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef WINDOWS_VISUALSTUDIO
	#define LEN 224 // Windows�ļ������������ַ���
#else
	#define LEN 255 // MacOS�� Linux�ļ������������ַ���
#endif

#ifdef CAN_OPEN_FILE
	#define	READ "r" // �ı��ļ������� ����Сд
	#define	WRITE "w" // �ı��ļ�д���� ����Сд
#else
	#define	READ "rb" // �������ļ������� ����Сд
	#define	WRITE "wb" // �������ļ�д���� ����Сд
#endif

#ifdef DEBUG
	#define APPEND "a" // �ı��ļ�׷�Ӳ��� ����Сд
#endif

// �������������˳��������������(ADT)���
#define INPUT_FORMAT "%d\n",&temp.KeyValue // �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define OUTPUT_FORMAT "%d%c",temp->item.KeyValue // �˴���ṹ��TreeItem���Ķ� �滻���ֲ��ð����ո�
#define NUMBER_OF_FORMAT 1 // �ṹ��TreeItem�ڵ���������Ŀ

typedef enum { false, true } bool;
typedef char ElemNumb; // ˳���������λ ElemNumb��Ϊchar��short��int��long ������Ϊlong long
typedef int Key;

/********************************����********************************/
typedef struct
{
	Key KeyValue; // �˴���Ԫ�����Զ��ı�
	// �˴������������������
} TreeItem;

typedef struct Tnode
{
	TreeItem item;
#ifdef BACKWARD_POINTER
	struct Tnode *father;
#endif
	struct Tnode *left, *right;
#ifdef AVL_BINARY_TREE
	ElemNumb height; // �����ĸ߶�
#endif
} TreeNode;

typedef struct
{
	TreeNode *root;
	ElemNumb size; // �����������
	ElemNumb MaxSize; // ��������������ֵ
	char *DLRFileName; // ǰ������ļ���
	char *LDRFileName; // ��������ļ���
	char *LRDFileName; // ��������ļ���
	char *FileName; // ��������ļ���
} Tree;

typedef struct
{
	TreeNode *parent; // ���ҳɹ���Ľ��ĸ�����ַ
	TreeNode *child; // ���ҳɹ���Ľ���ַ
}Pair; 

extern const char* const SameTreeItem;
extern const char* const NoTreeItem;
extern const char* const InputError;
extern const char* const NullPointer;
extern const char* const OpenFileError;
extern const char* const CloseFileError;
extern const char* const FileOperationError;
extern const char* const FileNameTooLong;
extern const char* const FileNameError;
extern const char* const MemoryNotEnough;

/********************************����********************************/
// ��������һ������ʼ��Ϊ����
// ����ǰ��treeָ��һ����
// �����󣺸����ѱ���ʼ��Ϊ����
void CreateBinaryTree(Tree * const tree, const ElemNumb Max, const char * const FileName);

// ������������ɾ�����н��
// ����ǰ��treeָ��һ���Ѿ���ʼ������
// �����󣺸���Ϊ����
void DestroyBinaryTree(Tree * const tree);

// ������ȷ�����Ƿ�Ϊ��
// ����ǰ��treeָ��һ����
// ��������Ϊ�շ���true �ǿշ���false
const bool BinaryTreeIsEmpty(const Tree * const tree);

// ������ȷ�����Ƿ�Ϊ��
// ����ǰ��treeָ��һ����
// ����������������true δ������false
const bool BinaryTreeIsFull(const Tree * const tree);

// ���������������һ�����
// ����ǰ��treeָ��һ���ѳ�ʼ������ piΪ����ӽ��
// ��������
void AddBinaryTreeNode(Tree * const tree, const TreeItem * const pi);

// ������������ɾ��һ�����
// ����ǰ��treeָ��һ����
// ��������
// ע�����DelBinaryTreeNodeʱ�����ڳ���΢�����ر�AVL_BINARY_TREE
void DelBinaryTreeNode(Tree * const tree, TreeItem * const pi);

Pair SearchBinaryTreeItem(const Tree * const tree, const TreeItem * const pi);

void FileOperationByBinaryTree(Tree * const tree, const char * const mode);

void InputBinaryTreeFromKeyboard(Tree * const tree, FILE * const stream);

// ���������tree������Ԫ��
void OutputBinaryTreeToMonitor(const Tree * const tree, FILE * const stream, const char * const str);

void GetMinOfBinaryTree(const Tree * const tree, TreeItem * const ap);

void GetMaxOfBinaryTree(const Tree * const tree, TreeItem * const ap);

void UnusualToExit(const char * const str, const char * const FileName);

void CheckFileName(const char * const FullFileName);

extern void UnusualToExit(const char* const str, const char* const FileName);

extern void CheckFileName(const char* const FullFileName);

#endif
