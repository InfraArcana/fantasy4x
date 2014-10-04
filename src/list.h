#ifndef LINKED_LIST_H //Note: Reserving the name "LIST_H"
#define LINKED_LIST_H

struct l_node {
  void*          data;
  struct l_node* next;
};

//void l_init(struct l_node* head);

//Note: This will only free the list nodes, not the content.
void l_free(struct l_node* head);

//Note: If head points to a NULL pointer, a new head is allocated. Otherwise a new node
//is inserted after head.
void l_add(struct l_node** head, void* data);

#endif // LINKED_LIST_H
