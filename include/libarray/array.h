#ifndef ARRAY_H_
#define ARRAY_H_
#define REALLY_INCLUDE_ARRAYTYPE_H_
#include "arraytype.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct ArrayList ArrayList;
struct Node;
struct ArrayInfo;
struct ArrayList {
 struct Node *head;
 struct ArrayInfo *info;
 int (*add)(ArrayList *plist, ...);
 int (*insert)(ArrayList *plist, uint32_t pos, ...);
 int (*set)(ArrayList *plist, uint32_t pos, ...);
 int (*get)(ArrayList *plist, uint32_t pos, ...);
 uint32_t (*length)(ArrayList *plist);
 uint8_t (*type)(ArrayList *plist);
 int (*remove)(ArrayList *plist, uint32_t pos);
 void (*destroy)(ArrayList **plist);
};
ArrayList *CreateArrayList(uint8_t type);
#ifndef _WIN32
ArrayList *ArrayListCreate(uint8_t type);
#endif // _WIN32
#ifdef __cplusplus
}
#endif
#endif /* ARRAY_H_ */
