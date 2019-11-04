
// 以链表作二叉树的队列
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "空队列\n"
#define FULL_QUEUE "满队列 请扩充Max或ElemNumb数据单位!\n"
#define QUEUE_FARMAT "%d%c",current->item->item.KeyValue

/********************************属性********************************/
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
	ElemNumb size; // 链表结点数量
	ElemNumb MaxSize; // 链表结点数上限
	const char *FileName; // 向文件输出元素的文件名
}LinkList;

/********************************操作********************************/

void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);


void DestroyListByLink(LinkList * const Link);

#ifdef DEBUG
void TextFileAppendOperationByLink(LinkList * const Link);
#endif


void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const Stream);

/********************************* 队列操作 *************************************/

void EnQueue(LinkList * const Link, const LinkItem NewItem);

void DeQueue(LinkList * const Link, LinkItem * const DelItem);

const bool QueueIsAllNull(const LinkList * const Link);

#endif
