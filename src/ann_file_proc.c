#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "ann_file_proc.h"
#include "ann_file_header.h"

#include "debug.h"

int ann_str_extract(char*** strListPtr, int* strCountPtr, char* src, char sepCh)
{
	int procIndex;
	int finish;
	int iResult;
	int retValue = ANN_NO_ERROR;
	
	char** strList = NULL;
	int strCount = 0;

	void* allocTmp = NULL;

	struct ANN_STR tmpStr;
	
	LOG("enter");

	// Zero memory
	ann_str_zeromem(&tmpStr);

	// Assign values
	*strListPtr = strList;
	*strCountPtr = strCount;

	procIndex = 0;
	finish = 0;
	while(finish == 0)
	{
		if(src[procIndex] == sepCh || src[procIndex] == '\0')
		{
			if(tmpStr.str != NULL)
			{
				allocTmp = realloc(strList, sizeof(char**) * (strCount + 1));
				if(allocTmp == NULL)
				{
					retValue = ANN_NO_ERROR;
					goto ERR;
				}
				else
				{
					strList = allocTmp;
					strCount += 1;
					allocTmp = NULL;
				}

				strList[strCount - 1] = tmpStr.str;
				tmpStr.str = NULL;
				tmpStr.size = 1;

				if(src[procIndex] == '\0')
				{
					finish = 1;
				}
			}
		}
		else
		{
			iResult = ann_str_append(&tmpStr, src[procIndex]);
			if(iResult != ANN_NO_ERROR)
			{
				retValue = iResult;
				goto ERR;
			}
		}

		procIndex++;
	}

	// Assign values
	*strListPtr = strList;
	*strCountPtr = strCount;
	
	goto RET;

ERR:	
	if(strList != NULL)
	{
		for(procIndex = 0; procIndex < strCount; procIndex++)
		{
			if(strList[procIndex] != NULL)
				free(strList[procIndex]);
		}
		free(strList);
	}

RET:
	ann_str_delete(&tmpStr);

	LOG("exit");

	return retValue;
}

struct ANN_FILE_BLOCK* ann_find_fblock(struct ANN_FILE_STRUCT* fStructPtr, int headerID)
{
	int i;
	struct ANN_FILE_BLOCK* fptr = NULL;
	
	LOG("enter");

	for(i = 0; i < fStructPtr->blockCount; i++)
	{
		if(ann_strcmp(fStructPtr->blockList[i].header, ann_file_header[headerID]) == 0)
		{
			fptr = &fStructPtr->blockList[i];
			break;
		}
	}
	
	LOG("exit");

	return fptr;
}

int ann_strcmp(char* src1, char* src2)
{
	int cmpLen;
	int srcLen;
	int retValue = 0;

	LOG("enter");

	cmpLen = strlen(src1);
	srcLen = strlen(src2);
	if(cmpLen != srcLen)
	{
		retValue = -1;
	}
	else
	{
		retValue = strncmp(src1, src2, cmpLen);
	}

	LOG("exit");

	return retValue;
}

int ann_fstruct_create(struct ANN_FILE_STRUCT* fStructPtr, const char* filePath)
{
	int retValue = ANN_NO_ERROR;
	int iResult;
	int fBlockIndex;

	char tmpRead;

	struct ANN_STR tmpStr;
	struct ANN_FILE_BLOCK tmpBlock;
	struct ANN_FILE_STRUCT tmpStruct;
	
	struct ANN_FILE_BLOCK* tmpBlockPtr = NULL;
	
	FILE* fileRead = NULL;

	LOG("enter");

	// Zero memory
	ann_str_zeromem(&tmpStr);
	ann_fstruct_zeromem(&tmpStruct);
	ann_fblock_zeromem(&tmpBlock);
	
	// Open file
	fileRead = fopen(filePath, "rb");
	if(fileRead == NULL)
	{
		retValue = ANN_FILE_FAILED;
		goto RET;
	}

	// Read file
	fBlockIndex = -1;
	while(!feof(fileRead))
	{
		tmpRead = ann_get_char(fileRead, READ_ALL);
		if(ann_is_sigchar(tmpRead))
		{
			switch(tmpRead)
			{
				case ']':
					if(tmpBlockPtr != NULL)
					{
						tmpBlockPtr->header = tmpStr.str;
					}
					else
					{
						retValue = ANN_SYNTAX_ERROR;
						goto ERR;
					}

					tmpStr.str = NULL;
					tmpStr.size = 1;
					break;

				case '[':
					iResult = ann_fstruct_append(&tmpStruct, &tmpBlock);
					if(iResult != ANN_NO_ERROR)
					{
						retValue = iResult;
						goto ERR;
					}

					fBlockIndex++;
					tmpBlockPtr = &tmpStruct.blockList[fBlockIndex];
					break;

				default:
					iResult = ann_str_append(&tmpStr, tmpRead);
					if(iResult != ANN_NO_ERROR)
					{
						retValue = iResult;
						goto ERR;
					}
			}
		}
		else
		{
			if(tmpStr.size > 1 && tmpBlockPtr != NULL)
			{
				iResult = ann_fblock_append(tmpBlockPtr, &tmpStr.str);
				if(iResult != ANN_NO_ERROR)
				{
					retValue = iResult;
					goto ERR;
				}

				tmpStr.size = 1;
			}
		}
	}

	// Assign value
	*fStructPtr = tmpStruct;
	
	goto RET;

ERR:
	ann_fstruct_delete(&tmpStruct);

RET:
	ann_fblock_delete(&tmpBlock);
	ann_str_delete(&tmpStr);

	if(fileRead != NULL)
		fclose(fileRead);
	
	LOG("exit");
	return retValue;
}

void ann_fstruct_print(struct ANN_FILE_STRUCT* fStructPtr)
{
	int i;

	LOG("enter");

	for(i = 0; i < fStructPtr->blockCount; i++)
	{
		ann_fblock_print(&fStructPtr->blockList[i]);
	}

	LOG("exit");
}

void ann_fblock_print(struct ANN_FILE_BLOCK* fBlockPtr)
{
	int i;

	LOG("enter");

	printf("[ %s ]\n", fBlockPtr->header);
	for(i = 0; i < fBlockPtr->strCount; i++)
	{
		printf("%s\n", fBlockPtr->strList[i]);
	}
	printf("\n");

	LOG("exit");
}

void ann_fblock_zeromem(struct ANN_FILE_BLOCK* fBlockPtr)
{
	LOG("enter");

	fBlockPtr->header = NULL;
	fBlockPtr->strCount = 0;
	fBlockPtr->strList = NULL;

	LOG("exit");
}

void ann_fblock_delete(struct ANN_FILE_BLOCK* fBlockPtr)
{
	int i;
	
	LOG("enter");

	if(fBlockPtr->strList != NULL)
	{
		for(i = 0; i < fBlockPtr->strCount; i++)
		{
			free(fBlockPtr->strList[i]);
		}
		free(fBlockPtr->strList);

		fBlockPtr->strList = NULL;
	}
	fBlockPtr->strCount = 0;

	if(fBlockPtr->header != NULL)
	{
		free(fBlockPtr->header);
		fBlockPtr->header = NULL;
	}

	LOG("exit");
}

int ann_fblock_append(struct ANN_FILE_BLOCK* dst, char** srcPtr)
{
	void* allocTmp = NULL;

	allocTmp = realloc(dst->strList, sizeof(char*) * (dst->strCount + 1));
	if(allocTmp == NULL)
	{
		LOG("exit");
		return ANN_MEM_FAILED;
	}
	else
	{
		dst->strList = allocTmp;
		dst->strCount++;

		dst->strList[dst->strCount - 1] = *srcPtr;
		*srcPtr = NULL;
	}

	return ANN_NO_ERROR;
}

void ann_fstruct_zeromem(struct ANN_FILE_STRUCT* fStructPtr)
{
	fStructPtr->blockCount = 0;
	fStructPtr->blockList = NULL;
}

int ann_fstruct_append(struct ANN_FILE_STRUCT* dst, struct ANN_FILE_BLOCK* src)
{
	void* allocTmp = NULL;

	LOG("enter");

	allocTmp = realloc(dst->blockList, sizeof(struct ANN_FILE_BLOCK) * (dst->blockCount + 1));
	if(allocTmp == NULL)
	{
		LOG("exit");
		return ANN_MEM_FAILED;
	}
	else
	{
		dst->blockList = allocTmp;
		dst->blockCount++;

		dst->blockList[dst->blockCount - 1].header = src->header;
		dst->blockList[dst->blockCount - 1].strCount = src->strCount;
		dst->blockList[dst->blockCount - 1].strList = src->strList;

		src->header = NULL;
		src->strCount = 0;
		src->strList = NULL;
	}
	
	LOG("exit");
	return ANN_NO_ERROR;
}

void ann_fstruct_delete(struct ANN_FILE_STRUCT* fStructPtr)
{
	int i;

	LOG("enter");

	if(fStructPtr->blockList != NULL)
	{
		for(i = 0; i < fStructPtr->blockCount; i++)
		{
			ann_fblock_delete(&(fStructPtr->blockList[i]));
		}
		free(fStructPtr->blockList);

		fStructPtr->blockList = NULL;
	}

	fStructPtr->blockCount = 0;

	LOG("exit");
}

int ann_is_sigchar(char ch)
{
	int retValue = 0;

	LOG("enter");

	if(ch >= ASCII_MIN_SIG && ch <= ASCII_MAX_SIG)
		retValue = 1;
	
	LOG("exit");

	return retValue;
}

char ann_get_char(FILE* fileRead, int readAction)
{
	int iResult;
	int readCount;
	char tmpRead;

	LOG("enter");

	// Read a character
	readCount = 1;
	iResult = fread(&tmpRead, sizeof(char), readCount, fileRead);
	if(iResult != readCount)
	{
		goto ERR;
	}

	if(readAction == READ_ALL)
	{
		goto RET;
	}

	// Determint if character is signaficant
	if(ann_is_sigchar(tmpRead))
		goto RET;

ERR:
	LOG("exit");
	return -1;

RET:
	LOG("exit");
	return tmpRead;
}

void ann_str_zeromem(struct ANN_STR* strPtr)
{
	LOG("enter");

	strPtr->size = 1;
	strPtr->str = NULL;

	LOG("exit");
}

int ann_str_append(struct ANN_STR* strPtr, char ch)
{
	void* allocTmp = NULL;

	LOG("enter");
	
	allocTmp = realloc(strPtr->str, sizeof(char) * (strPtr->size + 1));
	if(allocTmp == NULL)
	{
		LOG("exit");
		return ANN_MEM_FAILED;
	}
	else
	{
		strPtr->str = allocTmp;
		strPtr->size++;

		strPtr->str[strPtr->size - 1] = '\0';
		strPtr->str[strPtr->size - 2] = ch;
	}

	LOG("exit");

	return ANN_NO_ERROR;
}

void ann_str_delete(struct ANN_STR* strPtr)
{
	LOG("enter");

	if(strPtr->str != NULL)
	{
		free(strPtr->str);
		strPtr->str = NULL;
	}

	strPtr->size = 0;

	LOG("exit");
}

