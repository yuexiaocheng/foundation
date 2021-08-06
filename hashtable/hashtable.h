#ifndef XD_HASH_TABLE_H
#define XD_HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

struct nlist {
	struct nlist *next;
	char *key;
	char *value;
};

struct HashTable {
	int tablesize;
	struct nlist ** table;
};

struct HashTable* InitTable(int tablesize);
struct nlist* Lookup(struct HashTable* tbl, const char* key);
struct nlist* Insert(struct HashTable* tbl, const char* key, const char* value); 
void Remove(struct HashTable* tbl, const char* key);
void PrintTable(struct HashTable* tbl);

#ifdef __cplusplus
}
#endif

#endif // XD_HASH_TABLE_H
