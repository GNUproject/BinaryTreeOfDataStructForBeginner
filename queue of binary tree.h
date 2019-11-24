
// �õ���������Ϊ�������õ��Ķ���
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "�ն���\n"
#define FULL_QUEUE "������ ������Max��ElemNumb���ݵ�λ!\n"
#define QUEUE_FORMAT "%d%c",current->item->item.KeyValue

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

// ����: �����ն���
void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// ����: �ͷŶ����ڴ�
void DestroyListByLink(LinkList * const Link);

#ifdef LOG
// ����:	׷���������Ԫ�����ļ�
void TextFileAppendOperationByLink(LinkList * const Link);
#endif

// ����: �������Ԫ��
void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const Stream);

/********************************* ���в��� *************************************/

// ����: ���
void EnQueue(LinkList * const Link, const LinkItem NewItem);

// ����: ����
void DeQueue(LinkList * const Link, LinkItem * const DelItem);

// ����:	������ÿ��Ԫ���Ƿ��ΪNULL
// ����ֵ:	ȫ��Ԫ��ΪNULL����true ���򷵻�false
const bool QueueIsAllNull(const LinkList * const Link);

#endif
