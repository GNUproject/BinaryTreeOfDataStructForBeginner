
// 用单向链表作为二叉树用到的队列
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "空队列\n"
#define FULL_QUEUE "满队列 请扩充Max或ElemNumb数据单位!\n"
#define QUEUE_FORMAT "%d%c",current->item->item.KeyValue

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

// 功能: 创建空队列
void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// 功能: 释放队列内存
void DestroyListByLink(LinkList * const Link);

#ifdef LOG
// 功能:	追加输出队列元素至文件
void TextFileAppendOperationByLink(LinkList * const Link);
#endif

// 功能: 输出队列元素
void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const Stream);

/********************************* 队列操作 *************************************/

// 功能: 入队
void EnQueue(LinkList * const Link, const LinkItem NewItem);

// 功能: 出队
void DeQueue(LinkList * const Link, LinkItem * const DelItem);

// 功能:	队列中每个元素是否均为NULL
// 返回值:	全部元素为NULL返回true 否则返回false
const bool QueueIsAllNull(const LinkList * const Link);

#endif
