
// binary tree.h
// 动态搜索平衡二叉树
/****************************************************************************************************************
作者: 微博@GNU计划
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
#define STDIN "每行输入一个数据后回车 不得输入重复数据 在新行按Ctrl + %c后回车以终止输入\n"

// 开	以文本文件输入输出 前提条件CreateBinaryTree函数中的参数FileName不为NULL
// 关	以二进制文件输入输出 前提条件CreateBinaryTree函数中的参数FileName不为NULL
#define CAN_OPEN_FILE

// 开	开启调试模式 以文本文件形式输出程序中的堆栈及队列的所有操作 必须开启CAN_OPEN_FILE才有效
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
} Pair; 

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

// 功能:				创建空二叉树 为二叉树操作首个调用的函数
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Max:			二叉树最大结点数
// 入口参数FileName:	输入输出链表元素的文件名 若为NULL则无文件输入输出功能
void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max, const char * const FileName);

// 功能:				释放二叉树结点内存空间 为二叉树操作最后调用的函数
// 入口参数BinaryTree:	结构体Tree变量名地址
void DestroyBinaryTree(Tree * const BinaryTree);

// 功能:				二叉树是否为空
// 入口参数BinaryTree:	结构体Tree变量名地址
// 返回值:				空二叉树返回true 非空二叉树返回false
const bool BinaryTreeIsEmpty(const Tree * const BinaryTree);

// 功能:				二叉树结点数量是否达到最大值
// 入口参数BinaryTree:	结构体Tree变量名地址
// 返回值:				满二叉树返回true 二叉树未满返回false
const bool BinaryTreeIsFull(const Tree * const BinaryTree);

// 功能:				将新元素添加至二叉树结点
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数pi:			新元素地址
void AddBinaryTreeNode(Tree * const BinaryTree, const TreeItem * const pi);

// 功能:				删除二叉树结点
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数pi:			被删除元素地址
void DelBinaryTreeNode(Tree * const BinaryTree, TreeItem * const pi);

// 功能:				查找二叉树结点元素
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数pi:			被删除元素地址
// 返回参数:			查找成功parent为查找结点的父结点地址 child为查找结点的地址	查找失败child为NULL
Pair SearchBinaryTreeItem(const Tree * const BinaryTree, const TreeItem * const pi);

// 功能:				对二叉树元素进行文件输入/输出操作
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Mode:		为READ进行文件输入操作 为WRITE进行文件输出操作
void FileOperationByBinaryTree(Tree * const BinaryTree, const char * const Mode);

// 功能:				从键盘输入二叉树结点元素
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Stream:		固定为stdin
void InputBinaryTreeFromKeyboard(Tree * const BinaryTree, FILE * const Stream);

// 功能:				将二叉树结点元素输出至显示器
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Stream:		固定为stdout
// 入口参数Str:			固定为NULL
void OutputBinaryTreeToMonitor(const Tree * const BinaryTree, FILE * const Stream, const char * const Str);

// 功能:				取得二叉树结点的最小元素值
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数ap:			二叉树结点的最小元素值
void GetMinOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// 功能:				取得二叉树结点的最大元素值
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数ap:			二叉树结点的最大元素值
void GetMaxOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

extern void UnusualToExit(const char* const Str, const char* const FileName);

extern void CheckFileName(const char* const FullFileName);

#endif
