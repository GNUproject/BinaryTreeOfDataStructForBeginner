
// binary tree.h
// 动态搜索平衡二叉树
/****************************************************************************************************************
作者: 尹俊
本程序功能强大 具有抽象数据类型(ADT)风格 支持标准输入输出、文本文件输入输出、二进制文件输入输出
支持x86和x64两种方式编译
可切换Windows、Linux、MacOS操作系统
****************************************************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/******************************************* 以 下 为 程 序 微 调 区 *******************************************/
/************************
程序代码行		// 表示开
// 程序代码行	// 表示关
************************/

// 当前系统 以下三选一
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

// 开	生成从父结点至子结点的指针 同时生成从子结点至父结点的反向指针
// 关	生成从父结点至子结点的指针
// #define BACKWARD_POINTER

// 开	启用AVL平衡二叉树	注意:开启后不得调用DelBinaryTreeNode函数
// 关	禁用AVL平衡二叉树
// #define AVL_BINARY_TREE

// 开	以键盘输入添加二叉树元素
// 关	以程序语句添加二叉树元素
#define STDIN "每行输入一个数据后回车 在新行按Ctrl + %c后回车以终止输入\n"

// 开	以文本文件输入输出 前提条件CreateBinaryTree函数中的参数FileName不为NULL
// 关	以二进制文件输入输出 前提条件CreateBinaryTree函数中的参数FileName不为NULL
#define CAN_OPEN_FILE

// 开	开启调试模式 以文本文件形式输出程序中的堆栈及队列的所有操作 注:必须开启CAN_OPEN_FILE才有效
// 关	关闭调试模式
#define DEBUG
/******************************************* 以 上 为 程 序 微 调 区 *******************************************/
#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef WINDOWS_VISUALSTUDIO
	#define LEN 224 // Windows文件名长度上限字符数
#else
	#define LEN 255 // MacOS、 Linux文件名长度上限字符数
#endif

#ifdef CAN_OPEN_FILE
	#define	READ "r" // 文本文件读操作 必须小写
	#define	WRITE "w" // 文本文件写操作 必须小写
#else
	#define	READ "rb" // 二进制文件读操作 必须小写
	#define	WRITE "wb" // 二进制文件写操作 必须小写
#endif

#ifdef DEBUG
	#define APPEND "a" // 文本文件追加操作 必须小写
#endif

// 以下三行体现了程序抽象数据类型(ADT)风格
#define INPUT_FORMAT "%d\n",&temp.KeyValue // 此处随结构体TreeItem而改动 替换部分不得包含空格
#define OUTPUT_FORMAT "%d%c",temp->item.KeyValue // 此处随结构体TreeItem而改动 替换部分不得包含空格
#define NUMBER_OF_FORMAT 1 // 结构体TreeItem内的数据项数目

typedef enum { false, true } bool;
typedef char ElemNumb; // 顺序表数量单位 ElemNumb可为char或short或int或long 但不可为long long
typedef int Key;

/********************************属性********************************/
typedef struct
{
	Key KeyValue; // 此处随元素属性而改变
	// 此处可添加其他数据类型
} TreeItem;

typedef struct Tnode
{
	TreeItem item;
#ifdef BACKWARD_POINTER
	struct Tnode *father;
#endif
	struct Tnode *left, *right;
#ifdef AVL_BINARY_TREE
	ElemNumb height; // 子树的高度
#endif
} TreeNode;

typedef struct
{
	TreeNode *root;
	ElemNumb size; // 二叉树结点数
	ElemNumb MaxSize; // 二叉树结点数最大值
	char *DLRFileName; // 前序遍历文件名
	char *LDRFileName; // 中序遍历文件名
	char *LRDFileName; // 后序遍历文件名
	char *FileName; // 层序遍历文件名
} Tree;

typedef struct
{
	TreeNode *parent; // 查找成功后的结点的父结点地址
	TreeNode *child; // 查找成功后的结点地址
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

/********************************操作********************************/
// 操作：把一棵树初始化为空树
// 操作前：tree指向一棵树
// 操作后：该树已被初始化为空树
void CreateBinaryTree(Tree * const tree, const ElemNumb Max, const char * const FileName);

// 操作：从树中删除所有结点
// 操作前：tree指向一棵已经初始化的树
// 操作后：该树为空树
void DestroyBinaryTree(Tree * const tree);

// 操作：确认树是否为空
// 操作前：tree指向一棵树
// 操作后：树为空返回true 非空返回false
const bool BinaryTreeIsEmpty(const Tree * const tree);

// 操作：确认树是否为满
// 操作前：tree指向一棵树
// 操作后：树已满返回true 未满返回false
const bool BinaryTreeIsFull(const Tree * const tree);

// 操作：向树中添加一个结点
// 操作前：tree指向一颗已初始化的树 pi为待添加结点
// 操作后：无
void AddBinaryTreeNode(Tree * const tree, const TreeItem * const pi);

// 操作：从树中删除一个结点
// 操作前：tree指向一棵树
// 操作后：无
// 注意调用DelBinaryTreeNode时必须在程序微调区关闭AVL_BINARY_TREE
void DelBinaryTreeNode(Tree * const tree, TreeItem * const pi);

Pair SearchBinaryTreeItem(const Tree * const tree, const TreeItem * const pi);

void FileOperationByBinaryTree(Tree * const tree, const char * const mode);

void InputBinaryTreeFromKeyboard(Tree * const tree, FILE * const stream);

// 输出二叉树tree的所有元素
void OutputBinaryTreeToMonitor(const Tree * const tree, FILE * const stream, const char * const str);

void GetMinOfBinaryTree(const Tree * const tree, TreeItem * const ap);

void GetMaxOfBinaryTree(const Tree * const tree, TreeItem * const ap);

void UnusualToExit(const char * const str, const char * const FileName);

void CheckFileName(const char * const FullFileName);

extern void UnusualToExit(const char* const str, const char* const FileName);

extern void CheckFileName(const char* const FullFileName);

#endif
