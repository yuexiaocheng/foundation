#include <stdio.h>
#include "hashtable.h"

int main() {
	int n, i;
	char keyx[64] = {0};
	printf("请输入散列表的大小:\n");
	scanf("%d", &n);
	struct nlist* node, *p;
	const char* key = "hello";
	const char* value = "world";
	struct HashTable* tbl =  InitTable(n);
	if (NULL == tbl) {
		printf("InitTable[%d] failed.\n", n);
		return 0;
	}

	for (i=0; i<n*10; i++) {
		sprintf(keyx, "%s%d", key, i);
		node = Insert(tbl, keyx, value);
		if (NULL == node)
			printf("Insert[%s]=%s failed.\n", key, value);
		else
			printf("Insert[%s]=%s ok.\n", node->key, node->value);
	}
	PrintTable(tbl);
	return 0;
}
