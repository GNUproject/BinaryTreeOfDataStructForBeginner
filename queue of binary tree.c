
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
	// if (Link != NULL)
	if (Link)
	{
		Link->head = Link->tail = NULL;
		Link->size = 0;

		if (Max > 0)
		{
			Link->MaxSize = Max;

			// if (FileName != NULL)
			if (FileName)
			{
				CheckFileName(FileName);
				Link->FileName = FileName;
			}
		}

		// if (Max <= 0)
		else
			UnusualToExit(QueueLengthError, NULL);
	}

	// if (Link == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// �ͷ���malloc ( )������ڴ�
// ���б�ָ������ΪNULL
void DestroyListByLink(LinkList * const Link)
{
	// if (Link != NULL)
	if (Link)
	{
		LinkNode *assist = Link->head;
		
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

	// if (Link == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

#ifdef DEBUG
// �ļ��������
void TextFileAppendOperationByLink(LinkList * const Link)
{
	// if (Link != NULL)
	if (Link)
	{
		// if (Link->FileName != NULL)
		if (Link->FileName)
		{
#ifdef WINDOWS_VISUALSTUDIO
			FILE *FilePointer;
			const errno_t err = fopen_s(&FilePointer, Link->FileName, APPEND);

			// if (err == 0)
			if (!err)
#else
			FILE * const FilePointer = fopen(Link->FileName, APPEND);
			
			// if (FilePointer != NULL)
			if (FilePointer)
#endif
			{
#ifdef CAN_OPEN_FILE
				OutputListByLinkToMonitor(Link, FilePointer); // �ļ����
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

			else
				UnusualToExit(OpenFileError, Link->FileName);
		}
	}

	// if (Link == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}
#endif

void OutputListByLinkToMonitor(const LinkList * const Link, FILE * const stream)
{
	// if (Link != NULL && stream != NULL)
	if (Link && stream)
	{
		fputs("\n", stream);
		const LinkNode *current = Link->head;
		
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

	// if (Link == NULL || stream == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void EnQueue(LinkList * const Link, const LinkItem NewItem)
{
	// if (Link != NULL)
	if (Link)
	{
		if (Link->size != Link->MaxSize)
		{
			LinkNode * const NewNode = (LinkNode *)malloc(sizeof(LinkNode));

			// if (NewNode != NULL)
			if (NewNode)
			{
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

			// if (NewNode == NULL)
			else
				UnusualToExit(MemoryNotEnough, NULL);
		}

		// if (Link->size == Link->MaxSize)
		else
			UnusualToExit(FULL_QUEUE, NULL);
	}

	// if (Link == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void DeQueue(LinkList * const Link, LinkItem * const DelItem)
{
	// if (Link != NULL && DelItem != NULL)
	if (Link && DelItem)
	{
		// if (Link->size != 0)
		if (Link->size) // �������н��
		{
			LinkNode * const pnode = Link->head;
			Link->head = Link->head->next;
			
			// if (Link->head == NULL)
			if (!Link->head)
				Link->tail = NULL;
			*DelItem = pnode->item;
			free(pnode);
			--Link->size;
		}

		// if (Link->size == 0)
		else // �������޽��
			UnusualToExit(EMPTY_QUEUE, NULL);
	}

	// if (Link == NULL || DelItem == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

// ����ȫΪ0 ����ture
// ���򷵻�false
const bool QueueIsAllNull(const LinkList * const Link)
{
	// if (Link != NULL)
	if (Link)
	{
		const LinkNode *ptr = Link->head;
		
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

	// if (Link == NULL)
	else
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stderr, NullPointer, NULL);
		_getch();
#else
		fprintf(stderr, NullPointer, NULL);
#endif
		exit(EXIT_FAILURE); // exit (1);
	}
}
