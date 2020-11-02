
// 用单向链表作为二叉树用到的队列
// queue of binary tree.h

#ifndef QUEUE_OF_BINARY_TREE_H
#define QUEUE_OF_BINARY_TREE_H
#include "binary tree.h"

#define EMPTY_QUEUE "空队列\n"
#define FULL_QUEUE "满队列 请扩充Max或ElemNumb数据单位!\n"
#define QUEUE_FORMAT "%d%c",current->Item->Item.KeyValue

/********************************属性********************************/
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
	ElemNumb Size;			// 队列结点数量
	ElemNumb MaxSize;		// 队列结点数上限
	const char *FileName;	// 向文件输出数据的文件名
}LinkList;

/********************************操作********************************/

// 功能: 创建空队列
void CreateQueue(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// 功能: 释放队列内存
void DestroyQueue(LinkList * const Link);

#ifdef LOG
// 功能:	队列数据文件操作
void TextFileOperationWithQueue(LinkList * const Link, const char * const Mode);
#endif

// 功能: 输出队列数据
void OutputQueueToScreen(const LinkList * const Link, FILE * const Stream);

/********************************* 队列操作 *************************************/

// 功能: 入队
void Enqueue(LinkList * const Link, const LinkItem NewItem);

// 功能: 出队
void Dequeue(LinkList * const Link, LinkItem * const DelItem);

// 功能:	队列中每个数据是否均为NULL
// 返回值:	全部数据为NULL返回true 否则返回false
const bool QueueIsAllNull(const LinkList * const Link);

extern void UnusualToExit(const char * const Str, const char * const FileName);

#endif
