#ifndef ARRAY_H_
#define ARRAY_H_
#define REALLY_INCLUDE_ARRAYTYPE_H_
#include "arraytype.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct ArrayList ArrayList;
#ifndef _MSC_VER
typedef bool (*ArrayList_Compare_Function) (void *data_a, void *data_b);
typedef void (*ArrayList_Foreach_Function) (void *data);
#endif
struct Node;
struct ArrayInfo;
struct ArrayList {
 struct Node *head;
 struct ArrayInfo *info;
 int (*add)(ArrayList *plist, ...);
 int (*insert)(ArrayList *plist, uint32_t pos, ...);
 size_t (*search) (ArrayList *plist, void *data, void *func);
 int (*set)(ArrayList *plist, uint32_t pos, ...);
 int (*get)(ArrayList *plist, uint32_t pos, ...);
 void (*foreach) (ArrayList *plist, void *func);
 uint32_t (*length)(ArrayList *plist);
 uint8_t (*type)(ArrayList *plist);
 int (*remove)(ArrayList *plist, uint32_t pos);
 void (*destroy)(ArrayList **plist);
};
ArrayList *CreateArrayList(uint8_t type);
#ifndef __GNUC__
ArrayList *ArrayListCreate(uint8_t type);
#endif // __GNUC__
#ifdef __cplusplus
}
#endif
#endif /* ARRAY_H_ */
