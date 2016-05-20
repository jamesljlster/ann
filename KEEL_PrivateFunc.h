#ifndef KEEL_PRIVATEFUNC_H_INCLUDED
#define KEEL_PRIVATEFUNC_H_INCLUDED

#define KEEL_BUFFER_LEN 512

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern int KEEL_KWProc_Relation(KEEL_DATA keelData, char* fileBuffer, const char* keyword);
extern int KEEL_KWProc_Attribute(KEEL_DATA keelData, char* fileBuffer, const char* keyword);
extern int KEEL_KWProc_Inputs(KEEL_DATA keelData, char* fileBuffer, const char* keyword);
extern int KEEL_KWProc_Outputs(KEEL_DATA keelData, char* fileBuffer, const char* keyword);

extern int KEEL_FindChar(char* buffer, int startIndex, int targetChar, int lenLimit);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // KEEL_PRIVATEFUNC_H_INCLUDED
