#include <stdio.h>
#include <stdlib.h> // Added for malloc function

/* Return true (non-zero) if c is a whitespace character
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c) {
    return (c == ' ' || c == '\t') && c != '\0'; // Corrected comparison
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c) {
    return (c != ' ' && c != '\t') && c != '\0'; // Corrected logical operator and comparison
}

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */
char *token_start(char *str) {
    if (*str == '\0')
        return NULL; // Changed to NULL

    // Advances the pointer to the first non-space character
    while (space_char(*str)) {
        str++;
    }
    return str;
}

char *token_terminator(char *token) {
    // Advances the pointer to the end of the word
    while (non_space_char(*token)) {
        if (*token == '\n') {
            // do nothing
        }
        token++;
    }
    return token;
}

/* Counts the number of tokens in the string argument. */
int count_tokens(char *str) {
    int count = 0;
    while (*str != '\0') {
        if (non_space_char(*str)) {
            count++;
            str = token_terminator(str);
        } else {
            str++;
        }
    }
    return count;
}

/* Returns a freshly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {
    char *newstr = malloc(sizeof(char) * (len + 1));
    char *newstrslider = newstr;

    while (non_space_char(*inStr) && len > 0) { // Added len check
        *newstrslider = *inStr;
        inStr++;
        newstrslider++;
        len--; // Decrease len
    }

    // terminate with zero
    *newstrslider = '\0';

    // return pointer
    return newstr;
}
char **tokenize(char *str) {
    // Count the number of tokens
    int num_tokens = count_tokens(str);

    // Allocate memory for token pointers
    char **tokens = malloc(sizeof(char *) * (num_tokens + 1)); // +1 for NULL terminator
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int token_index = 0;
    while (*str != '\0') {
        str = token_start(str); // Move to the start of the next token
        if (*str != '\0') {
            char *terminator = token_terminator(str); // Find the end of the token
            int token_length = terminator - str; // Calculate the length of the token

            // Allocate memory for the token and copy the characters
            tokens[token_index] = copy_str(str, token_length);
            token_index++;

            str = terminator; // Move to the next character after the token
        }
    }

    tokens[token_index] = NULL; // Add NULL terminator to the token array
    return tokens;
}
/* Prints all tokens. */
void print_tokens(char **tokens) {
  int i;
  for (i = 0; tokens[i] != 0; i++) {
    if (tokens[i] == NULL) {
      return;
    }
    printf("\nTokens[%d] : %s\n", i, tokens[i]);
  }
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens){
  for (int i = 0;; i++) {
    if (tokens[i] == NULL) {  // break at the end of array
      return;
    }
    free(tokens[i]);
    tokens[i] = NULL;  // nullify pointer after freeing
  }

  free(tokens);
  tokens = NULL;  // nullify tokens itself
}
