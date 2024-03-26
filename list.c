#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node *createNode(void * data) {
    Node *new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List *createList() {
  List *list = (List *)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void *firstList(List * list) {
  if (list->head == NULL)
    return NULL;
  list->current = list->head;
  return list->head->data;
}

void *nextList(List * list) {
  if (list->current == NULL)
    return NULL;
  if (list->current->next == NULL)
    return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void *lastList(List * list) { //La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
  if (list->tail == NULL)
    return NULL;
  list->current = list->tail;
  return list->current->data;
}

void *prevList(List * list) { //La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.
  if(list->current == NULL)
    return NULL;
  if(list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List *list, void *data) {
  Node *newNode = createNode(data);
  if(list->head) {
    list->head->prev = newNode;
    newNode->next = list->head;
  }
  list->head = newNode;
  Node *aux = list->head;
  while(aux->next != NULL)
    aux = aux->next;
  list->tail = aux;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List *list, void *data) {
  Node *newNode = createNode(data);
  if(list->current == NULL)
    pushFront(list,data);
  else {
    newNode->prev = list->current;
    newNode->next = list->current->next;
    if(list->current->next)
      list->current->next->prev = newNode;
    list->current->next = newNode;
    if(list->current == list->tail)
      list->tail = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List * list) {
  if(list->current == NULL)
    return NULL;
  void *data = list->current->data;
  if(list->current == list->head) {
    list->head = list->current->next;
    if(list->head)
      list->head->prev = NULL;
  }
  if(list->current == list->tail) {
    list->tail = list->current->prev;
    if(list->tail)
      list->tail->next = NULL;
  }
  free(list->current);
  list->current = NULL;
  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}