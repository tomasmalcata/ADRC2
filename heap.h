#include <stdio.h>
#include <stdlib.h>

typedef struct heap{
	struct node *vals; //MIN HEAP
	int *mp; //save the AS position in vals
	int last; //number 
} heap;

typedef struct node{
	int AS;
	int r;
	int size;
} node;

void init_heap();
int RemovePrior(int *AS, int *type, int *size);
void Insert(int AS, int r, int s);
void free_heap();
void PrintHeap();