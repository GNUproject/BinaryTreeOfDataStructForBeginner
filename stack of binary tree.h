
// 用数组作为二叉树用到的堆栈
// stack of binary tree.h

#ifndef STACK_OF_BINARY_TREE_H
#define STACK_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_STACK "空堆栈\n"
#define FULL_STACK "满堆栈 请扩充Max或ElemNumb数据单位!\n"
#define STACK_FORMAT "%d\n",Array->Base[index].Item.KeyValue

/********************************属性********************************/

typedef TreeNode ArrayItem;

typedef struct
{
	ArrayItem *Base;		// 堆栈地址
	ElemNumb Size;			// 堆栈当前长度
	ElemNumb MaxSize;		// 堆栈最大长度
}ArrayList;

/********************************操作********************************/
// 功能:	创建空堆栈
void CreateStack(ArrayList * const Array, const ElemNumb Max);

// 功能:	释放堆栈内存空间
void DestroyStack(ArrayList * const Array);

#ifdef LOG
// 功能:	堆栈数据文件操作
void TextFileOperationWithStack(ArrayList * const Array, const char * const FileName, const char * const Mode);
#endif

// 功能:	输出堆栈数据
void OutputStackToScreen(const ArrayList * const Array, FILE * const Stream);

/********************************* 堆栈操作 *************************************/
// 功能:	入栈操作
void Push(ArrayList * const Array, const ArrayItem * const NewItem);

// 功能:	出栈操作
void Pop(ArrayList * const Array, ArrayItem * const DelItem);


extern void UnusualToExit(const char * const Str, const char * const FileName);

#endif
