#include "tokenizer.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>

// Initialize the history list and return a pointer to it
List *init_history()
{
  // Create a pointer to the history list
  List *history_list;
  // Initialize the pointer to NULL
  history_list = NULL;
  // Allocate memory for the history list using malloc()
  history_list = malloc(sizeof(List));
  // Return a pointer to the initialized history list
  return history_list;
}

// Add a new string to the history list
void add_history(List *list, char *string)
{
  // Allocate memory for a new item in the history list
  Item *new_item = (Item*) malloc(sizeof(Item));
  // Find the length of the new string
  int string_length = 0;
  while(string[string_length] != '\0'){
    string_length++;
  }
  // Copy the new string to the new item in the history list
  new_item->str = copy_str(string, string_length);

  // If the history list is empty, add the new item as the root
  if(list->root == NULL){
    list->root=new_item;
    new_item->id=1;
  }
  // Otherwise, add the new item to the end of the list
  else {
    Item *temp_item = list->root;
    while(temp_item->next != NULL){
      new_item->id += 1;
      temp_item = temp_item->next;
    }
    temp_item->next=new_item;
    new_item->id += 1;
  }
}

// Get a string from the history list based on its ID
char *get_history(List *list, int id)
{
  Item * curr_item = list->root;
  while(curr_item != 0) {
    // If the current item in the history list has the desired ID, return its string
    if(curr_item->id == id){
      return curr_item->str;
    }
    // Otherwise, move on to the next item in the history list
    curr_item = curr_item->next;
  }
  // If the desired ID is not found in the history list, return "Does not exist"
  return "Does not exist";
}

// Print all strings in the history list, along with their IDs
void print_history(List *list)
{
  Item *curr_item = list->root;
  int i = 1;
  // If the history list is empty, print a message and return
  if(list == NULL){
    printf("List does not have items\n");
    return;
  }
  // Otherwise, print the items in the history list, along with their IDs
  printf("Items in List: \n");
  while(curr_item != NULL){
    printf("[%d]%s\n", i, curr_item->str);
    curr_item = curr_item->next;
    i++;
  }
}

// Free all memory associated with the history list
void free_history(List *list)
{
  Item *curr_item;
  while(list->root != NULL){
    // Free the memory associated with the current item in the history list
    curr_item = list->root;
    list->root = list->root->next;
    free(curr_item);
  }
  // Free the memory associated with the history list itself
  free(list);
}