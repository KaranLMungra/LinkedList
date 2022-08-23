:wq:#include "library.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    struct LinkedList* list = LinkedList.new();
    assert(list->is_empty(list));
    list->push_front(list, 1);
    list->push_back(list, 2);
    list->insert_before(list, 2, 4);
    list->push_front(list, 3);
    list->insert_after(list, 1, 5);
    assert(2 == list->find(list, 2)->key);
    assert(3 == list->pop_front(list)->key);
    assert(2 == list->pop_back(list)->key);
    list->reverse(list);
    assert(4 == list->pop_front(list)->key);
    assert(5 == list->remove(list, 5)->key);
    struct LinkedList* list1 = LinkedList.new();
    list1->push_back(list, 2);
    list->append(list, list1);
    assert(2 == list->pop_back(list)->key);
    LinkedList.del(list);
    printf("Test Passed Successfully!");
    return 0;
}