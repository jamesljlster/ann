#ifndef KEEL_DATAPROC_H_INCLUDED
#define KEEL_DATAPROC_H_INCLUDED

struct _KEEL_DATA
{
    char* name;

    int attrAmount;
    struct KEEL_ATTRIBUTE* attrList;

    int inputs;
    int outputs;

    int* inputAttrIndexList;
    int outputAttrIndex;

    double* data;

    int dataRows;
    int dataCols;
};

typedef struct _KEEL_DATA* KEEL_DATA;

struct KEEL_ATTRIBUTE
{
    int stringMember;

    char* attrName;
    char* attrType;

    int memberCount;
    char** member;
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern KEEL_DATA KEEL_ReadDataset(const char* dataPath);
extern int KEEL_Delete(KEEL_DATA keelData);

extern int KEEL_Normalize(KEEL_DATA keelData, int targetColumn, double targetMin, double targetMax);

extern int KEEL_GetDataAmount(KEEL_DATA keelData);
extern int KEEL_GetInputs(KEEL_DATA keelData);
extern int KEEL_GetOutputs(KEEL_DATA keelData);

extern double* KEEL_GetInputList(KEEL_DATA keelData, int dataIndex);
extern double* KEEL_GetOutputList(KEEL_DATA keelData, int dataIndex);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KEEL_DATAPROC_H_INCLUDED
