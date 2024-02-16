#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

#define MAX 1024

int main() {
  // declare variables for user input, and tokens
  char userInput[MAX];
  char** tokens;
  List* history = init_history(); // initialize list

  printf("h= history, != specific history, q= quit\n");

  while (1) { // loop until user quits
    printf("Enter some words:");
    fgets(userInput, MAX, stdin); // user input
    
    printf("String typed: %s", userInput);
    userInput[strcspn(userInput, "\n")] = 0;

    tokens = tokenize(userInput);
    print_tokens(tokens);
    add_history(history, userInput);

    if (userInput[0] == 'q') { //quits program
      break;
    }
    else if (userInput[0] == 'h') { // prints history
      print_history(history);
    }
    else if (userInput[0] == '!') {
      char *h = get_history(history, atoi(userInput + 1)); // prints a specific item
      if (h != NULL) {
        char** tokens = tokenize(h);
        printf("History: %s\n", h);
        printf("Tokenized history:\n");
        print_tokens(tokens);
        free_tokens(tokens);
      } else {
        printf("Invalid history index\n");
      }
    }
  }

  // Free history list
  free_history(history);

  return 0;
}