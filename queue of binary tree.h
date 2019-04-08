
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

// ����ԭ��
// ����:	��ʼ��һ���б�
// ����ǰ:	Linkָ��һ���б�
// ������:	���б���ʼ��Ϊ���б�
void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// ����:	�ͷ��ѷ�����ڴ�(�����)
// ����ǰ:	Linkָ��һ���ѳ�ʼ�����б�
// ������:	Ϊ���б������ڴ��ѱ��ͷ�
// 		���Ҹ��б���Ϊ���б�
void DestroyListByLink(LinkList * const Link);

#ifdef DEBUG
void TextFileAppendOperationByLink(LinkList * const Link);
#endif

// ����:	����б��е�ÿ����Ŀֵ
// ����ǰ:	Linkָ��һ���ѳ�ʼ�����б�
// ������:	����б��е�ÿ����Ŀֵ
void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const stream);

/********************************* ���в��� *************************************/

// ����:�����β�������Ŀ
// ����ǰ:Linkָ��һ����ǰ�ѳ�ʼ�����Ķ��� NewItem��Ҫ��ӵ�����β�˵���Ŀ
// ������:�������δ��,NewItem����ӵ�����β��;����,���ı����
void EnQueue(LinkList * const Link, const LinkItem NewItem);

// ����:�Ӷ����׶�ɾ����Ŀ
// ����ǰ:Linkָ��һ����ǰ�ѳ�ʼ�����Ķ���
// ������:������зǿ�,�����׶˵���Ŀ�����Ƶ�*DelItem,�����Ӷ�����ɾ��,��������True;����ò���ʹ����Ϊ��,�Ѷ�������Ϊ�ն���
//        ���������ʼʱΪ��,���ı����,��������False
void DeQueue(LinkList * const Link, LinkItem * const DelItem);

const bool QueueIsAllNull(const LinkList * const Link);

#endif
