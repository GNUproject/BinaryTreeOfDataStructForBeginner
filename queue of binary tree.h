
// �õ���������Ϊ�������õ��Ķ���
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "�ն���\n"
#define FULL_QUEUE "������ ������Max��ElemNumb���ݵ�λ!\n"
#define QUEUE_FORMAT "%d%c",current->Item->Item.KeyValue

/********************************����********************************/
typedef TreeNode *LinkItem;

typedef struct Lnode
{
	LinkItem Item;
	struct Lnode *Next;
}LinkNode;

typedef struct
{
	LinkNode *Head;
	LinkNode *Tail;
	ElemNumb Size;			// ���н������
	ElemNumb MaxSize;		// ���н��������
	const char *FileName;	// ���ļ�������ݵ��ļ���
}LinkList;

/********************************����********************************/

// ����: �����ն���
void CreateQueue(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// ����: �ͷŶ����ڴ�
void DestroyQueue(LinkList * const Link);

#ifdef LOG
// ����:	���������ļ�����
void TextFileOperationWithQueue(LinkList * const Link, const char * const Mode);
#endif

// ����: �����������
void OutputQueueToScreen(const LinkList * const Link, FILE * const Stream);

/********************************* ���в��� *************************************/

// ����: ���
void Enqueue(LinkList * const Link, const LinkItem NewItem);

// ����: ����
void Dequeue(LinkList * const Link, LinkItem * const DelItem);

// ����:	������ÿ�������Ƿ��ΪNULL
// ����ֵ:	ȫ������ΪNULL����true ���򷵻�false
const bool QueueIsAllNull(const LinkList * const Link);

extern void UnusualToExit(const char * const Str, const char * const FileName);

#endif
