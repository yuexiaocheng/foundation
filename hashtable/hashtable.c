#include "hashtable.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

/* generate a prime number near by n */
int next_prime(int n) {
	int i;
	if (2 == n) return n;
	while (true) {
		i = 1;
		do {
			i++;
		} while (n % i != 0 && i <= sqrt(n));
		if (n % i == 0) {
			// printf("%d is not a prime number\n", n);
			n++;
		}
		else {
			printf("%d is a prime number\n", n);
			break;
		}
	}
	return n;
}

/* the hash function */
unsigned int hash(const char* key, int tablesize) {
	unsigned int hashval = 0;
	assert(key != NULL);
	while ('\0' != *key) 
		hashval = (hashval << 5) + *key++;
	return hashval % tablesize;
}

/* Init a hash table */
struct HashTable* InitTable(int tablesize) {
	int primeTableSize = next_prime(tablesize);
	struct nlist** p = (struct nlist**)malloc(sizeof(struct nlist*) * primeTableSize);
	if (NULL == p) return NULL;
	struct HashTable* tbl = (struct HashTable*)malloc(sizeof(struct HashTable));
	if (NULL == tbl) return NULL;
	tbl->tablesize = primeTableSize;
	tbl->table = p;
	return tbl;
}

/* lookup a key in hash table */
struct nlist* Lookup(struct HashTable* tbl, const char* key) {
	struct nlist* np;
	for (np = tbl->table[hash(key, tbl->tablesize)]; np != NULL; np = np->next)
		if (strcmp(np->key, key) == 0)
			return np;
	return NULL;
}

/* Insert a key to the map */
struct nlist* Insert(struct HashTable* tbl, const char* key, const char* value) {
	struct nlist* np;
	unsigned int hashval;
	if (NULL == (np = Lookup(tbl, key))) { /* not found */
		np = (struct nlist*)malloc(sizeof(*np));
		if (NULL == np || NULL == (np->key = strdup(key)))
			return NULL;
		hashval = hash(key, tbl->tablesize);
		np->next = tbl->table[hashval];
		tbl->table[hashval] = np;
	} 
	else /* already there */
		free((void*)np->value);
	if (NULL == (np->value = strdup(value)))
		return NULL;
	return np;
}

/* Delete a key from the map */
void Remove(struct HashTable* tbl, const char* key) {
	struct nlist* np, *prev;
	unsigned int hashval;

	hashval = hash(key, tbl->tablesize);
	prev = tbl->table[hashval];
	for (np = prev; np != NULL; prev = np, np = np->next)
		if (strcmp(np->key, key) == 0) {
			if (prev == np) tbl->table[hashval] = np->next; /* head */
			else prev->next = np->next;
			printf("the key[%s] value[%s] is deleted\n", key, np->value);
			free(np->key);
			free(np->value);
			free(np);
			break;
		}
	return;
}

/* Show the map */
void PrintTable(struct HashTable* tbl) {
	int i;
	struct nlist* j;
	printf("table size: %d\n", tbl->tablesize);
	for (i=0; i<tbl->tablesize; i++) {
		printf("[%d] ", i);
		for (j=tbl->table[i]; j != NULL; j = j->next)
			printf("->%s:%s", j->key, j->value);
		printf("\n");
	}
	return;
}
