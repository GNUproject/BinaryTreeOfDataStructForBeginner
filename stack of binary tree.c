
// stack of binary tree.c

#include "stack of binary tree.h"

extern const char * const MemoryNotEnough;
extern const char * const NullPointer;
extern const char * const OpenFileError;
extern const char * const CloseFileError;
extern const char * const FileOperationError;
extern const char * const FileNameTooLong;
extern const char * const FileNameError;
extern const char * const WhiteList;
static const char * const StackLengthError = "堆栈长度非法\n";

extern void UnusualToExit(const char * const str, const char * const FileName);
extern void CheckFileName(const char * const FullFileName);

// 创建空顺序表Array
void CreateListByArray(ArrayList * const Array, const ElemNumb Max, const char * const FileName)
{
	// if (Array != NULL)
	if (Array)
	{
		if (Max > 0)
		{
			Array->base = (ArrayItem *)malloc(Max * sizeof(ArrayItem));

			// if (Array->base != NULL)
			if (Array->base)
			{
				Array->size = 0; // 空表长度置0
				Array->MaxSize = Max;

				// if (FileName != NULL)
				if (FileName)
				{
					CheckFileName(FileName);
					Array->FileName = FileName;
				}
			}

			// if (Array->base == NULL)
			else
				UnusualToExit(MemoryNotEnough, NULL);
		}

		// if (Max <= 0)
		else
			UnusualToExit(StackLengthError, NULL);
	}

	// if (Array == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void DestroyListByArray(ArrayList * const Array)
{
	// if (Array != NULL)
	if (Array)
	{
		free(Array->base);
		Array->base = NULL;
		Array->size = Array->MaxSize = 0;
		Array->FileName = NULL;
	}

	// if (Array == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

#ifdef DEBUG
// 文件输出操作
void TextFileAppendOperationByArray(ArrayList * const Array)
{
	// if (Array != NULL)
	if (Array)
	{
		// if (Array->FileName != NULL)
		if (Array->FileName)
		{
#ifdef WINDOWS_VISUALSTUDIO
			FILE *FilePointer;
			const errno_t err = fopen_s(&FilePointer, Array->FileName, APPEND);
			
			// if (err == 0)
			if (!err)
#else
			FILE * const FilePointer = fopen(Array->FileName, APPEND);
			
			// if (FilePointer != NULL)
			if (FilePointer)
#endif
			{
#ifdef CAN_OPEN_FILE
				OutputListByArrayToMonitor(Array, FilePointer); // 文件输出
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

			else
				UnusualToExit(OpenFileError, Array->FileName);
		}
	}

	// if (Array == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}
#endif

// 输出顺序表List的所有元素
void OutputListByArrayToMonitor(const ArrayList * const Array, FILE * const stream)
{
	// if (Array != NULL)
	if (Array)
	{
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

	// if (Array == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void Push(ArrayList * const Array, const ArrayItem * const NewItem)
{
	// if (Array != NULL && NewItem != NULL)
	if (Array && NewItem)
	{
		if (Array->size != Array->MaxSize) // 元素数量未至数据类型极限值
		{
			(Array->base)[Array->size] = *NewItem;
			++Array->size; // 表长增1
		}

		// if (Array->size == Array->MaxSize)
		else // 元素数量已至数据类型极限值
			UnusualToExit(FULL_STACK, NULL);
	}

	// if (Array == NULL || NewItem == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}

void Pop(ArrayList * const Array, ArrayItem * const DelItem)
{
	// if (Array != NULL && DelItem != NULL)
	if (Array && DelItem)
	{
		// if (Array->size != 0)
		if (Array->size) // 顺序表非空
		{
			*DelItem = Array->base[Array->size - 1];
			--Array->size; // 表长减1
		}

		// if (Array->size == 0)
		else // 顺序表为空
			UnusualToExit(EMPTY_STACK, NULL);
	}

	// if (Array == NULL || DelItem == NULL)
	else
		UnusualToExit(NullPointer, NULL);
}
