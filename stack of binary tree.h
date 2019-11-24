
// 用数组作为二叉树用到的堆栈
// stack of binary tree.h

#ifndef STACK_OF_BINARY_TREE_H
#define STACK_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_STACK "空堆栈\n"
#define FULL_STACK "满堆栈 请扩充Max或ElemNumb数据单位!\n"
#define STACK_FORMAT "%d\n",Array->base[index].item.KeyValue

/********************************属性********************************/

typedef TreeNode ArrayItem;

typedef struct
{
	ArrayItem *base; // 数组地址
	ElemNumb size;	// 数组当前长度
	ElemNumb MaxSize; // 数组最大长度
	const char *FileName; // 向文件输出元素的文件名
}ArrayList;

/********************************操作********************************/
// 功能:	创建空堆栈
void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName);

// 功能:	释放堆栈内存空间
void DestroyListByArray(ArrayList * const Array);

#ifdef LOG
// 功能:	追加输出堆栈元素至文件
void TextFileAppendOperationByArray(ArrayList * const Array);
#endif

// 功能:	输出堆栈元素
void OutputListByArrayToMonitor(const ArrayList * const Array, FILE * const Stream);

/********************************* 堆栈操作 *************************************/
// 功能:	入栈操作
void Push(ArrayList * const Array, const ArrayItem * const NewItem);

// 功能:	出栈操作
void Pop(ArrayList * const Array, ArrayItem * const DelItem);

#endif
