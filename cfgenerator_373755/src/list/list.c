#include <assert.h>
#include "list.h"

struct node{
	list_type content;
	node* next;
	struct node* previous;
};

struct list_struct {
	node* head;
	node* tail;
	int length;
};

list* new_list(void)
{
	list* newlist = (list*) malloc(sizeof(list));
	newlist->head = NULL;
	newlist->tail = NULL;
	newlist->length = 0;
	return newlist;
}

node* new_node(list_type content)
{
	node* newnode = (node*) malloc(sizeof(node));
	newnode->content = content;
	newnode->next = NULL;
	newnode->previous = NULL;
	return newnode;
}

list_type content(node* n)
{
	assert(n!=NULL);
	return n->content;
}

node* head(const list* l)
{
	assert(l != NULL);
	return l->head;
}

node* tail(const list* l)
{
	assert(l != NULL);
	return l->tail;
}

int length(const list* l)
{
	assert(l != NULL);
	return l->length;
}

node* next(const list* l, node* n)
{
	assert(l != NULL);
	assert(n != NULL);
	return n->next;
}

node* prev(const list* l, node* n)
{
	assert(l != NULL);
	assert(n != NULL);
	return n->previous;
}

void add_node(list* l, node* node_before, node* node_to_add)
{
	assert(l != NULL);
	assert(node_to_add != NULL);

	/* se node_after e' NULL, allora per convenzione l'inserimento e' in testa*/
	node* node_after = node_before != NULL ? node_before->next : l->head;

	node_to_add->next = node_after;
	node_to_add->previous = node_before;

	if (node_before != NULL) {
		/* node_to_add non inizale*/
		node_before->next = node_to_add;
	} else {
		/* node_to_add iniziale*/
		l->head = node_to_add;
	}

	if (node_after != NULL) {
		/* node_to_add non finale */
		node_after->previous = node_to_add;
	} else {
		/* node_to_add finale */
		l->tail = node_to_add;
	}

	++l->length;
}

void remove_node(list* l, node* node_to_remove)
{
	assert(l != NULL);
	assert(node_to_remove != NULL);

	node* node_before = node_to_remove->previous;
	node* node_after = node_to_remove->next;

	if (node_before != NULL){
		/* il nodo da eliminare non e' in testa */
		node_before->next = node_after;
	} else {
		/* il nodo da eliminare e' in testa */
		l->head = node_after;
	}

	if (node_after != NULL){
		/* il nodo da eliminare non e' in coda */
		node_after->previous = node_before;
	} else {
		/* il nodo da eliminare e' in cosa */
		l->tail = node_before;
	}

	node_to_remove->next = NULL;
	node_to_remove->previous = NULL;

	--l->length;
}

void delete_list(list* l)
{
	assert(l!=NULL);

	node* n = head(l);
	while (n!=NULL){
		node* next_node = next(l,n);
		remove_node(l,n);
		delete_node(n);
		n = next_node;
	}
	free(l);
}

void delete_node(node* n){
	assert(n!=NULL);
	free(n);
}

node* lookfor(const list* l, list_type cont)
{
	assert(l!=NULL);

	node* found_node = NULL; /* il nodo che contiene l'elemento*/
	node* examined_node = head(l);
	while(examined_node != NULL && found_node == NULL){
		found_node = (content(examined_node) == cont) ? examined_node : NULL;
		examined_node = next(l, examined_node);
	}

	return found_node;
}
