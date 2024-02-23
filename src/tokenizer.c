#include<stdio.h>
#include<stdlib.h>
#include"tokenizer.h"

// True if c is a whitespace character ('\t', ' ')

int space_char(char c){
  return (c ==  ' ' || c == '\t') && c != 0;
}

int non_space_char(char c){
  return c != ' ' && c != '\t' && c != 0;
}

// Returns a pointer to the 1st char of the next space-separated word in zero-terminated str;
// Return a null pointer if str doesn't contain any words.
char *word_start(char *word){
  if(*word == '\0'){
    return 0;
  }
  while(space_char(*word)){
    word++;
  }
  if(*word == '\0'){
    return 0;
  }
  return word;
}

// Returns a pointer terminator char following *word
char *word_terminator(char *word){
  while(non_space_char(*word)){
      word++;
  }
  return word;
}
// Counts the number of words in the string
int count_words(char *str){
  int count = 0;
  while(*str != '\0'){
    str = word_start(str);
    if(str == 0){
      return count;
    }
    str = word_terminator(str);
    count++;
  }
  return count;
}
char *copy_str(char *inStr, short len){
  char *copiedStr = malloc((len + 1) * sizeof(char));
  int i;
  for(i = 0; i < len; i++){
    copiedStr[i] = inStr[i];
  }
  copiedStr[i] = '\0';
  return copiedStr;
}
char **tokenize(char *str){
  int word_length = count_words(str);
  char **words = malloc((word_length + 1) * sizeof(char*));
  int i = 0;
  for(i = 0; i<word_length; i++){
    char* start = word_start(str);
    str = word_terminator(start);
    words[i] = copy_str(start, str - start);
  }
  words[i] = NULL;
  return words;
}
// Prints all tokens
void print_tokens(char **tokens){
  int i;
  for(i = 0; tokens[i] != 0; i++){
    printf("\ntokens[%d] : %s\n", i, tokens[i]);
  }
}
// Frees all tokens
void free_tokens(char **tokens){
  char**temp=tokens;
  while(*temp!= NULL){
    free(*temp);
    temp++;
  }
  free(tokens);
}
    
