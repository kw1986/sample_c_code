#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "linked_list.h"

typedef struct LinkedListItem LinkedListItem;

struct LinkedListItem {
	LinkedListItem  *previous;
	LinkedListItem  *next;
	void *data;
};

struct LinkedList {
	unsigned long len;
	LinkedListItem *head;
	LinkedListItem *tail;
};

LinkedList *linked_list_create() {
	LinkedList *ll = NULL;
	
	ll = (LinkedList*)malloc(sizeof(LinkedList));
	ll->len = 0;
	ll->head = NULL;
	ll->tail = NULL;

	return ll;
}

void linked_list_destroy_item(void *item, void (*destructor)(void*)) {
	LinkedListItem *lli = (LinkedListItem*)item;
	
	if (lli) {
		if (destructor) {
			destructor(lli->data);
		}
		
		free(lli);
	}
}

void linked_list_destroy_item(void *item) {
	linked_list_destroy_item(item, NULL);
}

void linked_list_destroy(LinkedList *ll, void (*destructor)(void*)) {
	LinkedListItem *lli = NULL;
	LinkedListItem *tmp = NULL;
	
	if (ll) {
		lli = ll->head;
		
		while (lli != NULL) {
			tmp = lli->next;
			linked_list_destroy_item((void*)lli, destructor);
			lli = tmp;
		}
		
		free(ll);
	}
}

void linked_list_destroy(LinkedList *ll) {
	if(ll) {
		linked_list_destroy(ll, NULL);
	}
}

static inline void modify_next_link(LinkedListItem *lli, LinkedListItem *next) {
	if (lli) {
		lli->next = next;
	}
}

static inline void modify_previous_link(LinkedListItem *lli, LinkedListItem *previous) {
	if (lli) {
		lli->previous = previous;
	}
}

static LinkedListItem *linked_list_item_create(LinkedListItem *previous, LinkedListItem *next, void *data) {
	LinkedListItem *lli = NULL;
	
	lli = (LinkedListItem*)malloc(sizeof(LinkedListItem));
	
	lli->previous = previous;
	modify_next_link(previous, lli);
	
	lli->next = next;
	modify_previous_link(next, lli);
	
	lli->data = data;
	
	return lli;
}

int linked_list_prepend(LinkedList* ll, void* data)
{
	LinkedListItem* lli = NULL;

	if (ll == NULL) {
		return -1;
	}

	lli = linked_list_item_create(NULL, ll->head, data);
	ll->head = lli;
	(ll->len)++;

	return 0;
}

int linked_list_append(LinkedList* ll, void* data)
{
	LinkedListItem* lli = NULL;
	
	if (ll == NULL) {
		return -1;
	}

	lli = linked_list_item_create(ll->tail, NULL, data);
	
	if (ll->head == NULL) {
		ll->head = lli;
	}
	ll->tail = lli;
	
	(ll->len)++;

	return 0;
}

void *linked_list_extract_first(LinkedList *ll) {
	LinkedListItem *lli = NULL;
	void *data = NULL;
	
	if (ll == NULL) {
		return NULL;
	}
	
	if (ll->head) {
		lli = ll->head;
		
		if (lli->next == NULL) {
			ll->head = NULL;
			ll->tail = NULL;
		}
		else {
			ll->head = lli->next;
			modify_previous_link(lli->next, NULL);
		}
		
		data = lli->data;
		
		linked_list_destroy_item((void*)lli);
		(ll->len)--;
	}
	
	return data;
}


void *linked_list_get(LinkedList *ll, unsigned long pos) {
	void *data = NULL;
	
	if (ll == NULL) {
		return NULL;
	}

	if (ll->head) {
		LinkedListItem *lli = NULL;
		unsigned int i = 0;
		
		lli = ll->head;
		while ((i < pos) && (lli->next != NULL)) {
			lli = lli->next;
			i++;
		}
		
		if (i == pos) {
			data = lli->data;
		}
	}

	return data;
}


unsigned long linked_list_len(LinkedList *ll) {
	unsigned long len = 0;
	
	if (ll == NULL) {
		return 0;
	}
	
	len = ll->len;

	return len;
}
