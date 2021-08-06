#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct element {
	struct list_head entry;
	int number;
};

int main() {
	int i;
	struct element *pos, *elem;

	LIST_HEAD(head);

	for (i=0; i<100; i++) {
		elem = (struct element*)malloc(sizeof(struct element));
		elem->number = i;
		// list_add(&elem->entry, &head);
		list_add_tail(&elem->entry, &head);
	}
	printf("%s", "*");
	list_for_each_entry(pos, &head, entry)
		printf("->%d", pos->number);
	printf("\n");
	return 0;
}
