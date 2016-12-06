/* Daniel Jang
 * CSE 374 Homework 5
 * 3/2/14
 * T9 Text Prediction
 * main.c
 */

#include "header.h"
#include "trie.c"

//t9 text prediction
//reads a file as a dictionary
//user inputs keypad input combinations to see the t9 text output prediction
int main(int argc, char** argv)
{

  FILE * file = fopen(argv[1], "r");
  char line[maxWordLength];
  char input[maxInput];
  struct T9node* root = newEmptyNode();

  if (file!=NULL)
    {
      while (fgets(line, maxWordLength, file) != NULL)
	{

	  int lineLength = strlen(line)-1; // -1 for \n char

	  char * lineMalloc = (char *)malloc(sizeof(line));
	  int i;
	  for (i=0;i<lineLength; i++)
	    {
	      lineMalloc[i] = line[i];
	    }
	  lineMalloc[lineLength] = '\0'; // gets rid of the last \n char
	  root = insertWord(root, lineMalloc, lineLength);
	}

      fclose(file);


      struct T9node * current = root;
      printf("Enter \"exit\" to quit.\n");
      while (strncmp(&input[0], "exit", maxInput) != 0)
	{
	  printf("Enter Key Sequence (or \"#\" for next word):\n");
	  scanf("%s", &input[0]);
	  if (strncmp(&input[0], "exit", maxInput) != 0) {
	    if (input[0] != '#')
	      {
		current = traverse(root, &input[0]);
	      } else {
	      current = traverse(current, &input[0]);
	    }
	    readNode(current);
	  }
	}
      freeNode(root);
    }


  else
    {
      fprintf(stderr, "Error: File %s not found...\n", argv[1]);
    }

  return 0;
}
