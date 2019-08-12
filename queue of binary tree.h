
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

// 函数原型
// 操作:	初始化一个列表
// 操作前:	Link指向一个列表
// 操作后:	该列表被初始化为空列表
void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName);

// 操作:	释放已分配的内存(如果有)
// 操作前:	Link指向一个已初始化的列表
// 操作后:	为该列表分配的内存已被释放
// 		并且该列表被置为空列表
void DestroyListByLink(LinkList * const Link);

#ifdef DEBUG
void TextFileAppendOperationByLink(LinkList * const Link);
#endif

// 操作:	输出列表中的每个项目值
// 操作前:	Link指向一个已初始化的列表
// 操作后:	输出列表中的每个项目值
void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const stream);

/********************************* 队列操作 *************************************/

// 操作:向队列尾端添加项目
// 操作前:Link指向一个先前已初始化过的队列 NewItem是要添加到队列尾端的项目
// 操作后:如果队列未满,NewItem被添加到队列尾部;否则,不改变队列
void EnQueue(LinkList * const Link, const LinkItem NewItem);

// 操作:从队列首端删除项目
// 操作前:Link指向一个先前已初始化过的队列
// 操作后:如果队列非空,队列首端的项目被复制到*DelItem,并被从队列中删除,函数返回True;如果该操作使队列为空,把队列重置为空队列
//        如果队列起始时为空,不改变队列,函数返回False
void DeQueue(LinkList * const Link, LinkItem * const DelItem);

const bool QueueIsAllNull(const LinkList * const Link);

#endif
