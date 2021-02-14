
// binary tree.h
// 动态搜索平衡二叉树
/****************************************************************************************************************
作者: @CodeHub
本程序功能强大 具有抽象数据类型(ADT)风格 支持标准输入输出、文本文件输入输出、二进制文件输入输出
支持x86和x64两种方式编译
可切换Windows、Linux、MacOS操作系统
作者承诺终生维护本程序
绝对无毒 若编译时杀毒软件报警实为误报
****************************************************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
/******************************************* 以 下 为 程 序 微 调 区 *******************************************/
// 当前环境 以下三选一
#define WINDOWS_VISUALSTUDIO
// #define LINUX_GCC
// #define MACOS_XCODE

// 开	以键盘输入添加二叉树数据
// 关	以程序语句添加二叉树数据
#define STDIN

// 开	启用AVL平衡二叉树
// 关	禁用AVL平衡二叉树
// #define AVL

// 开	以文本文件输入输出		自动添加扩展名.txt
// 关	以二进制文件输入输出	文件无扩展名
#define READABLE

// 开	开启日志模式 以文本文件形式自动输出程序中的堆栈及队列的所有操作 必须开启READABLE才有效 用于调试 
// 关	关闭日志模式
#define LOG

// 开	生成从父结点至子结点的指针 同时生成从子结点至父结点的反向指针
// 关	生成从父结点至子结点的指针
// #define BACKWARD_POINTER

/******************************************* 以 上 为 程 序 微 调 区 *******************************************/
#ifdef WINDOWS_VISUALSTUDIO
	#include <conio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { false, true } bool;

#ifdef READABLE
	#define	READ	"r"		// 文本文件读操作 必须小写
	#define WRITE	"w"		// 文本文件写操作 必须小写
#else
	#define READ	"rb"	// 二进制文件读操作 必须小写
	#define WRITE	"wb"	// 二进制文件写操作 必须小写
#endif

#ifdef LOG
	#define APPEND	"a"		// 文本文件追加写操作 必须小写
#endif

/******************************************* 以 下 为 A D T 数 据 项 *******************************************/
// 以下三行体现了程序抽象数据类型(ADT)风格
#define INPUT_FORMAT "%d\n",&temp.KeyValue			// 此处随结构体TreeItem而改动 替换部分不得包含空格
#define OUTPUT_FORMAT "%d%c",temp->Item.KeyValue	// 此处随结构体TreeItem而改动 替换部分不得包含空格
#define NUMBER_OF_FORMAT 1							// 结构体TreeItem内的数据项数目

typedef char ElemNumb;	// 顺序表数量单位 ElemNumb可为char或short或int或long 但不可为long long
typedef int Key;

typedef struct
{
	Key KeyValue; // 此处随数据属性而改变
	// 此处可添加其他数据类型
} TreeItem;
/******************************************* 以 上 为 A D T 数 据 项 *******************************************/
typedef struct Tnode
{
	TreeItem Item;
#ifdef BACKWARD_POINTER
	struct Tnode *Father;
#endif
	struct Tnode *Left, *Right;
#ifdef AVL
	ElemNumb Height;	// 子树的高度
#endif
} TreeNode;

typedef struct
{
	TreeNode *Root;		// 根结点指针
	ElemNumb Size;		// 二叉树结点数
	ElemNumb MaxSize;	// 二叉树结点数最大值
} Tree;

typedef struct
{
	TreeNode *Parent;	// 查找成功后的结点的父结点地址
	TreeNode *Child;	// 查找成功后的结点地址
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

/********************************操作********************************/

// 功能:				创建空二叉树 为二叉树操作首个调用的函数
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Max:			二叉树最大结点数
void CreateBinaryTree(Tree * const BinaryTree, const ElemNumb Max);

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

// 功能:				将新数据添加至二叉树结点
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数pi:			新数据地址
void AddNodeOfBinaryTree(Tree * const BinaryTree, const TreeItem * const pi);

// 功能:				删除二叉树结点
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数pi:			被删除数据地址
void DeleteNodeOfBinaryTree(Tree * const BinaryTree, TreeItem * const pi);

// 功能:				查找二叉树结点数据
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数pi:			被删除数据地址
// 返回参数:			查找成功Parent为查找结点的父结点地址 Child为查找结点的地址	查找失败Child为NULL
Pair SearchItemOfBinaryTree(const Tree * const BinaryTree, const TreeItem * const pi);

// 功能:				对二叉树数据执行文件输入/输出操作
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数FileName:	输入输出链表数据的文件名
// 入口参数Mode:		为READ执行文件输入操作 为WRITE执行文件输出操作
void FileOperationWithBinaryTree(Tree * const BinaryTree, const char * const FileName, const char * const Mode);

// 功能:				从键盘输入二叉树结点数据
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Stream:		固定为stdin
void InputBinaryTreeFromKeyboard(Tree * const BinaryTree, FILE * const Stream);

// 功能:				将二叉树结点数据输出至显示器
// 入口参数BinaryTree:	结构体Tree变量名地址
// 入口参数Stream:		固定为stdout
// 入口参数Str:			固定为NULL
void OutputBinaryTreeToScreen(const Tree * const BinaryTree, FILE * const Stream, const char * const FileName);

// 功能:				取得二叉树结点的最小数据值
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数ap:			二叉树结点的最小数据值
void GetMinNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// 功能:				取得二叉树结点的最大数据值
// 入口参数BinaryTree:	结构体Tree变量名地址
// 出口参数ap:			二叉树结点的最大数据值
void GetMaxNodeOfBinaryTree(const Tree * const BinaryTree, TreeItem * const ap);

// 功能:					异常退出函数 若遇见异常问题调用本函数后退出程序
// 入口参数str:				异常退出原因字符串
// 入口参数FileName:		文件操作失败时的文件名字符串 无文件操作时为NULL
void UnusualToExit(const char * const Str, const char * const FileName);

#endif
