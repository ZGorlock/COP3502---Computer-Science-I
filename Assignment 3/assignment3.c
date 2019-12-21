//Zachary Gill
//COP 3502C Spring 2015
//Section 1
//Assignment 3
//03-29-2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  openFile(FILE**, char[], char[]);
void closeFile(FILE**);
void permute(char[], int, FILE**);
void swapChars(char[], int, int);

int main()
{
  FILE *fi = NULL; //pointer for input file
  FILE *fo = NULL; //pointer for output file

  if (openFile(&fi, "AssignmentThreeInput.txt", "r")) { //open fi for input
    if (openFile(&fo, "AssignmentThreeOutput.txt", "w")) { //open fo for output
      
      char word[128];
      while (fgets(word, 128, fi)) { //get line from fi 
        if (word[strlen(word) - 1] == '\n')
          word[strlen(word) - 1] = '\0'; //trim newline off string
        printf("Permutating %s\n", word);
        permute(word, 0, &fo); //permute word and output to fo
      }

      closeFile(&fo); //close output file
    }
    closeFile(&fi); //close input file
    printf("Processed input and wrote output!\n");
  }

  return 0;
}

//open the file name as type with the passed FILE pointer
int openFile(FILE** f, char name[], char type[])
{
  printf("Trying to open file %s\n", name);
  *f = fopen(name, type); //open file name for read

  if (f == NULL) { //failed
    printf("Failed to open file %s\n", name);
    return 0;
  }
  else { //success
    printf("Successfully opened file %s\n", name);
    return 1;
  }
}

//closes the passed FILE pointer f
void closeFile(FILE** f)
{
  fclose(*f); //close file
  return;
}

//permutes word and outputs permutations to FILE pointer f
void permute(char word[], int locked, FILE** f)
{
  int j;

  if (locked == strlen(word)) { //if all characters are locked
    fprintf(*f, "%s\n", word); //output permutation
  }
  else {
    for (j = locked; j < (int)strlen(word); j++) { //for every character passes the last locked one
      swapChars(word, locked, j); //move that character to first unlocked position
      permute(word, locked + 1, f); //recusively permute the word with the newly swapped character now locked
      swapChars(word, j, locked); //move character back to original position
    }
  }
}

//swaps chars at location i and j in string word
void swapChars(char word[], int i, int j)
{
  char temp = word[i];
  word[i] = word[j];
  word[j] = temp;
}