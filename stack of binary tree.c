
// stack of binary tree.c

#include "stack of binary tree.h"

static const char * const StackLengthError = "堆栈长度非法\n";

// 创建空顺序表Array
void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	if (Max <= 0)
		UnusualToExit(StackLengthError, NULL);

	Array->base = (ArrayItem *)malloc(Max * sizeof(ArrayItem));

	// if (Array->base == NULL)
	if (!Array->base)
		UnusualToExit(MemoryNotEnough, NULL);

	Array->size = 0; // 空表长度置0
	Array->MaxSize = Max;

	// if (FileName != NULL)
	if (FileName)
	{
		CheckFileName(FileName);
		Array->FileName = FileName;
	}

	// if (FileName == NULL)
	else
		Array->FileName = NULL;
}

void DestroyListByArray(ArrayList * const Array)
{
	// if (Array == NULL)
	if (!Array)
		UnusualToExit(NullPointer, NULL);

	free(Array->base);
	Array->base = NULL;
	Array->size = Array->MaxSize = 0;
	Array->FileName = NULL;
}

#ifdef DEBUG
// 文件追加操作
void TextFileAppendOperationByArray(ArrayList * const Array)
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
		FILE * const FilePointer = fopen(Array->FileName, APPEND);

		// if (FilePointer == NULL)
		if (!FilePointer)
#endif
			UnusualToExit(OpenFileError, Array->FileName);
#ifdef CAN_OPEN_FILE
			OutputListByArrayToMonitor(Array, FilePointer); // 文件追加
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
void OutputListByArrayToMonitor(const ArrayList * const Array, FILE * const stream)
{
	// if (Array == NULL || stream == NULL)
	if (!Array || !stream)
		UnusualToExit(NullPointer, NULL);
		
	fputs("\n", stream);
	ElemNumb index;
	for (index = 0; index < Array->size; ++index)
	{
#ifdef WINDOWS_VISUALSTUDIO
		fprintf_s(stream, STACK_FORMAT);
#else
		fprintf(stream, STACK_FORMAT);
#endif
	}
}

void Push(ArrayList * const Array, const ArrayItem * const NewItem)
{
	// if (Array == NULL || NewItem == NULL)
	if (!Array || !NewItem)
		UnusualToExit(NullPointer, NULL);
	
	if (Array->size == Array->MaxSize) // 元素数量已至数据类型极限值
		UnusualToExit(FULL_STACK, NULL);

	Array->base[Array->size] = * NewItem;
	++Array->size; // 表长增1
}

void Pop(ArrayList * const Array, ArrayItem * const DelItem)
{
	// if (Array == NULL || DelItem == NULL)
	if (!Array || !DelItem)
		UnusualToExit(NullPointer, NULL);

	// if (Array->size == 0)
	if (!Array->size) // 顺序表为空
		UnusualToExit(EMPTY_STACK, NULL);

	* DelItem = Array->base[Array->size - 1];
	--Array->size; // 表长减1
}
