#ifndef LINKED_LIST_H //Note: Reserving the name "LIST_H"
#define LINKED_LIST_H

struct l_node {
  void*          data;
  struct l_node* next;
};

//Note: If "head" points to a NULL pointer, the new node will become head. Otherwise a
//new node is inserted after the current head.
void l_add(struct l_node** head, void* data);

//Note: This will only free the list nodes, not the content. "head" may be NULL.
void l_free(struct l_node* head);

#endif // LINKED_LIST_H
