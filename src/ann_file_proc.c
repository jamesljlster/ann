#include <stdio.h>
#include <stdlib.h>

#include "ann.h"
#include "ann_file_proc.h"

#include "debug.h"

int ann_fstruct_create(struct ANN_FILE_STRUCT* fStructPtr, const char* filePath)
{
	int retValue = ANN_NO_ERROR;
	int iResult;

	struct ANN_STR tmpStr;
	struct ANN_FILE_BLOCK tmpBlock;
	struct ANN_FILE_STRUCT tmpStruct;
	
	FILE* fileRead = NULL;

	log("enter");

	// Open file
	fileRead = fopen(filePath, "rb");
	if(fileRead == NULL)
	{
		retValue = ANN_FILE_FAILED;
		goto RET;
	}

	// Zero memory
	ann_str_zeromem(&tmpStr);
	ann_fstruct_zeromem(&tmpStruct);
	ann_fblock_zeromem(&tmpBlock);

	
	goto RET;

ERR:
	ann_fstruct_delete(&tmpStruct);

RET:
	ann_fblock_delete(&tmpBlock);
	ann_str_delete(&tmpStr);

	if(fileRead != NULL)
		fclose(fileRead);
	
	log("exit");
	return retValue;
}

void ann_fblock_zeromem(struct ANN_FILE_BLOCK* fBlockPtr)
{
	log("enter");

	fBlockPtr->header = NULL;
	fBlockPtr->strCount = 0;
	fBlockPtr->strList = NULL;

	log("exit");
}

void ann_fblock_delete(struct ANN_FILE_BLOCK* fBlockPtr)
{
	int i;
	
	log("enter");

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

	log("exit");
}

int ann_fblock_append(struct ANN_FILE_BLOCK* dst, char** srcPtr)
{
	void* allocTmp = NULL;

	allocTmp = realloc(dst->strList, sizeof(char*) * (dst->strCount + 1));
	if(allocTmp == NULL)
	{
		log("exit");
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

	log("enter");

	allocTmp = realloc(dst->blockList, sizeof(struct ANN_FILE_BLOCK) * (dst->blockCount + 1));
	if(allocTmp == NULL)
	{
		log("exit");
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
	
	log("exit");
	return ANN_NO_ERROR;
}

void ann_fstruct_delete(struct ANN_FILE_STRUCT* fStructPtr)
{
	int i;

	log("enter");

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

	log("exit");
}

char ann_get_char(FILE* fileRead, int readAction)
{
	int iResult;
	int readCount;
	char tmpRead;

	log("enter");

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
	if(tmpRead >= ASCII_MIN_SIG && tmpRead <= ASCII_MAX_SIG)
		goto RET;

ERR:
	log("exit");
	return -1;

RET:
	log("exit");
	return tmpRead;
}

void ann_str_zeromem(struct ANN_STR* strPtr)
{
	log("enter");

	strPtr->size = 0;
	strPtr->str = NULL;

	log("exit");
}

int ann_str_append(struct ANN_STR* strPtr, char ch)
{
	void* allocTmp = NULL;

	log("enter");
	
	allocTmp = realloc(strPtr->str, sizeof(char) * (strPtr->size + 1));
	if(allocTmp == NULL)
	{
		log("exit");
		return ANN_MEM_FAILED;
	}
	else
	{
		strPtr->str = allocTmp;
		strPtr->size++;

		strPtr->str[strPtr->size - 1] = '\0';
		strPtr->str[strPtr->size - 2] = ch;
	}

	log("exit");
}

void ann_str_delete(struct ANN_STR* strPtr)
{
	log("enter");

	if(strPtr->str != NULL)
	{
		free(strPtr->str);
		strPtr->str = NULL;
	}

	strPtr->size = 0;

	log("exit");
}

