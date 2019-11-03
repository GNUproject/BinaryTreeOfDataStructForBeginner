
// ���������������Ķ���
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "�ն���\n"
#define FULL_QUEUE "������ ������Max��ElemNumb���ݵ�λ!\n"
#define QUEUE_FARMAT "%d%c",current->item->item.KeyValue

/********************************����********************************/
typedef TreeNode *LinkItem;

typedef struct Lnode
{
	LinkItem item;
	struct Lnode *next;
}LinkNode;

typedef struct
{
	LinkNode *head;
	LinkNode *tail;
	ElemNumb size; // ����������
	ElemNumb MaxSize; // ������������
	const char *FileName; // ���ļ����Ԫ�ص��ļ���
}LinkList;

/********************************����********************************/

void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);


void DestroyListByLink(LinkList * const Link);

#ifdef DEBUG
void TextFileAppendOperationByLink(LinkList * const Link);
#endif


void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const Stream);

/********************************* ���в��� *************************************/

void EnQueue(LinkList * const Link, const LinkItem NewItem);

void DeQueue(LinkList * const Link, LinkItem * const DelItem);

const bool QueueIsAllNull(const LinkList * const Link);

#endif
