
#include <stdio.h>
#include <string.h>

// All the keywords in the language
char keywords[32][10] = {
    "goto", "break", "continue", "return", "if", "else", "while", "do", "for",
    "switch", "case", "default", "struct", "union", "enum", "typedef", "sizeof",
    "static", "auto", "register", "extern", "const", "volatile", "restrict",
    "asm", "int", "long", "short", "char", "float", "double",
    "void"};

// separators
char separators[9] = {'(', ')', '{', '}', '[', ']', ';', ',', ':'};
char operators[12] = {'+', '-', '=', '!', '^', '&', '*', '/', '<', '>', '?', '|'};

// checks if the given character is a alphabet or not
int isAlpha(char ch) {
  return  ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

// checks if the given character is a number or not
int isNum(char ch) {
  return ( ch >= '0' && ch <= '9');
}

int main() {
  FILE *fp;
  char line[100];
  fp = fopen("input.c", "r");

  // Read file line by line
  while (fgets(line, 100, fp)) {
      int left = 0, right = strlen(line);
      while (line[left] == ' ') // Goto non white space character from left
          left++; // increment left pointer

    // Goto non white space or newline character from right
      while (line[right - 1] == ' ' || line[right - 1] == '\n')
        right--; // decrement right pointer

      line[right] = '\0'; // set ending of string

      // preprocessor directive check
      if (line[left] == '#') {
          printf("%s is a preprocessor directive\n", line);
          continue;
      }

      // check for keywords
      while (left < right) {
          // strip spaces
          while (line[left] == ' ')
              left++;

          // check for separators
          for (int i = 0; i < 9; i++) {
              if (line[left] == separators[i]) {
                  printf("%c is a seperator\n", line[left]);
                  left++;
                  break; 
              }
          }

          // check for operators
          for (int i = 0; i < 12; i++) {
              if (line[left] == operators[i]) {
                  printf("%c is a operator\n", line[left]);
                  left++;
                  break; 
              }
          }

          // strip spaces
          while (line[left] == ' ')
              left++;


          // Check if we encounter a string i.e " "
          if (line[left] == '\"') {
              left++;
              int len = 0; // length of string

              // move till we encounter a " or end of line
              while (left + len <= right && line[left + len] != '\"' ) {
                  len++; // increment length of the string
              }

              // Copy string to substr
              char substr[100];
              memcpy(substr, &line[left], len);
              substr[len] = '\0';

              // print substr string
              printf("%s is a string\n", substr);
              left += len + 1;
          }

          // get word
          int len = 0;
          while (left + len <= right && (isAlpha(line[left + len]) || isNum(line[left + len]))) {
              len++; // increment length of the word
          }

          // if word found
          if (len) {
              // copy word to substr
              char substr[30];
              memcpy(substr, &line[left], len);
              substr[len] = '\0';

              left += len; // increment left pointer
              int isKeyword = 0;
              // check if the word is a keyword
              for (int i = 0; i < 32; i++) {
                  if (strcmp(substr, keywords[i]) == 0) {
                      isKeyword = 1;
                      break;
                  }
              }

              if (isKeyword) {
                  printf("%s is a keyword\n", substr);
              } else {
                  // if the word is starting with number, it is a number else it is a identifier
                  if (isNum(substr[0])) {
                      printf("%s is a number\n", substr);
                  } else {
                      printf("%s is an identifier\n", substr);
                  }
              }
          }
      }
  }
  return 0;
}