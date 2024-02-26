#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"history.h"
#include"tokenizer.h"

List *init_history(){
  List *history = malloc(sizeof(List));
  if (history == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  history->root = NULL;
  return history;
}

void add_history(List *list, char *str){
  Item *new = (Item*)malloc(sizeof(Item));
  if (new == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  new->next = NULL;
  new->str = strdup(str); // You can use strdup to simplify string copying
  
  if(list->root == NULL){
    list->root = new;
    new->id = 1;
  } else {
    Item *temp = list->root;
    new->id = 0;
    while(temp->next != NULL){
      new->id += 1;
      temp = temp->next;
    }
    temp->next = new;
    new->id += 1;  
  }
}

char *get_history(List *list, int id){
  Item *curr = list->root;
  while(curr != NULL){
    if(curr->id == id){
      return curr->str;
    }
    curr = curr->next;
  }
  return NULL; // Returning NULL indicates that the history item was not found
}

void print_history(List *list){
  Item *curr = list->root;
  int i = 1;
  if(list == NULL || list->root == NULL){
    printf("List does not have items\n");
    return;
  }
  printf("Items in List: \n");
  while(curr != NULL){
    printf("[%d]%s\n", i, curr->str);
    curr = curr->next;
    i++;
  }
}

void free_history(List *list){
  if (list == NULL) return;
  Item *curr;
  while(list->root != NULL){
    curr = list->root;
    list->root = list->root->next;
    free(curr->str); // Freeing the string
    free(curr);      // Freeing the item
  }
  free(list); // Freeing the list itself
}
