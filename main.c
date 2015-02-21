/**
 * This is a program that takes in an advanced bash program and outputs
 * a standard bash program that has (hopefully) has no syntax errors
 * (a.k.a this is a Bash++ to Bash transpiler)
 *
 * Created by:
 * --------------------
 * Charles Bido
 * Sam Epstein
 * Mayur Kotamraju
 * (TJ) Emanuel Taylor  
 * --------------------
 * 
 * Notes:
 * - arg 1 is the bashfile++
 * - arg 2...n is the bashfile++ arguments
 */

/**
 * TODO:
 * - handle the rest of if...else reserved statements
 *    - if, elif
 *    - then, else, fi
 * - handle comments
 * [ ] validate if file is passed as argument
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** initDynamicArray(int, char const*[], int, int *);

char * createAndLoadDynArray(char **, int, int);

void createFile(char *);

int main(int argc, char const *argv[])
{
   int i = 0; // loop counter
   // this is the max string length;
   static const int MAX_STRING_LEN = 100;
   // this will become a dynamic array of dynamic c-style strings
   char **storage = NULL;
   // this will be the output
   char *output = NULL;

   // used to prevent access to bad memory
   int limiter = 0;
   int *pLimiter;
   pLimiter = &limiter;

   // printf("Running the function \"loadDynamicArray\"...\n"); // for debugging
   
   // This puts the dynamically allocated array into the "storage" pointer
   storage = initDynamicArray(argc, argv, MAX_STRING_LEN, pLimiter);
   // printf("The value of the limiter is: %d\n", limiter); // for debugging
   // printf("Success\n"); // for debugging

   if (storage == NULL)
   {
      printf("Error: a file was not passed in as an argument...\n");
      printf("Closing program...\n");
      return 0;
   }

   // This puts the generated string into the "output" pointer
   output = createAndLoadDynArray(storage, MAX_STRING_LEN, limiter);

   // This snippet of code will print every string in the array // for debugging
   
   // printf("Elements in the array:\n");
   // for (i = 0; i <= limiter; ++i)
   // {
   //    printf("storage[%d] = %s\n", i, storage[i]);
   // }
   // printf("A total of %d items were printed.\n", i);

   // this creates an "output.sh" file
   printf("Generating \"output.sh\"...\n");
   createFile(output);
   printf("Success!\n");

   // cleans memory
   // printf("debug: Cleaning storage memory...\n"); // for debugging
   for (i = limiter; i >= 0; i--) {
      free(storage[i]);
   }
   free(storage); // frees the memeory pointed by "storage"
   // printf("debug: Memory is clean!\n"); // for debugging
   // printf("debug: Cleaning output memory...\n"); // for debugging
   free(output); // frees the memeory pointed by "output"
   // printf("debug: Memory is clean!\n"); // for debugging
   return 0;
}

// function definitions go here

/**
 * This will return a dynamically allocated array of c-style strings, filled
 * with the contents of the file loaded form argv[1]
 * @param  argc Number of arguments
 * @param  argv Argument array
 * @param  max  The max length of each allocated string in the array
 * @param  *p   Points to an integer for modification outside of the scope of this function
 * @return      {{char ** }} Returns the dynArray
 */
char ** initDynamicArray(int argc, char const *argv[], int max, int *p)
{
   // printf("debug: entering initDynamicArray()\n"); // for debugging
   // determines # of elements the dynArray will have
   int wordCount = 0;
   // string buffer
   char buffer[max];
   // used to build dynamic array
   char **dynArray = NULL; 

   // printf("Opening file...\n"); // for debugging
   // opens the file from argv[1]
   if (argc < 2)
   {
      return NULL;
   }

   FILE *file = fopen(argv[1], "r");

   if (file == NULL)
   {
      return NULL;
   }
   // printf("debug: Success\n"); // for debugging

   // this will findout how many words are in the file
   // note: find a way to improve this? make this cleaner
   // printf("debug: Scanning through file to get wordCount...\n"); // for debugging
   while ( (fscanf(file, "%s[^\n]", buffer)) != EOF)
   {
      wordCount++;
      // printf("Scan print:%s\n", buffer); // for debugging
   }
   // printf("Success\n"); // for debugging

   // allocates memeory for the number of elements in the dynArray
   // printf("debug: Allocating Memory for dynArray...\n"); // for debugging
   dynArray = malloc(wordCount * sizeof(char*));
   // printf("debug: Success\n"); // for debugging
   // printf("debug: Allocating Memory for dynArray elements...\n"); // for debugging
   int i = 0; // loop counter
   for (i = 0; i < wordCount; i++)
   {
      dynArray[i] = malloc((max+1) * sizeof(char));
   }
   // printf("debug: Success\n"); // for debugging

   for (i=0; i < wordCount; i++)
   {
      dynArray[i][1] = '\0';
   }

   // reset file counter to the beginning of the file
   fseek(file, 0, SEEK_SET); 

   int loadNum = 0;
   // printf("debug: Scanning through file to get stuff...\n"); // for debugging
   while ( (fscanf(file, "%s", buffer)) != EOF)
   {
      // printf("2nd scan print:%s\n", buffer); // for debugging
      strcpy(dynArray[loadNum], buffer);
      // printf("The load num is %d\n", loadNum); // for debugging
      ++loadNum;
   }
   // printf("debug: The final load num is %d\n", loadNum);// for debugging
   // loading array with 
   
   // need to validate this
   // printf("debug: Closing the file...\n"); // for debugging
   fclose(file);
   // printf("debug: Success\n"); // for debugging

   // sets the int limiter from the main function to the value of wordCount-1
   *p = wordCount-1;

   // printf("debug: exiting initDynamicArray()\n"); // for debugging
   return dynArray;
}

char* createAndLoadDynArray(char **s, int max, int wc)
{
   char *dynArray; // temp array
   int sizeOfStorage = 0;
   int sizeOfOutput = 0;
   // determine size of array
   int i = 0; // loop counter
   int j = 0; // loop counter
   for (i = 0; i <= wc; i++)
   {
      j = 0;
      while(s[i][j] != '\0')
      {
         // printf("debug: s[%d][%d] = %c\n",i, j, s[i][j]);
         sizeOfOutput++;
         // printf("debug: sizeOfOutput = %d\n", sizeOfOutput);
         j++;
      }
      // printf("debug: s[%d] = %s\n",i , s[i]);
      sizeOfStorage++;
      sizeOfOutput+=4;
      // printf("debug: sizeOfStorage = %d\n", sizeOfStorage);
   }
   // printf("debug: sizeOfOutput = %d\n", sizeOfOutput);

   // allocates memeory for the number of elements in the dynArray
   // printf("debug: Allocating Memory for dynArray...\n"); // for debugging
   dynArray = malloc(sizeOfOutput * sizeof(char*));
   // printf("debug: Success\n"); // for debugging

   // LOAD DATA INTO ARRAY HERE!!!
   i = 0;
   int k = 0;
   for (i=0; i < sizeOfStorage; i++) {
      if (strcmp(s[i], "if") == 0 || strcmp(s[i], "elif") == 0)
      {
         // printf("debug: entered \"if\" condition\n");
         j = 0;
         dynArray[k] = '\n';
         k++;
         while (s[i][j] != '\0')
         {
            if (s[i][j] != '\0')
            {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = ' ';
         k++;

      } else if (strcmp(s[i], "then") == 0 || strcmp(s[i], "else") == 0 || strcmp(s[i], "fi") == 0) {
         // printf("debug: entered \"then\" condition\n");
         dynArray[k] = '\n';
         k++;
         j = 0;
         while (s[i][j] != '\0')
         {
            if (s[i][j] != '\0')
            {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = '\n';
         k++;

      }
      else if (strcmp(s[i], "=") == 0)
      {
         dynArray[k-1] = '=';
      } 
      else if (s[i][0] == '#')
      {
         j = 0;   
         while (s[i][j] != '\0')
         {
            if (s[i][j] == '[') {
               dynArray[k] = s[i][j++];
               k++;
               dynArray[k] = ' ';
               k++;
            } 
            else if (s[i][j] == ']')
            {
               dynArray[k] = ' ';
               k++;
               dynArray[k] = s[i][j++];
               k++;
            }
            else 
            {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k++] = '\n';
      }
      else
      {
         // printf("debug: entered else condition\n");
         j = 0;

         while (s[i][j] != '\0')
         {
            if (s[i][j] == '[')
            {
               dynArray[k] = s[i][j++];
               k++;
               dynArray[k] = ' ';
               k++;
            }
            else if (s[i][j] == ']')
            {
               dynArray[k] = ' ';
               k++;
               dynArray[k] = s[i][j++];
               k++;
            }
            else
            {
               dynArray[k] = s[i][j++];
               k++;
            }
         }
         dynArray[k] = ' ';
         k++;
      }
   }
   // printf("debug: output = \"%s\"\n", dynArray);

   return dynArray;
}

void createFile(char *out)
{
   // printf("debug: creating the file...\n");
   FILE *file = fopen("output.sh", "w");
   // printf("debug: Success!\n");

   // printf("debug: storing the values into the file...\n");
   fprintf(file, "%s\n", out);
   // printf("debug: success!\n");

   // printf("debug: closing the file...\n");
   fclose(file);
   // printf("debug: success!\n");
}






