#include "linkedList.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void list_create(struct list *self) {
  self -> first =  NULL;
}

void list_print(struct list *self){
  struct list_node *curr = self->first;
  while(curr != NULL){
    printf("%d,",curr->data);
    curr = curr->next;
  }
  printf("\n");
}

void list_create_from(struct list *self, const int *other, size_t size) {
  self->first = malloc(sizeof(struct list_node));
  struct list_node *curr = self-> first;
  curr->data = other[0];
  for(size_t i=1; i<size; ++i){
   struct list_node *new = malloc(sizeof(struct list_node));
   new->data = other[i];
   curr->next = new;
   curr = curr->next;
  }
  curr->next = NULL;
}

void node_destroy(struct list_node *curr){
  if(curr->next == NULL){
    free(curr);
    return;
  }
  node_destroy(curr->next);
}

void list_destroy(struct list *self) {
  if(list_empty(self) != true)node_destroy(self->first);
}

bool list_empty(const struct list *self) {
  return(self == NULL || self->first == NULL);
}

size_t list_size(const struct list *self) {
  struct list_node *curr = self->first;
  size_t size = 0;
  while (curr != NULL) {
    ++size;
    curr = curr->next;
  }
  return size;
}

bool list_equals(const struct list *self, const int *data, size_t size){
  if(list_empty(self) && size!=0) return false;
  if(list_size(self)!=size)return false;
  struct list_node *curr = self->first;
  for(size_t i=0; i<size; ++i){
    if(curr->data != data[i]) return false;
    curr = curr->next;
  }
  return true;
}

void list_push_front(struct list *self, int value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->data = value;
  new->next = self->first;
  self->first = new;
}

void list_pop_front(struct list *self) {
  if(list_size(self)>0){
    self->first = self->first->next;
  }
}

void list_push_back(struct list *self, int value) {
  struct list_node *new = malloc(sizeof(struct list_node));
  new->data = value;
  new->next = NULL;
  if(self->first == NULL){
    self->first = new;
  }
  else{
    struct list_node *curr = self->first;
    while(curr->next != NULL){
      curr = curr->next;
    }
    curr->next = new;
  }
}

void list_pop_back(struct list *self) {
  struct list_node *curr =self->first;
  if(curr->next == NULL){
    free(curr);
    self->first = NULL;
  }
  else{
    struct list_node *theNext =curr->next;
    while(theNext->next != NULL){
      theNext = theNext->next;
      curr = curr->next;
    }
    free(theNext);
    curr->next = NULL;
  }
}


void list_insert(struct list *self, int value, size_t index) {
  if(index == 0)list_push_front(self,value);
  else{
    struct list_node *curr = self->first;
    struct list_node *new = malloc(sizeof(struct list_node));
    new->data = value;
    for(size_t i=0; i<index-1;++i){
      curr = curr->next;
    }
    new->next = curr->next;
    curr->next = new;
  }
}


void list_remove(struct list *self, size_t index) {
  if(index == 0)list_pop_front(self);
  else{
    struct list_node *buffer = malloc(sizeof(struct list_node));
    struct list_node *curr = self->first;
    for(size_t i=0; i<index-1;++i){
      curr = curr->next;
    }
    buffer = curr->next;
    curr->next = buffer->next;
    free(buffer);
  }
}

int list_get(const struct list *self, size_t index) {
  if(index<list_size(self)){
    struct list_node *curr = self->first;
    for(size_t i=0; i<index; ++i){
      curr=curr->next;
    }
    return curr->data;
  }
  else return 0;
}

void list_set(struct list *self, size_t index, int value) {
  if(index<list_size(self)){
    struct list_node *curr = self->first;
    for(size_t i=0; i<index; ++i){
      curr=curr->next;
    }
    curr->data = value;
  }
}

size_t list_search(const struct list *self, int value) {
  struct list_node *curr = self->first;
  for(size_t i=0; i<list_size(self);++i){
    if(curr->data == value) return i;
    curr = curr->next;
  }
  return list_size(self);
}

bool list_is_sorted(const struct list *self) {
  if(list_empty(self))return true;
  struct list_node *curr = self->first;
  while(curr->next!=NULL){
    if(curr->data > curr->next->data) return false;
    curr =curr->next;
  }
  return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
  struct list_node *curr = self->first;
  for(size_t i=0; i<list_size(self);++i){
    if(i<list_size(self)/2)list_push_back(out1,curr->data);
    else list_push_back(out2,curr->data);
    curr=curr->next;
  }
  list_destroy(self);
  self->first = NULL;
}


void list_merge(struct list *self, struct list *in1, struct list *in2) {
  while(in1->first!=NULL && in2->first!=NULL){
    if(in1->first->data<in2->first->data){
      list_push_back(self,in1->first->data);
      list_pop_front(in1);
    }
    else{
      list_push_back(self,in2->first->data);
      list_pop_front(in2);
    }
  }
  if(in2->first!=NULL){
    while(in2->first!=NULL){
      list_push_back(self,in2->first->data);
      list_pop_front(in2);
    }
  }
  else if(in1->first!=NULL){
    while(in1->first!=NULL){
      list_push_back(self,in1->first->data);
      list_pop_front(in1);
    }
  }
}

void list_merge_sort(struct list *self) {
  if(list_size(self) == 1){
    return;
  }
  struct list *part1 = malloc(sizeof(struct list));
  struct list *part2 = malloc(sizeof(struct list));
  list_create(part1);
  list_create(part2);
  list_split(self, part1, part2);
  list_merge_sort(part1);
  list_merge_sort(part2);
  list_merge(self, part1, part2);
  free(part1);
  free(part2);
}
