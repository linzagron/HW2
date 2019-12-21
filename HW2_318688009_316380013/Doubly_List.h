#pragma once
#include "Monomial.h"

typedef Monomial polynom_element;
typedef polynom_element list_type;

typedef struct node
{
	list_type* value;
	struct node* next;
	struct node* prev;

	node()
	{
		value = NULL;
		next = NULL;
		prev = NULL;
	}

	~node()
	{
		delete value;
	}
}node;

typedef struct list
{
	node* head;
	node* tail;
}list;

void initList(list* lst);

int isEmpty(list* lst);

int length(list* lst);

node* allocItem(list_type value);

node* getLinkByIndex(list* lst, int idx);

int insertFirst(list* lst, node* item);

int insertLast(list* lst, node* item);

int deleteFirst(list* lst);

int deleteLast(list* lst);

int deleteLink(list* lst, node* link);

int insertAfter(list* lst, node* item, node* link);

int insertBefore(list* lst, node* item, node* link);