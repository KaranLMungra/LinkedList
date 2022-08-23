#include "library.h"

#include <stdlib.h>
#include <assert.h>

#define NIL (uintptr_t) NULL

#define VERIFY_NULL_CHECK(ptr) assert(ptr != NULL);

// API

uint32_t size(const struct LinkedList* list) {
    VERIFY_NULL_CHECK(list);
    return list->length;
}
bool is_empty(const struct LinkedList* list) {
    VERIFY_NULL_CHECK(list);
    return list->size(list) == 0;
}
void push_front(struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list);
    Node* node = (Node* ) malloc(sizeof(Node*));
    node->key = key;
    node->xpn = 0;
    if(list->is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {
        node->xpn = NIL ^ (uintptr_t) list->head;
        uintptr_t next = NIL ^ list->head->xpn;
        list->head->xpn = (uintptr_t) node ^ next;
        list->head = node;
    }
    list->length++;
}
Node* pop_front(struct LinkedList* list) {
    VERIFY_NULL_CHECK(list);
    if(list->is_empty(list)) {
        return NULL;
    }
    Node* node = list->head;
    if(list->size(list) == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node* next = (Node*)(list->head->xpn ^ NIL);
        Node* next1 = (Node*)(next->xpn ^ (uintptr_t) node);
        next->xpn = (uintptr_t) next1 ^ NIL;
        list->head = next;
    }
    node->xpn = 0;
    list->length--;
    return node;
}
void push_back(struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list);
    Node* node = (Node* ) malloc(sizeof(Node*));
    node->key = key;
    node->xpn = 0;
    if(list->is_empty(list)) {
        list->head = node;
        list->tail = node;
    } else {
        node->xpn = (uintptr_t) list->tail ^ NIL;
        uintptr_t prev = list->tail->xpn ^ NIL;
        list->tail->xpn = prev ^ (uintptr_t) node;
        list->tail = node;
    }
    list->length++;
}
Node* pop_back(struct LinkedList* list) {
    VERIFY_NULL_CHECK(list);
    if(list->is_empty(list)) {
        return NULL;
    }
    Node* node = list->tail;
    if(list->size(list) == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node* prev = (Node*)(list->tail->xpn ^ NIL);
        Node* prev1 = (Node*)(prev->xpn ^ (uintptr_t) node);
        prev->xpn = (uintptr_t) prev1 ^ NIL;
        list->tail = prev;
    }
    node->xpn = 0;
    list->length--;
    return node;
}
Node* find(const struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return NULL;
    }
    Node* iter = list->head;
    uintptr_t prev = NIL;
    while(iter != NULL) {
        Node* next = (Node*)(prev ^ iter->xpn);
        if(iter->key == key) {
            return iter;
        }
        prev = (uintptr_t)iter;
        iter = next;
    }
    return NULL;
}
Node* find_prev(const struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return NULL;
    }
    Node* iter = list->head;
    uintptr_t prev = NIL;
    while(iter != NULL) {
        Node* next = (Node*)(prev ^ iter->xpn);
        if(iter->key == key) {
            return (Node*) prev;
        }
        prev = (uintptr_t)iter;
        iter = next;
    }
    return NULL;
}
Node* find_next(const struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return NULL;
    }
    Node* iter = list->head;
    uintptr_t prev = NIL;
    while(iter != NULL) {
        Node* next = (Node*)(prev ^ iter->xpn);
        if(iter->key == key) {
            return (Node*) (prev ^ iter->xpn);
        }
        prev = (uintptr_t)iter;
        iter = next;
    }
    return NULL;
}
void insert_after(struct LinkedList* list, uint32_t key1, uint32_t key2) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return;
    }
    if(list->tail->key == key1) {
        push_back(list, key2);
    } else {
        Node* iter = list->find(list, key1);
        uintptr_t prev = (uintptr_t) find_prev(list, key1);
        uintptr_t next = prev ^ iter->xpn;
        Node* node = (Node*) malloc(sizeof(Node));
        node->key = key2;
        node->xpn = (uintptr_t)iter ^ next;
        iter->xpn = prev ^ (uintptr_t)node;
        Node* n = (Node*) next;
        uintptr_t next1 = (uintptr_t) iter ^ n->xpn;
        n->xpn = (uintptr_t)node ^ next1;
        list->length++;
    }
}
void insert_before (struct LinkedList* list, uint32_t key1, uint32_t key2) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return;
    }
    if(list->head->key == key1) {
        push_front(list, key2);
    } else {
        Node* iter = list->find(list, key1);
        uintptr_t prev = (uintptr_t)find_prev(list, key1);
        uintptr_t next = prev ^ iter->xpn;
        Node* node = (Node*) malloc(sizeof(Node));
        node->key = key2;
        node->xpn = prev ^ (uintptr_t)iter;
        iter->xpn = (uintptr_t)node ^ next;
        Node* p = (Node*) prev;
        uintptr_t prev1 = p->xpn ^ (uintptr_t)iter;
        p->xpn = prev1 ^ (uintptr_t)node;
        list->length++;
    }
}
Node* remove(struct LinkedList* list, uint32_t key) {
    VERIFY_NULL_CHECK(list)
    if(list->is_empty(list)) {
        return 0;
    }
    if(list->head->key == key) {
        return list->pop_front(list);
    }
    if(list->tail->key == key) {
        return list->pop_back(list);
    }
    Node* iter = list->head;
    uintptr_t prev = NIL;
    bool find_key = false;
    while(iter != NULL) {
        Node* next = (Node*)(prev ^ iter->xpn);
        if(iter->key == key) {
            find_key = true;
            break;
        }
        prev = (uintptr_t)iter;
        iter = next;
    }
    if(find_key == false) {
        return NULL;
    }
    uintptr_t next = prev ^ (uintptr_t)iter;
    Node* p = (Node*) prev;
    Node* n = (Node*) next;
    uintptr_t p1 = p->xpn ^ (uintptr_t)iter;
    p->xpn = p1 ^ next;
    uintptr_t n1 = (uintptr_t)iter ^ n->xpn;
    n->xpn = prev ^ n1;
    list->length--;
    iter->xpn = NIL;
    return iter;
}
void reverse(struct LinkedList* list) {
    VERIFY_NULL_CHECK(list)
    Node* temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}
void append(struct LinkedList* list, struct LinkedList* list1) {
    VERIFY_NULL_CHECK(list)
    VERIFY_NULL_CHECK(list1)
    if(list->is_empty(list) && list1->is_empty(list1)) {
        free(list1);
        return;
    }
    if(list->is_empty(list)) {
        list->head = list1->head;
        list->tail = list1->tail;
        list->length = list1->length;
        free(list1);
        return;
    }
    if(list1->is_empty(list1)) {
        free(list1);
        return;
    }
    uintptr_t prev = list->tail->xpn ^ NIL;
    list->tail->xpn = prev ^ (uintptr_t)list1->head;
    uintptr_t next = NIL ^ list1->head->xpn;
    list1->head->xpn = (uintptr_t)list->tail ^ next;
    list->tail = list1->tail;
    list->length += list1->length;
    free(list1);
}

static struct LinkedList* new(void) {
    struct LinkedList* list = malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->size = &size;
    list->is_empty = &is_empty;
    list->push_front = &push_front;
    list->pop_front = &pop_front;
    list->push_back = &push_back;
    list->pop_back = &pop_back;
    list->find = &find;
    list->insert_after = &insert_after;
    list->insert_before = &insert_before;
    list->remove = &remove;
    list->reverse = &reverse;
    list->append = &append;
    return list;
}

static void del(struct LinkedList* list) {
    while(!list->is_empty(list)) {
        Node* node = list->pop_front(list);
        free(node);
    }
    free(list);
}

const struct LinkedListClass LinkedList = {.new = &new, .del = &del};


