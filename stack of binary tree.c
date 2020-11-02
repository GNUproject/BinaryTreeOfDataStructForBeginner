
// stack of binary tree.c

#include "stack of binary tree.h"

static const char * const StackLengthError = "��ջ���ȷǷ�\n";

// ������˳���Array
void CreateStack(ArrayList * const Array, const ElemNumb Max, const char * const FileName)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	if (Max <= 0)
		UnusualToExit(StackLengthError, NULL);

	Array->Base = (ArrayItem *)malloc(Max * sizeof(ArrayItem));

	// if (Array->Base == NULL)
	if (!Array->Base)
		UnusualToExit(MemoryNotEnough, NULL);

	Array->Size = 0; // �ձ�����0
	Array->MaxSize = Max;

	// if (FileName == NULL)
	if (!FileName)
		Array->FileName = NULL;

	// if (FileName != NULL)
	else
	{
		Array->FileName = FileName;
	}
}

void DestroyStack(ArrayList * const Array)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	free(Array->Base);
	Array->Base = NULL;
	Array->Size = Array->MaxSize = 0;
	Array->FileName = NULL;
}

#ifdef LOG
// �ļ�׷�Ӳ���
void TextFileOperationWithStack(ArrayList * const Array, const char * const Mode)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	// if (Array->FileName != NULL)
	if (Array->FileName)
	{
#ifdef WINDOWS_VISUALSTUDIO
		FILE * FilePointer;
		const errno_t error = fopen_s(&FilePointer, Array->FileName, Mode);

		// if (error != 0)
		if (error)
#else
		FILE * const restrict FilePointer = fopen(Array->FileName, Mode);

		// if (FilePointer == NULL)
		if (!FilePointer)
#endif
			UnusualToExit(OpenFileError, Array->FileName);
#ifdef READABLE
		// if (strcmp(Mode, APPEND) == 0 || strcmp(Mode, WRITE) == 0)
		if (!strcmp(Mode, APPEND) || !strcmp(Mode, WRITE)) // ��Ϊд������׷�Ӳ���
			// if (strrchr(Mode, 'b') == NULL)
			if (!strrchr(Mode, 'b')) // ��Ϊ�ı��ļ�
				OutputStackToScreen(Array, FilePointer); // �ļ�׷��
#endif
			// if (ferror(FilePointer) != 0)
			if (ferror(FilePointer))
				UnusualToExit(FileOperationError, Array->FileName);

#ifdef WINDOWS_VISUALSTUDIO
			// if (FilePointer != NULL)
			if (FilePointer)
#endif
				// if (fclose(FilePointer) != 0)
				if (fclose(FilePointer))
					UnusualToExit(CloseFileError, Array->FileName);
	}
}
#endif

// ���˳���List����������
void OutputStackToScreen(const ArrayList * const Array, FILE * const Stream)
{
	// if (Array == NULL || Stream == NULL)
	if (!Array || !Stream)
		UnusualToExit(NullPointer, NULL);
		
	fputs("\nջ��\n", Stream);
	ElemNumb index;
	for (index = Array->Size - 1; index >= 0; --index)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(Stream, STACK_FORMAT);
#else
		fprintf(Stream, STACK_FORMAT);
#endif
	}
	fputs("ջ��\n", Stream);
}

void Push(ArrayList * const Array, const ArrayItem * const NewItem)
{
	// if (Array == NULL || NewItem == NULL)
	if (!Array || !NewItem)
		UnusualToExit(NullPointer, NULL);
	
	if (Array->Size == Array->MaxSize) // �������������������ͼ���ֵ
		UnusualToExit(FULL_STACK, NULL);

	Array->Base[Array->Size] = * NewItem;
	++Array->Size; // ����1
}

void Pop(ArrayList * const Array, ArrayItem * const DelItem)
{
	// if (Array == NULL || DelItem == NULL)
	if (!Array || !DelItem)
		UnusualToExit(NullPointer, NULL);

	// if (Array->Size == 0)
	if (!Array->Size) // ˳���Ϊ��
		UnusualToExit(EMPTY_STACK, NULL);

	* DelItem = Array->Base[Array->Size - 1];
	--Array->Size; // ����1
}
