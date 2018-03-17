
#include <stdlib.h>
#include <libarray/array.h>

#define __LIBARRAY_PUBLIC __attribute__ ((visibility ("default")))
#ifdef LIBARRAY_STATIC
#define __LIBARRAY_PRIVATE static
#else
#define __LIBARRAY_PRIVATE __attribute__ ((visibility ("hidden")))
#endif

typedef struct Node Node;
typedef struct ArrayInfo ArrayInfo;

struct Node {
  void *data;
  Node *nextptr;
};

struct ArrayInfo {
  uint8_t type_id;
  uint32_t length;
};
// Internal fuctions declared here
__LIBARRAY_PRIVATE int ArrayListAdd(ArrayList *plist, ...);
__LIBARRAY_PRIVATE int ArrayListAddInternal(ArrayList *plist, va_list list);
__LIBARRAY_PRIVATE int ArrayListInsert(ArrayList *plist, uint32_t pos, ...);
__LIBARRAY_PRIVATE int ArrayListSet(ArrayList *plist, uint32_t pos, ...);
__LIBARRAY_PRIVATE int ArrayListGet(ArrayList *plist, uint32_t pos, ...);
__LIBARRAY_PRIVATE uint32_t ArrayListGetLength(ArrayList *plist);
__LIBARRAY_PRIVATE uint8_t ArrayListGetType(ArrayList *plist);
__LIBARRAY_PRIVATE int ArrayListRemove(ArrayList *plist, uint32_t pos);
__LIBARRAY_PRIVATE void ArrayListDestroy(ArrayList *plist);
static inline void ArrayListFunctionClear(ArrayList *plist);
static inline void ArrayListFree(Node *pnode, uint8_t type);

__LIBARRAY_PRIVATE int ArrayListDataStore(uint8_t type, Node *pnode ,va_list list)
{
	switch (type)
	{
        case ARRAY_TYPE_SIGNED_INT: {
          int data = va_arg(list, int);
          int *iptr = malloc(sizeof(int));
          *iptr = data;
          pnode->data = iptr;
          break;
        }
        case ARRAY_TYPE_UNSIGNED_INT: {
          unsigned int data = (unsigned int)va_arg(list, int);
          unsigned int *uiptr = malloc(sizeof(unsigned int));
          *uiptr = data;
          pnode->data = uiptr;
          break;
        }
        case ARRAY_TYPE_SIGNED_SHORT: {
          short data = (short)va_arg(list, int);
          short *sptr = malloc(sizeof(short));
          *sptr = data;
          pnode->data = sptr;
          break;
        }
        case ARRAY_TYPE_UNSIGNED_SHORT: {
          unsigned short data = (unsigned short)va_arg(list, int);
          unsigned short *usptr = malloc(sizeof(unsigned short));
          *usptr = data;
          pnode->data = usptr;
          break;
        }
        case ARRAY_TYPE_SIGNED_LONG: {
          long data = va_arg(list, long);
          long *lptr = malloc(sizeof(long));
          *lptr = data;
          pnode->data = lptr;
          break;
        }
        case ARRAY_TYPE_UNSIGNED_LONG: {
          unsigned long data = (unsigned long)va_arg(list, long);
          unsigned long *ulptr = malloc(sizeof(unsigned long));
          *ulptr = data;
          pnode->data = ulptr;
          break;
        }
        case ARRAY_TYPE_SIGNED_LONG_LONG: {
          long long data = va_arg(list, long long);
          long long *llptr = malloc(sizeof(long long));
          *llptr = data;
          pnode->data = llptr;
          break;
        }
        case ARRAY_TYPE_UNSIGNED_LONG_LONG: {
          unsigned long long data = (unsigned long long)va_arg(list, long long);
          unsigned long long *ullptr = malloc(sizeof(long long));
          *ullptr = data;
          pnode->data = ullptr;
          break;
        }
        case ARRAY_TYPE_SIGNED_CHAR: {
          signed char data = (signed char)va_arg(list, int);
          signed char *scptr = malloc(sizeof(signed char));
          *scptr = data;
          pnode->data = scptr;
          break;
        }
        case ARRAY_TYPE_UNSIGNED_CHAR: {
          unsigned char data = (unsigned char)va_arg(list, int);
          unsigned char *ucptr = malloc(sizeof(unsigned char));
          *ucptr = data;
          pnode->data = ucptr;
          break;
        }
        case ARRAY_TYPE_CHAR: {
          char data = (char)va_arg(list, int);
          char *cptr = malloc(sizeof(char));
          *cptr = data;
          pnode->data = cptr;
          break;
        }
        case ARRAY_TYPE_DOUBLE: {
          double data = va_arg(list, double);
          double *dptr = malloc(sizeof(double));
          *dptr = data;
          pnode->data = dptr;
          break;
        }
        case ARRAY_TYPE_FLOAT: {
          float data = (float)va_arg(list, double);
          float *fptr = malloc(sizeof(float));
          *fptr = data;
          pnode->data = fptr;
          break;
        }
        case ARRAY_TYPE_POINTER: {
          void *data = va_arg(list, void *);
          pnode->data = data;
          break;
        }
        default:
          return -1;
        }
        return 0;
}

__LIBARRAY_PRIVATE int ArrayListCheck(ArrayList *plist)
{
  if (plist == NULL) {
    return -1;
  }
  ArrayInfo *pinfo = plist->info;
  if (pinfo == NULL) {
    return -1;
  }
  uint8_t type = pinfo->type_id;
  if (type < ARRAY_TYPE_SIGNED_INT || type > ARRAY_TYPE_POINTER) {
    return -1;
  }
  if (plist->add == NULL || plist->get == NULL || plist->length==NULL || plist->type==NULL) {
    return -1;
  }
  if (plist->destroy == NULL||plist->insert==NULL||plist->remove==NULL||plist->set==NULL) {
    return -1;
  }
  return 0;
}

__LIBARRAY_PUBLIC ArrayList *CreateArrayList(uint8_t type)
{
  if (type <= 0x00 || type > 0x0e) {
    return NULL;
  }
  ArrayList *plist = malloc(sizeof(ArrayList));
  if (plist == NULL) {
    return NULL;
  }
  ArrayInfo *pinfo = malloc(sizeof(ArrayInfo));
  if (pinfo == NULL) {
    free(plist);
    return NULL;
  }
  pinfo->type_id = type;
  pinfo->length = 0;
  plist->head = NULL;
  plist->info = pinfo;
  plist->add = ArrayListAdd;
  plist->insert = ArrayListInsert;
  plist->set = ArrayListSet;
  plist->get = ArrayListGet;
  plist->length = ArrayListGetLength;
  plist->type = ArrayListGetType;
  plist->remove = ArrayListRemove;
  plist->destroy = ArrayListDestroy;
  return plist;
}
__LIBARRAY_PRIVATE int ArrayListAddInternal(ArrayList *plist,va_list list)
{
  int r=ArrayListCheck(plist);
  if (r < 0) {
    return -1;
  }
  Node *ptr = plist->head;
  ArrayInfo *pinfo = plist->info;
  uint32_t len = pinfo->length;
  uint8_t type = pinfo->type_id;
  while (len > 1) {
    ptr = ptr->nextptr;
    --len;
  }
  Node *pnode = malloc(sizeof(Node));
  if (pnode == NULL) {
    return -2;
  }
  r = ArrayListDataStore(type, pnode, list);
  va_end(list);
  if (r != 0) {
    free(pnode);
    return -4;
  }
  pnode->nextptr = NULL;
  if (len == 0) {
    plist->head = pnode;
  } else {
    ptr->nextptr = pnode;
  }
  pinfo->length += 1;
  return 0;
}

__LIBARRAY_PRIVATE int ArrayListGet(ArrayList *plist,uint32_t pos,...)
{
  int r = ArrayListCheck(plist);
  if (r < 0) {
    return -1;
  }
  uint32_t len = plist->info->length;
  uint8_t type = plist->info->type_id;
  if (pos >= len) {
    return -1;
  }
  Node *ptr = plist->head;
  while (pos > 0) {
    ptr = ptr->nextptr;
    --pos;
  }
  va_list list;
  va_start(list, pos);
  switch (type)
	{
        case ARRAY_TYPE_SIGNED_INT: {
          int *iptr = va_arg(list, int *);
          if (iptr == NULL) {
            va_end(list);
            return -1;
          }
          *iptr = *((int *)ptr->data);
          break;
        }
        case ARRAY_TYPE_UNSIGNED_INT: {
          unsigned int *uiptr = va_arg(list, unsigned int *);
          if (uiptr == NULL) {
            va_end(list);
            return -1;
          }
          *uiptr = *((unsigned int *)ptr->data);
          break;
        }
        case ARRAY_TYPE_SIGNED_SHORT: {
          short *sptr = va_arg(list, short *);
          if (sptr == NULL) {
            va_end(list);
            return -1;
          }
          *sptr = *((short *)ptr->data);
          break;
        }
        case ARRAY_TYPE_UNSIGNED_SHORT: {
          unsigned short *usptr = va_arg(list, unsigned short *);
          if (usptr == NULL) {
            va_end(list);
            return -1;
          }
          *usptr = *((unsigned short *)ptr->data);
          break;
        }
        case ARRAY_TYPE_SIGNED_LONG: {
          long *lptr = va_arg(list, long *);
          if (lptr == NULL) {
            va_end(list);
            return -1;
          }
          *lptr = *((long *)ptr->data);
          break;
        }
        case ARRAY_TYPE_UNSIGNED_LONG: {
          unsigned long *ulptr = va_arg(list, unsigned long *);
          if (ulptr == NULL) {
            va_end(list);
            return -1;
          }
          *ulptr = *((unsigned long *)ptr->data);
          break;
        }
        case ARRAY_TYPE_SIGNED_LONG_LONG: {
          long long *llptr = va_arg(list, long long *);
          if (llptr == NULL) {
            va_end(list);
            return -1;
          }
          *llptr = *((long long *)ptr->data);
          break;
        }
        case ARRAY_TYPE_UNSIGNED_LONG_LONG: {
          unsigned long long *ullptr = va_arg(list, unsigned long long *);
          if (ullptr == NULL) {
            va_end(list);
            return -1;
          }
          *ullptr = *((unsigned long long *)ptr->data);
          break;
        }
        case ARRAY_TYPE_SIGNED_CHAR: {
          signed char *scptr = va_arg(list, signed char *);
          if (scptr == NULL) {
            va_end(list);
            return -1;
          }
          *scptr = *((signed char *)ptr->data);
          break;
        }
        case ARRAY_TYPE_UNSIGNED_CHAR: {
          unsigned char *ucptr = va_arg(list, unsigned char *);
          if (ucptr == NULL) {
            va_end(list);
            return -1;
          }
          *ucptr = *((unsigned char *)ptr->data);
          break;
        }
        case ARRAY_TYPE_CHAR: {
          char *cptr = va_arg(list, char *);
          if (cptr == NULL) {
            va_end(list);
            return -1;
          }
          *cptr = *((char *)ptr->data);
          break;
        }
        case ARRAY_TYPE_DOUBLE: {
          double *dptr = va_arg(list, double *);
          if (dptr == NULL) {
            va_end(list);
            return -1;
          }
          *dptr = *((double *)ptr->data);
          break;
        }
        case ARRAY_TYPE_FLOAT: {
          float *fptr = va_arg(list, float *);
          if (fptr == NULL) {
            va_end(list);
            return -1;
          }
          *fptr = *((float *)ptr->data);
          break;
        }
        case ARRAY_TYPE_POINTER: {
          void **vptr = va_arg(list, void **);
          if (vptr == NULL) {
            va_end(list);
            return -1;
          }
          *vptr = ptr->data;
          break;
        }
        default: {
          va_end(list);
          return -1;
        }
        }
        va_end(list);
        return 0;
}

__LIBARRAY_PRIVATE uint32_t ArrayListGetLength(ArrayList *plist)
{
  if (ArrayListCheck(plist) < 0) {
    return 0;
  }
  return plist->info->length;
}

__LIBARRAY_PRIVATE uint8_t ArrayListGetType(ArrayList *plist)
{
  if (ArrayListCheck(plist) < 0) {
    return 0;
  }
  return plist->info->type_id;
}

__LIBARRAY_PRIVATE void ArrayListDestroy(ArrayList *plist)
{
  if (ArrayListCheck(plist) < 0) {
    return;
  }
  uint8_t type = ArrayListGetType(plist);
  if (type == 0) {
    return;
  }
  if (type==ARRAY_TYPE_POINTER)
  {
    Node *ptr = plist->head;
    Node *nptr = NULL;
    while (ptr!=NULL) {
      nptr = ptr;
      nptr->data = NULL;
      ptr = ptr->nextptr;
      free(nptr);
    }
    free(plist->info);
    plist->info = NULL;
    ArrayListFunctionClear(plist);
    free(plist);
  }
  else
  {
    Node *ptr = plist->head;
    void *dataptr = NULL;
    Node *nptr = NULL;
    while (ptr != NULL) {
      nptr = ptr;
      dataptr = nptr->data;
      free(dataptr);
      nptr->data = NULL;
      ptr = ptr->nextptr;
      free(nptr);
    }
    ArrayListFunctionClear(plist);
    free(plist);
  }
}

static inline void ArrayListFunctionClear(ArrayList *plist) {
  plist->add = NULL;
  plist->insert = NULL;
  plist->set = NULL;
  plist->get = NULL;
  plist->length = NULL;
  plist->type = NULL;
  plist->remove = NULL;
  plist->destroy = NULL;
}

__LIBARRAY_PRIVATE int ArrayListAdd(ArrayList *plist, ...) {
  va_list list;
  va_start(list, plist);
  return ArrayListAddInternal(plist, list);
}

__LIBARRAY_PRIVATE int ArrayListInsert(ArrayList *plist, uint32_t pos, ...)
{
  if (ArrayListCheck(plist) < 0) {
    return -1;
  }
  uint32_t len = ArrayListGetLength(plist);
  if (len == pos) {
    va_list list;
    va_start(list, pos);
    return ArrayListAddInternal(plist, list);
  }
  if (pos==0)
  {
    Node *pnode = malloc(sizeof(Node));
    va_list list;
    va_start(list, pos);
    if (ArrayListDataStore(ArrayListGetType(plist), pnode, list) < 0) {
      free(pnode);
      return -1;
    }
    va_end(list);
    pnode->nextptr = plist->head;
    plist->head = pnode;
    plist->info->length += 1;
    return 0;
  }
  else
  {
    if (pos > len) {
      return -1;
    }
    Node *pnode = malloc(sizeof(Node));
    va_list list;
    va_start(list, pos);
    if (ArrayListDataStore(ArrayListGetType(plist), pnode, list) < 0) {
      free(pnode);
      return -1;
    }
    va_end(list);
    Node *ptr = plist->head;
    for (int i = 1; i < pos; i++) {
      ptr = ptr->nextptr;
    }
    pnode->nextptr = ptr->nextptr;
    ptr->nextptr = pnode;
    plist->info->length += 1;
    return 0;
  }
}

static inline void ArrayListFree(Node *pnode,uint8_t type)
{
  if (type == ARRAY_TYPE_POINTER) {
    pnode->data = NULL;
    free(pnode);
  } else {
    free(pnode->data);
    pnode->data = NULL;
    free(pnode);
  }
}

__LIBARRAY_PRIVATE int ArrayListRemove(ArrayList *plist,uint32_t pos)
{
  if (ArrayListCheck(plist) < 0) {
    return -1;
  }
  uint32_t len = ArrayListGetLength(plist);
  if (len == 0) {
    return -1;
  }
  if (pos >= len) {
    return -1;
  }
  if (pos == 0) {
    Node *ptr = plist->head;
    plist->head = ptr->nextptr;
    ArrayListFree(ptr, ArrayListGetType(plist));
    plist->info->length -= 1;
    return 0;
  }
  if (pos == len - 1) {
    Node *ptr = plist->head;
    for (int i = 1; i < pos; i++) {
      ptr = ptr->nextptr;
    }
    ArrayListFree(ptr->nextptr, ArrayListGetType(plist));
    ptr->nextptr = NULL;
    plist->info->length -= 1;
    return 0;
  }
  else
  {
        Node *ptr = plist->head;
        for (int i = 1; i < pos; i++) {
          ptr = ptr->nextptr;
        }
        Node *nptr = ptr->nextptr;
        ptr->nextptr = nptr->nextptr;
        ArrayListFree(nptr, ArrayListGetType(plist));
        plist->info->length -= 1;
        return 0;
  }
}

__LIBARRAY_PRIVATE int ArrayListSet(ArrayList *plist,uint32_t pos,...)
{
  if (ArrayListCheck(plist) < 0) {
    return -1;
  }
  uint32_t len = ArrayListGetLength(plist);
  uint8_t type = ArrayListGetType(plist);
  if (pos >= len) {
    return -1;
  }
  Node *ptr=plist->head;
  for (int i = 0; i < pos; i++) {
    ptr = ptr->nextptr;
  }
  if (type!=ARRAY_TYPE_POINTER)
  {
  free(ptr->data);
  }
  ptr->data = NULL;
  va_list list;
  va_start(list, pos);
  if (ArrayListDataStore(ArrayListGetType(plist), ptr, list) < 0) {
    return -1;
  }
  va_end(list);
  return 0;
}
