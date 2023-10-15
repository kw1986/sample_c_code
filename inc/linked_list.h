#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList *linked_list_create();
void linked_list_destroy(LinkedList *ll);
void linked_list_destroy(LinkedList *ll, void (*destructor)(void*));

int linked_list_append(LinkedList *ll, void *data);

void *linked_list_extract_first(LinkedList *ll);

void *linked_list_get(LinkedList *ll, unsigned long pos);

unsigned long linked_list_len(LinkedList *ll);


#endif /* _LINKED_LIST_H */