
// queue of binary tree.c

#include "queue of binary tree.h"

static const char * const QueueLengthError = "���г��ȷǷ�\n";

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

	// if (FileName == NULL)
	if (!FileName)
		Link->FileName = NULL;

	// if (FileName != NULL)
	else
	{
		Link->FileName = FileName;
	}
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

#ifdef LOG
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

#ifdef READABLE
		OutputListByLinkToScreen(Link, FilePointer); // �ļ�׷��
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

void OutputListByLinkToScreen(const LinkList * const Link, FILE * const Stream)
{
	// if (Link == NULL || Stream == NULL)
	if (!Link || !Stream)
		UnusualToExit(NullPointer, NULL);

	fputs("\n����\n", Stream);
	const LinkNode * current = Link->head;

	// while (current != NULL)
	while (current)
	{
		// if (current->item->item.KeyValue != 0)
		if (current->item->item.KeyValue)
#ifdef WINDOWS_VISUALSTUDIO
			fprintf_s(Stream, QUEUE_FORMAT, Stream == stdout ? '\t' : '\n');
#else
			fprintf(Stream, QUEUE_FORMAT, Stream == stdout ? '\t' : '\n');
#endif
		// if (current->item->item.KeyValue == 0)
		else
			fputs("NULL\n", Stream);

		current = current->next;
	}
	fputs("��β\n", Stream);
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
