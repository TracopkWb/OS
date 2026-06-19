#include <stdio.h>
#include <stdlib.h>
int main() {
   char text[100];
   // printf() displays the string inside quotation
   printf("Hello Tracopk!");
   int numVowels = 0;
   int numBlankSpaces = 0;

   printf("\tEnter Text: \n");
   fgets(text, sizeof(text), stdin);

   printf("You entered: %s", text);

   for(int i = 0; text[i] != '\0'; i++) {
      
      if((text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u')) {
         //printf("%c is a vowel letter.\n", msg[i]);
         numVowels++;
      }else if(text[i] == ' ') {
         //printf("%c is a blank space.\n", msg[i]);
         numBlankSpaces++;
      }
   }

   printf("Number of vowels: %d\n", numVowels);
   printf("Number of blank spaces: %d\n", numBlankSpaces);

   return 0;
}