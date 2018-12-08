#include <stdio.h>
#include <libarray/array.h>
#include <libarray/arraylog.h>

static inline void printf_list(ArrayList *list)
{
  for (uint32_t i = 0; i < list->length(list); i++) {
    int num;
    list->get(list, i,&num); // Get value from list by index
    LOGD("the number in %d:%d\n", i, num);
  }
}
int main(void) {
  ArrayList *list = CreateArrayList(ARRAY_TYPE_SIGNED_INT); // Create signed int container
  for (int i = 0; i < 10; i++) {
    list->add(list, i); // Add value to list by index
  }
  LOGD("length:%d\n", list->length(list)); // Print length
  printf_list(list); // Print the whole list
  list->destroy(list); // Destroy list
  return 0;
}
