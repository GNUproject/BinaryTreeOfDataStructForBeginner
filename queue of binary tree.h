
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
	LinkNode *End;
	ElemNumb Size; // ����������
	ElemNumb MaxSize; // ������������
	const char *FileName; // ���ļ����Ԫ�ص��ļ���
}LinkList;

/********************************����********************************/

// ����: �����ն���
void CreateQueue(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// ����: �ͷŶ����ڴ�
void DestroyQueue(LinkList * const Link);

#ifdef LOG
// ����:	׷���������Ԫ�����ļ�
void TextFileAppendOperationWithQueue(LinkList * const Link);
#endif

// ����: �������Ԫ��
void OutputQueueToScreen(const LinkList * const Link, FILE * const Stream);

/********************************* ���в��� *************************************/

// ����: ���
void Enqueue(LinkList * const Link, const LinkItem NewItem);

// ����: ����
void Dequeue(LinkList * const Link, LinkItem * const DelItem);

// ����:	������ÿ��Ԫ���Ƿ��ΪNULL
// ����ֵ:	ȫ��Ԫ��ΪNULL����true ���򷵻�false
const bool QueueIsAllNull(const LinkList * const Link);

#endif
