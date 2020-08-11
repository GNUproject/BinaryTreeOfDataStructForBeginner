
// stack of binary tree.c

#include "stack of binary tree.h"

static const char * const StackLengthError = "堆栈长度非法\n";

// 创建空顺序表Array
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

	Array->Size = 0; // 空表长度置0
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
// 文件追加操作
void TextFileAppendOperationWithStack(ArrayList * const Array)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	// if (Array->FileName != NULL)
	if (Array->FileName)
	{
#ifdef WINDOWS_VISUALSTUDIO
		FILE * FilePointer;
		const errno_t error = fopen_s(&FilePointer, Array->FileName, APPEND);

		// if (error != 0)
		if (error)
#else
		FILE * const restrict FilePointer = fopen(Array->FileName, APPEND);

		// if (FilePointer == NULL)
		if (!FilePointer)
#endif
			UnusualToExit(OpenFileError, Array->FileName);
#ifdef READABLE
			OutputStackToScreen(Array, FilePointer); // 文件追加
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

// 输出顺序表List的所有元素
void OutputStackToScreen(const ArrayList * const Array, FILE * const Stream)
{
	// if (Array == NULL || Stream == NULL)
	if (!Array || !Stream)
		UnusualToExit(NullPointer, NULL);
		
	fputs("\n栈底\n", Stream);
	ElemNumb index;
	for (index = 0; index < Array->Size; ++index)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(Stream, STACK_FORMAT);
#else
		fprintf(Stream, STACK_FORMAT);
#endif
	}
	fputs("栈顶\n", Stream);
}

void Push(ArrayList * const Array, const ArrayItem * const NewItem)
{
	// if (Array == NULL || NewItem == NULL)
	if (!Array || !NewItem)
		UnusualToExit(NullPointer, NULL);
	
	if (Array->Size == Array->MaxSize) // 元素数量已至数据类型极限值
		UnusualToExit(FULL_STACK, NULL);

	Array->Base[Array->Size] = * NewItem;
	++Array->Size; // 表长增1
}

void Pop(ArrayList * const Array, ArrayItem * const DelItem)
{
	// if (Array == NULL || DelItem == NULL)
	if (!Array || !DelItem)
		UnusualToExit(NullPointer, NULL);

	// if (Array->Size == 0)
	if (!Array->Size) // 顺序表为空
		UnusualToExit(EMPTY_STACK, NULL);

	* DelItem = Array->Base[Array->Size - 1];
	--Array->Size; // 表长减1
}
