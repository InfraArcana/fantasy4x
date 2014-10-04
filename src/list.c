#include "list.h"

#include <assert.h>
#include <stdlib.h>

void l_init(struct l_node* head) {
  assert(head);

  head->data = NULL;
  head->next = NULL;
}

void l_free(struct l_node* head) {
  if(head) {
    if(head->data) {
      struct l_node* cur = head;

      while(cur) {
        assert(cur->data);
        struct l_node* next = cur->next;
        free(cur->data);
        free(cur);
        cur = next;
      }
    }
  }
}

//TODO This does not consider an empty list
void l_add(struct l_node* head, void* data) {
  assert(head);
  assert(data);

  struct l_node* new_node = malloc(sizeof(struct l_node));

  new_node->data  = data;
  new_node->next  = head->next;

  head->next = new_node;
}
