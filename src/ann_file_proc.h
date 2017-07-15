#ifndef __ANN_FILE_PROC_H__
#define __ANN_FILE_PROC_H__

#include <stdio.h>

#define LF				0x0A
#define CR				0x0D
#define ASCII_MIN_SIG	0x20
#define ASCII_MAX_SIG	0x7E

enum READ_CHAR_TYPE
{
	READ_ALL,		// Read all type character
	READ_SIG		// Read signaficant character
};

struct ANN_FILE_BLOCK
{
	char* header;

	int strCount;
	char** strList;
};

struct ANN_FILE_STRUCT
{
	int blockCount;
	struct ANN_FILE_BLOCK* blockList;
};

struct ANN_STR
{
	int size;
	char* str;
};

#ifdef __cplusplus
extern "C" {
#endif

struct ANN_FILE_BLOCK* ann_find_fblock(struct ANN_FILE_STRUCT* fStructPtr, int headerID);

int ann_fstruct_create(struct ANN_FILE_STRUCT* fStructPtr, const char* filePath);

void ann_fstruct_zeromem(struct ANN_FILE_STRUCT* fStructPtr);
void ann_fstruct_delete(struct ANN_FILE_STRUCT* fStructPtr);
void ann_fstruct_print(struct ANN_FILE_STRUCT* fStructPtr);
int ann_fstruct_append(struct ANN_FILE_STRUCT* dst, struct ANN_FILE_BLOCK* src);

void ann_fblock_zeromem(struct ANN_FILE_BLOCK* fBlockPtr);
void ann_fblock_delete(struct ANN_FILE_BLOCK* fBlockPtr);
void ann_fblock_print(struct ANN_FILE_BLOCK* fBlockPtr);
int ann_fblock_append(struct ANN_FILE_BLOCK* dst, char** srcPtr);

int ann_get_char(FILE* fileRead, int readAction);
int ann_is_sigchar(char ch);

int ann_strcmp(char* src1, char* src2);
int ann_str_extract(char*** strListPtr, int* strCountPtr, char* src, char sepCh);
int ann_str_append(struct ANN_STR* strPtr, char ch);
void ann_str_delete(struct ANN_STR* strPtr);
void ann_str_zeromem(struct ANN_STR* strPtr);

#ifdef __cplusplus
}
#endif

#endif
