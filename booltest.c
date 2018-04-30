#include <stdio.h>
#include <stdbool.h>
#include <libarray/array.h>

static inline void printf_bool(ArrayList *list) {
	if (!list) return;
	uint32_t len = list->length(list);
	for (uint32_t i = 0;i< len;i++) {
		bool b;
		list->get(list, i, &b);
		printf(b ? "true\n" : "false\n");
	}
}

int main(void) {
	ArrayList *list = ArrayListCreate(ARRAY_TYPE_BOOL);
	if (!list) {
		printf("Create ArrayList failed!\n");
		return -1;
	}
	for (int i = 0;i < 10;i++) {
		list->add(list, true);
	}
	printf_bool(list);
	return 0;
}
