#ifndef LINKED_LIST_H //Note: Reserving the name "LIST_H"
#define LINKED_LIST_H

struct l_node {
  void*             data;
  struct l_node* next;
};

void l_init(struct l_node* head);

//Note: If the list is empty, nothing is done
void l_free(struct l_node* head);

void l_add(struct l_node* head, void* data);

#endif // LINKED_LIST_H
