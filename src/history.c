#include<stdio.h>
#include<stdlib.h>
#include"history.h"
#include"tokenizer.h"

List *init_history(){
  List *history;
  history = NULL;
  history = malloc(sizeof(List));
  return history;
}

void add_history(List *list, char *str){
  Item *new = (Item*)malloc(sizeof(Item));
  int i = 0;
  while(str[i] != '\0'){
    i++;
  }
  new->str = copy_str(str, i);

  if(list->root == NULL){
    list->root=new;
    new->id=1;
  }
  
  else{
    Item *temp = list->root;
    new->id = 1;
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
  while(curr != 0){
    if(curr->id == id){
      return curr->str;
    }
    curr = curr->next;
  }
  return "Does not exist";
}

void print_history(List *list){
  Item *curr = list->root;
  int i = 1;
  if(list == NULL){
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
  Item *curr;
  while(list->root != NULL){
    curr = list->root;
    list->root = list->root->next;
    free(curr);
  }
}
