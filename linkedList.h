#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct list_node {
  int data;
  struct list_node *next;
};

struct list {
  struct list_node *first;
};

/*
 * Create an empty list
 */
void list_create(struct list *self);

/*
 * Create a list with initial content
 */
void list_create_from(struct list *self, const int *other, size_t size);

/*
 * Destroy a list
 */
void list_destroy(struct list *self);

/*
 * Tell if the list is empty
 */
bool list_empty(const struct list *self);

/*
 * Get the size of the list
 */
size_t list_size(const struct list *self);

/*
 * Compare the list to an array (data and size)
 */
bool list_equals(const struct list *self, const int *data, size_t size);

/*
 * Add an element in the list at the beginning
 */
void list_push_front(struct list *self, int value);

/*
 * Remove the element at the beginning of the list
 */
void list_pop_front(struct list *self);

/*
 * Add an element in the list at the end
 */
void list_push_back(struct list *self, int value);

/*
 * Remove the element at the end of the list
 */
void list_pop_back(struct list *self);

/*
 * Insert an element in the list (preserving the order)
 * index is valid or equals to the size of the list (insert at the end)
 */
void list_insert(struct list *self, int value, size_t index);

/*
 * Remove an element in the list (preserving the order)
 * index is valid
 */
void list_remove(struct list *self, size_t index);

/*
 * Get the element at the specified index in the list or 0 if the index is not valid
 */
int list_get(const struct list *self, size_t index);

/*
 * Set an element at the specified index in the list to a new value, or do nothing if the index is not valid
 */
void list_set(struct list *self, size_t index, int value);

/*
 * Search for an element in the list and return its index or the size of the list if not present.
 */
size_t list_search(const struct list *self, int value);

/*
 * Tell if a list is sorted
 */
bool list_is_sorted(const struct list *self);

/*
 * Split a list in two. At the end, self should be empty.
 */
void list_split(struct list *self, struct list *out1, struct list *out2);

/*
 * Merge two sorted lists in an empty list. At the end, in1 and in2 should be empty.
 */
void list_merge(struct list *self, struct list *in1, struct list *in2);

/*
 * Sort a list with merge sort
 */
void list_merge_sort(struct list *self);

#ifdef __cplusplus
}
#endif

#endif // CONTAINERS_H