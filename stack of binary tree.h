
// ��������Ϊ�������õ��Ķ�ջ
// stack of binary tree.h

#ifndef STACK_OF_BINARY_TREE_H
#define STACK_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_STACK "�ն�ջ\n"
#define FULL_STACK "����ջ ������Max��ElemNumb���ݵ�λ!\n"
#define STACK_FORMAT "%d\n",Array->Base[index].Item.KeyValue

/********************************����********************************/

typedef TreeNode ArrayItem;

typedef struct
{
	ArrayItem *Base;		// ��ջ��ַ
	ElemNumb Size;			// ��ջ��ǰ����
	ElemNumb MaxSize;		// ��ջ��󳤶�
}ArrayList;

/********************************����********************************/
// ����:	�����ն�ջ
void CreateStack(ArrayList * const Array, const ElemNumb Max);

// ����:	�ͷŶ�ջ�ڴ�ռ�
void DestroyStack(ArrayList * const Array);

#ifdef LOG
// ����:	��ջ�����ļ�����
void TextFileOperationWithStack(ArrayList * const Array, const char * const FileName, const char * const Mode);
#endif

// ����:	�����ջ����
void OutputStackToScreen(const ArrayList * const Array, FILE * const Stream);

/********************************* ��ջ���� *************************************/
// ����:	��ջ����
void Push(ArrayList * const Array, const ArrayItem * const NewItem);

// ����:	��ջ����
void Pop(ArrayList * const Array, ArrayItem * const DelItem);


extern void UnusualToExit(const char * const Str, const char * const FileName);

#endif
