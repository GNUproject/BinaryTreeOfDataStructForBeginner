
// queue of binary tree.c

#include "queue of binary tree.h"

extern const char * const MemoryNotEnough;
extern const char * const NullPointer;
extern const char * const OpenFileError;
extern const char * const CloseFileError;
extern const char * const FileOperationError;
extern const char * const FileNameTooLong;
extern const char * const FileNameError;
extern const char * const WhiteList;
static const char * const QueueLengthError = "���г��ȷǷ�\n";

extern void UnusualToExit(const char * const str, const char * const FileName);
extern void CheckFileName(const char * const FullFileName);

// �ӿں���

// ��������Ϊ���б�
// ����LinkΪ����ָ�� MaxΪ�����������ֵ FileNameΪ���������Ԫ�ص��ļ���
void CreateListByLink(LinkList * const Link, const ElemNumb Max, const char * const FileName)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	if (Max <= 0)
		UnusualToExit(QueueLengthError, NULL);

	Link->head = Link->tail = NULL;
	Link->size = 0;
	Link->MaxSize = Max;

	// if (FileName != NULL)
	if (FileName)
	{
		CheckFileName(FileName);
		Link->FileName = FileName;
	}

	// if (FileName == NULL)
	else
		Link->FileName = NULL;
}

// �ͷ���malloc ( )������ڴ�
// ���б�ָ������ΪNULL
void DestroyListByLink(LinkList * const Link)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	LinkNode * assist = Link->head;

	// while (assist != NULL)
	while (assist)
	{
		assist = Link->head->next; // ������һ�����ĵ�ַ
		free(Link->head); // �ͷŵ�ǰ���
		Link->head = assist; // ǰ������һ�����
	}
	Link->head = Link->tail = NULL;
	Link->size = Link->MaxSize = 0;
	Link->FileName = NULL;
}

#ifdef DEBUG
// �ļ�׷�Ӳ���
void TextFileAppendOperationByLink(LinkList * const Link)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	// if (Link->FileName != NULL)
	if (Link->FileName)
	{
#ifdef WINDOWS_VISUALSTUDIO
		FILE * FilePointer;
		const errno_t error = fopen_s(&FilePointer, Link->FileName, APPEND);

		// if (error != 0)
		if (error)
#else
		FILE * const FilePointer = fopen(Link->FileName, APPEND);

		// if (FilePointer == NULL)
		if (!FilePointer)
#endif
			UnusualToExit(OpenFileError, Link->FileName);

#ifdef CAN_OPEN_FILE
		OutputListByLinkToMonitor(Link, FilePointer); // �ļ�׷��
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

void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const stream)
{
	// if (Link == NULL || stream == NULL)
	if (!Link || !stream)
		UnusualToExit(NullPointer, NULL);

	fputs("\n", stream);
	const LinkNode * current = Link->head;

	// while (current != NULL)
	while (current)
	{
		// if (current->item->item.KeyValue != 0)
		if (current->item->item.KeyValue)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(stream, QUEUE_FARMAT, stream == stdout ? '\t' : '\n');
#else
			fprintf(stream, QUEUE_FARMAT, stream == stdout ? '\t' : '\n');
#endif
		// if (current->item->item.KeyValue == 0)
		else
			fputs("NULL\n", stream);

		current = current->next;
	}
}

void EnQueue(LinkList * const Link, const LinkItem NewItem)
{
	// if (Link == NULL)
	if (!Link)
		UnusualToExit(NullPointer, NULL);

	if (Link->size == Link->MaxSize)
		UnusualToExit(FULL_QUEUE, NULL);

	LinkNode * const NewNode = (LinkNode *)malloc(sizeof(LinkNode));

	// if (NewNode == NULL)
	if (!NewNode)
		UnusualToExit(MemoryNotEnough, NULL);

	// if (Link->size != 0) 
	if (Link->size) // �����н��
		Link->tail->next = NewNode;

	// if (Link->size == 0)
	else // �����޽��
		Link->head = NewNode;

	Link->tail = NewNode;
	NewNode->next = NULL;

	NewNode->item = NewItem;
	++Link->size;
}

void DeQueue(LinkList * const Link, LinkItem * const DelItem)
{
	// if (Link == NULL || DelItem == NULL)
	if (!Link || !DelItem)
		UnusualToExit(NullPointer, NULL);

	// if (Link->size == 0)
	if (!Link->size) // �������޽��
		UnusualToExit(EMPTY_QUEUE, NULL);

	LinkNode * const pnode = Link->head;
	Link->head = Link->head->next;

	// if (Link->head == NULL)
	if (!Link->head)
		Link->tail = NULL;
	* DelItem = pnode->item;
	free(pnode);
	--Link->size;
}

// ����ȫΪ0 ����ture
// ���򷵻�false
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

	const LinkNode * ptr = Link->head;

	// while (ptr != NULL)
	while (ptr)
	{
		// if (ptr->item->item.KeyValue != 0)
		if (ptr->item->item.KeyValue)
			return false;
		ptr = ptr->next;
	}
	// ��ʱptr->next == NULL
	return true;
}
