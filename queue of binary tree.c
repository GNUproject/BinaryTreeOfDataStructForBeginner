
// queue of binary tree.c

#include "queue of binary tree.h"

static const char * const QueueLengthError = "队列长度非法\n";

// 接口函数

// 把链表设为空列表
// 参数Link为链表指针 Max为链表结点数最大值 FileName为欲输出链表数据的文件名
void CreateQueue(LinkList * const Link, const ElemNumb Max, const char * const FileName)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	if (Max <= 0)
		UnusualToExit(QueueLengthError, NULL);

	Link->Head = Link->Tail = NULL;
	Link->Size = 0;
	Link->MaxSize = Max;

	// if (FileName == NULL)
	if (!FileName)
		Link->FileName = NULL;

	// if (FileName != NULL)
	else
	{
		Link->FileName = FileName;
	}
}

// 释放由malloc ( )分配的内存
// 把列表指针设置为NULL
void DestroyQueue(LinkList * const Link)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	LinkNode * assist = Link->Head;

	// while (assist != NULL)
	while (assist)
	{
		assist = Link->Head->Next; // 保存下一个结点的地址
		free(Link->Head); // 释放当前结点
		Link->Head = assist; // 前进到下一个结点
	}
	Link->Head = Link->Tail = NULL;
	Link->Size = Link->MaxSize = 0;
	Link->FileName = NULL;
}

#ifdef LOG
// 文件追加操作
void TextFileOperationWithQueue(LinkList * const Link, const char * const Mode)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	// if (Link->FileName != NULL)
	if (Link->FileName)
	{
#ifdef WINDOWS_VISUALSTUDIO
		FILE * FilePointer;
		const errno_t error = fopen_s(&FilePointer, Link->FileName, Mode);

		// if (error != 0)
		if (error)
#else
		FILE * const restrict FilePointer = fopen(Link->FileName, Mode);

		// if (FilePointer == NULL)
		if (!FilePointer)
#endif
			UnusualToExit(OpenFileError, Link->FileName);

#ifdef READABLE
		// if (strcmp(Mode, APPEND) == 0 || strcmp(Mode, WRITE) == 0)
		if (!strcmp(Mode, APPEND) || !strcmp(Mode, WRITE)) // 若为写操作或追加操作
			// if (strrchr(Mode, 'b') == NULL)
			if (!strrchr(Mode, 'b')) // 若为文本文件
				OutputQueueToScreen(Link, FilePointer);
#endif
		// if (ferror(FilePointer) != 0)
		if (ferror(FilePointer))
			UnusualToExit(FileOperationError, Link->FileName);

#ifdef WINDOWS_VISUALSTUDIO
		// if (FilePointer != NULL)
		if (FilePointer)
#endif
			// if (fclose(FilePointer) != 0)
			if (fclose(FilePointer))
				UnusualToExit(CloseFileError, Link->FileName);	
	}
}
#endif

void OutputQueueToScreen(const LinkList * const Link, FILE * const Stream)
{
	// if (Link == NULL || Stream == NULL)
	if (!Link || !Stream)
		UnusualToExit(NullPointer, NULL);

	fputs("\n队首\n", Stream);
	const LinkNode * current = Link->Head;

	// while (current != NULL)
	while (current)
	{
		// if (current->Item->Item.KeyValue != 0)
		if (current->Item->Item.KeyValue)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, QUEUE_FORMAT, Stream == stdout ? '\t' : '\n');
#else
			fprintf(Stream, QUEUE_FORMAT, Stream == stdout ? '\t' : '\n');
#endif
		// if (current->Item->Item.KeyValue == 0)
		else
			fputs("NULL\n", Stream);

		current = current->Next;
	}
	fputs("队尾\n", Stream);
}

void Enqueue(LinkList * const Link, const LinkItem NewItem)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	if (Link->Size == Link->MaxSize)
		UnusualToExit(FULL_QUEUE, NULL);

	LinkNode * const NewNode = (LinkNode *)malloc(sizeof(LinkNode));

	// if (NewNode == NULL)
	if (!NewNode)
		UnusualToExit(MemoryNotEnough, NULL);

	// if (Link->Size != 0) 
	if (Link->Size) // 链表有结点
		Link->Tail->Next = NewNode;

	// if (Link->Size == 0)
	else // 链表无结点
		Link->Head = NewNode;

	Link->Tail = NewNode;
	NewNode->Next = NULL;

	NewNode->Item = NewItem;
	++Link->Size;
}

void Dequeue(LinkList * const Link, LinkItem * const DelItem)
{
	// if (Link == NULL || DelItem == NULL)
	if (!Link || !DelItem)
		UnusualToExit(NullPointer, NULL);

	// if (Link->Size == 0)
	if (!Link->Size) // 链表中无结点
		UnusualToExit(EMPTY_QUEUE, NULL);

	LinkNode * const pnode = Link->Head;
	Link->Head = Link->Head->Next;

	// if (Link->Head == NULL)
	if (!Link->Head)
		Link->Tail = NULL;
	* DelItem = pnode->Item;
	free(pnode);
	--Link->Size;
}

// 队列全为0 返回ture
// 否则返回false
const bool QueueIsAllNull(const LinkList * const Link)
{
	// if (Link == NULL)
	if (!Link)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer, NULL);
		_getch();
#else
		fprintf(stderr, NullPointer, NULL);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}

	const LinkNode * ptr = Link->Head;

	// while (ptr != NULL)
	while (ptr)
	{
		// if (ptr->Item->Item.KeyValue != 0)
		if (ptr->Item->Item.KeyValue)
			return false;
		ptr = ptr->Next;
	}
	// 此时ptr->Next == NULL
	return true;
}
