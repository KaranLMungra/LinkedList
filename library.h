#ifndef LINKEDLIST_LIBRARY_H
#define LINKEDLIST_LIBRARY_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Node {
    uint32_t key;
    uintptr_t xpn; // xor of previous node pointer and next node pointer
} Node;

struct LinkedList {
    Node* head;
    Node* tail;
    uint32_t length;

    // API
    bool (*is_empty)(const struct LinkedList* list);
    uint32_t (*size)(const struct LinkedList* list);
    void (*push_front)(struct LinkedList* list, uint32_t key);
    Node* (*pop_front)(struct LinkedList* list);
    void (*push_back)(struct LinkedList* list, uint32_t key);
    Node* (*pop_back)(struct LinkedList* list);
    Node* (*find)(const struct LinkedList* list, uint32_t key);
    void (*insert_after)(struct LinkedList* list, uint32_t key1, uint32_t key2);
    void (*insert_before) (struct LinkedList* list, uint32_t key1, uint32_t key2);
    Node* (*remove)(struct LinkedList* list, uint32_t key);
    void (*reverse)(struct LinkedList* list);
    void (*append)(struct LinkedList* list, struct LinkedList* list1);
};

extern const struct LinkedListClass {
    struct LinkedList* (*new) ();
    void (*del)(struct LinkedList*);
} LinkedList;

#endif //LINKEDLIST_LIBRARY_H
