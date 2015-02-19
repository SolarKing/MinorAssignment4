/**
 * Write a program that takes in an advanced bash program and outputs
 * a standard bash program that has no syntax errors
 * (a.k.a create a Bash++ to Bash transpiler)
 *
 * Created by:
 * --------------------
 * Charles Bido
 * Sam Epstein
 * Mayur Kotamraju
 * (TJ) Emanuel Taylor  
 * --------------------
 * due next Monday
 *
 * FEATURES TO IMPLEMENT
 * ---------------------
 * - bash does not allow spaces, tabs, or newlines around
 *   the "=" symbol used in initialization
 * - the "then" keyword in bash if statements must be on a different line
 *   than the the "if" itself
 * - Also, the brackets ([,]) in bash’s conditionals must have spaces
 *   between the bracket and the condition itself.
 * - 
 * 
 * Notes:
 * - use redirection instead of fileio
 * - allow newlines in redirection 
 * - arg 1 is the bashfile++
 * - arg 2...n is the bashfile++ arguments
 */

// (i.e of valid bash++ syntax but invalid bash syntax)
// num    =                0            
//     if [x -lt 5] then ...

// Your preprocessor will need to change those two statements 
// (and others like them) in the output to be:
// 
// num=0
// if [ x -lt 5 ]
//     then

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// globals go here (try to avoid this)



// function prototypes go here
char ** initDynamicArray(int, char const*[], int);


char * createAndLoadDynArray(char **, int);

// void cleanDynamicArray(char ***, int);

// void openFile(int, char *[]);
// void getWordCount(char *[]);

// main goes here
int main(int argc, char const *argv[]) {

   // this is the max string length;
   static const int MAX_STRING_LEN = 100;

   // this will become a dynamic array of dynamic c-style strings
   char **storage = NULL;
   // this will be the output
   char *output = NULL;

   // int x; // idk what this does?

   // printf("Running the function \"loadDynamicArray\"...\n"); // for debugging

   /**
    * This puts the dynamically allocated array into the "storage" pointer
    */
   storage = initDynamicArray(argc, argv, MAX_STRING_LEN);

   // printf("Success\n"); // for debugging
   output = createAndLoadDynArray(storage, MAX_STRING_LEN);

   /**
    * This snippet of code will print every string in the array.
    */
   
   printf("Elements in the array:\n");
   int storageLength = 0;
   do {
      printf("storage[%d] = %s\n", storageLength, storage[storageLength]);
      ++storageLength;
   } while (storage[storageLength] != '\0');
   // printf("A total of %d items were printed.\n", i);

   // clean memory
   printf("Cleaning storage memory...\n"); // for debugging
   for (int i = storageLength-1; i >= 0; i--) {
      free(storage[i]);
   }
   free(storage);
   printf("Memory is clean!\n"); // for debugging

   printf("Cleaning output memory...\n"); // for debugging
   free(output);
   printf("Memory is clean!\n"); // for debugging
   return 0;
}

// function definitions go here

/**
 * This will return a dynamically allocated array of c-style strings, filled
 * with the contents of the file loaded form argv[1]
 * @param  argc Number of arguments
 * @param  argv Argument array
 * @param  max  The max length of each allocated string in the array
 * @return      {{char ** }} Returns the dynArray
 */
char ** initDynamicArray(int argc, char const *argv[], int max) {

   int wordCount = 0; // determines # of elements the dynArray will have
   char buffer[max]; // string buffer
   char **dynArray = NULL; // used to build dynamic array

   // opens file

   // printf("Opening file...\n"); // for debugging
   // opens the file from argv[1]
   FILE *file = fopen(argv[1], "r");
   // printf("Success\n"); // for debugging

   // this will findout how many words are in the file
   // note: find a way to improve this? make this cleaner
   // printf("Scanning through file to get wordCount...\n"); // for debugging
   while ( (fscanf(file, "%s", buffer)) != EOF) {
      wordCount++;
      // printf("Scan print:%s\n", buffer);
   }
   // printf("Success\n"); // for debugging

   // allocates memeory for the number of elements in the dynArray
   // printf("Allocating Memory for dynArray...\n"); // for debugging
   dynArray = malloc(wordCount * sizeof(char*));
   // printf("Success\n"); // for debugging

   // printf("Allocating Memory for dynArray elements...\n"); // for debugging
   for (int i = 0; i < wordCount; i++) {
      dynArray[i] = malloc((max+1) * sizeof(char));
   }
   // printf("Success\n"); // for debugging


   // reset file counter to the beginning of the file
   fseek(file, 0, SEEK_SET); 

   int loadNum = 0;
   // printf("Scanning through file to get stuff...\n"); // for debugging
   while ( (fscanf(file, "%s", buffer)) != EOF) {
      // printf("2nd scan print:%s\n", buffer); // for debugging
      strcpy(dynArray[loadNum], buffer);
      // printf("The load num is %d\n", loadNum); // for debugging
      ++loadNum;
      
   }
   // printf("The final load num is %d\n", loadNum);// for debugging
   // loading array with 
   
   // need to validate this
   // printf("Closing the file...\n"); // for debugging
   fclose(file);
   // printf("Success\n"); // for debugging
   return dynArray;
}

char* createAndLoadDynArray(char **s, int max) {

   // CREATE OUTPUT ARRAY HERE!!!

   char *dynArray; // temp array
   int sizeOfStorage = 0;
   int sizeOfOutput = 0;
   // determine size of array
   int i = 0;
   while (s[i] != NULL) {
      int j = 0;
      while(s[i][j] != '\0') {
         // printf("debug: s[i][j] = %c\n", s[i][j]);
         sizeOfOutput++;
         // printf("debug: sizeOfStorage = %d\n", sizeOfStorage);
         j++;
      }
      //printf("debug: s[i] = %s\n", s[i]);
      sizeOfStorage++;
      sizeOfOutput+=4;
      //printf("debug: sizeOfStorage = %d\n", sizeOfStorage);
      i++;
   }
   printf("debug: sizeOfOutput = %d\n", sizeOfOutput);

   // allocates memeory for the number of elements in the dynArray
   printf("debug: Allocating Memory for dynArray...\n"); // for debugging
   dynArray = malloc(sizeOfOutput * sizeof(char*));
   printf("debug: Success\n"); // for debugging

   // LOAD DATA INTO ARRAY HERE!!!
   i = 0;
   int k = 0;
   for (int i=0; i < sizeOfStorage; i++) {
      if (strcmp(s[i], "if") == 0) {
         printf("debug: entered \"if\" condition\n");
         int j = 0;
         dynArray[k] = '\n';
         k++;
         while (s[i][j] != '\0') {
            if (s[i][j] != '\0') {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = ' ';
         k++;

      } else if (strcmp(s[i], "then") == 0) {
         printf("debug: entered \"then\" condition\n");
         dynArray[k] = '\n';
         k++;
         int j = 0;
         while (s[i][j] != '\0') {
            if (s[i][j] != '\0') {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = '\n';
         k++;

      } else if (strcmp(s[i], "=") == 0) {
         dynArray[k-1] = '=';
         k;
      } else {
         printf("debug: entered else condition\n");
         int j = 0;

         while (s[i][j] != '\0') {
            if (s[i][j] == '[') {
               dynArray[k] = s[i][j++];
               k++;
               dynArray[k] = ' ';
               k++;
            } else if (s[i][j] == ']') {
               dynArray[k] = ' ';
               k++;
               dynArray[k] = s[i][j++];
               k++;
            } else /*(s[i][j] != '\0')*/ {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = ' ';
         k++;
      }
   }
   printf("debug: output = \"%s\"\n", dynArray);

   return dynArray;
}






