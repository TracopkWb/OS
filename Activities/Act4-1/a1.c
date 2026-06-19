#include <stdio.h>
#include <stdlib.h>
int main() {
   char text[100];
   // printf() displays the string inside quotation
   printf("Hello Tracopk!");
   int numVowels = 0;
   int numBlankSpaces = 0;
   int numConsonants = 0;
   int numUppercase = 0;

   printf("\tEnter Text: \n");
   fgets(text, sizeof(text), stdin);

   printf("You entered: %s", text);

   for(int i = 0; text[i] != '\0'; i++) {
      
      if((text[i] >= 'A' && text[i] <= 'Z')) {
         //printf("%c is an uppercase letter.\n", msg[i]);
         numUppercase++;
      }
      else if (!((text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u')))
      {
         
         numConsonants++;
      }
   }

   printf("Number of vowels: %d\n", numVowels);
   printf("Number of blank spaces: %d\n", numBlankSpaces);
   printf("Number of uppercase letters: %d\n", numUppercase);
   printf("Number of consonants: %d\n", numConsonants);

   return 0;
}