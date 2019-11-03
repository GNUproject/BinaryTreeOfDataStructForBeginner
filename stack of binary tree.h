
// ���������������Ķ�ջ
// stack of binary tree.h

#ifndef STACK_OF_BINARY_TREE_H
#define STACK_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_STACK "�ն�ջ\n"
#define FULL_STACK "����ջ ������Max��ElemNumb���ݵ�λ!\n"
#define STACK_FORMAT "%d\n",Array->base[index].item.KeyValue

/********************************����********************************/

typedef TreeNode ArrayItem;

typedef struct
{
	ArrayItem *base; // �����ַ
	ElemNumb size;	// ���鵱ǰ����
	ElemNumb MaxSize; // ������󳤶�
	const char *FileName; // ���ļ����Ԫ�ص��ļ���
}ArrayList;

/********************************����********************************/

void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName);

void DestroyListByArray(ArrayList * const Array);

#ifdef DEBUG
void TextFileAppendOperationByArray(ArrayList * const Array);
#endif

void OutputListByArrayToMonitor(const ArrayList * const Array, FILE * const Stream);

/********************************* ��ջ���� *************************************/

void Push(ArrayList * const Array, const ArrayItem * const NewItem);

void Pop(ArrayList * const Array, ArrayItem * const DelItem);

#endif
