#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

#define MAX 400 

int main(){
  char userInput[MAX];
  char** tokens;
  List* history = init_history();

  printf("> h = history, * = specific history, q = quit\n");
  while(1){
    printf(">");
    fgets(userInput, MAX, stdin);

    printf("String typed : %s", userInput);

    // Remove newline character from input
    userInput[strcspn(userInput, "\n")] = 0;
    
    tokens = tokenize(userInput);
    print_tokens(tokens);
    add_history(history, userInput);

    if(userInput[0] == 'q'){
      break;
    }
    else if(userInput[0] == 'h'){
      print_history(history);
    }
    else if(userInput[0] == '*'){
      char *h = get_history(history, atoi(userInput + 1));
      if(h != NULL){
        char** tokens = tokenize(h); // Memory allocated here
        printf("History: %s\n", h);
        printf("Tokenized history:\n");
        print_tokens(tokens);
        free_tokens(tokens); // Memory freed here
      }else{
        printf("Invalid history index\n");
        // No need to free tokens here, as it's not allocated
      }
    }

  }
  // Free history list
  free_history(history);
  return 0;
}
