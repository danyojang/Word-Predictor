/* Daniel Jang
 * CSE 374 Homework 5
 * 3/2/14
 * T9 Text Prediction
 * trie.c
 */


#include "header.h"

//creates new empty t9node with null data and null next pointers
//prints to stderr and exits if it cannot allocate memory
struct T9node * newEmptyNode()
{
  struct T9node * root =(struct T9node*)malloc(sizeof(struct T9node));
  if (root == NULL)
    {
      fprintf(stderr, "cannot allocate memory");
      exit(-1);
    }
  root->data=NULL;
  int i;
  for (i = 0; i < sizeNodeArray; i++)
    {
      root->next[i]=NULL;
    }

  return root;

}

//creates new t9node with char pointer word and null next pointers
//prints to stderr and exits if it cannot allocate memory
struct T9node * newNode(char * word)
{
  struct T9node * node =(struct T9node*)malloc(sizeof(struct T9node));
  if (node == NULL)
    {
      fprintf(stderr, "cannot allocate memory");
      exit(-1);
    }
  node->data=word;
  int i;
  for (i = 0; i < sizeNodeArray; i++)
    {
      node->next[i]=NULL;
    }

  return node;

}

//frees the node and its children
void freeNode(struct T9node * node)
{
  if (node)
    {
      int i;
      for (i=0; i<sizeNodeArray; i++)
	{
	  freeNode(node->next[i]);
	}
      if (node->data)
	{
	  free(node->data);
	}
      free(node);
    }
}

//adds word to node prints to stderr if node is null
void addToNode(struct T9node * node, char * word)
{
  if (node != NULL)
    {
      node->data = word;
    } else
    {
      fprintf(stderr, "Error: Cannot add word to node. Node is NULL\n");
    }

}

//insert the given word to the trie, prints to stderr if root trie is null
struct T9node * insertWord(struct T9node * root, char * word, int wordLength)
{
  if (!root)
    {
      fprintf(stderr, "Error: root not found\n");
    } else
    {
      struct T9node * current = root;
      int i = 0;

      for (i = 0; i < wordLength; i++)
	{
	  int n = convertCharToNodeInt(word[i]);
	  if (current && n!='\n')
	    {
	      if (!(current->next[n]))
		{
		  struct T9node * pathNode = newEmptyNode();
		  current->next[n] = pathNode;

		}
	      current = current->next[n];
	    }


	}

      while (current && (current->data != NULL))
	{
	  if (!(current->next[pound])) {
	    struct T9node * poundNode = newEmptyNode();
	    current->next[pound] = poundNode;
	  }
	  current = current->next[pound];

	}

      addToNode(current, word);
    }
  return root;
}

//prints the data of the node in single quotes
void readNode(struct T9node * node) {
  if (node)
    {
      if (node->data != NULL)
	{

	  printf("\t'%s'\n", node->data);
	}

    }
}

// returns the node corresponding to the keypad input
// returns null if it is not in the dictionary or if there are no t9onyms
// and prints whether it is not in the dictionary or if there are no t9onyms
struct T9node * traverse(struct T9node * node, char * input) {
  struct T9node * current = node;
  int length = strlen(input);
  int i = 0;

  char lastChar = input[length-1];

  if (current && input) {
    while (i < length && current->next[convertKeyToNodeInt(input[i])])
      {

	current = current->next[convertKeyToNodeInt(input[i])];
	i++;


      }

    // 3 cases next is null, i == length but data is null, i == length but data is not null (found)
    if (i != length) // current->next is null
      {

	printNotFound(lastChar);
	return current->next[convertKeyToNodeInt(input[i])];
      } else {
      if (current->data == NULL) { //2nd case
	printNotFound(lastChar);
      }

      //3rd case just returns current (found!)
    }
  }

  return current;


}

//prints whether it is not in the dictionary or if there are no t9onyms given char c
void printNotFound(char c)
{
  if (c == '#')
    {
      fprintf(stdout, "\tThere are no more T9onyms\n");
    } else if ('2' <=c && c <= '9')
    {
      fprintf(stdout, "\tNot found in current dictionary\n");
    } else {
    fprintf(stderr, "ONLY CHARACTERS '2-9' & '#' ARE ALLOWED!\n");
  }
}

//converts a character of the alphabet or '#' to a node array position 0-8
int convertCharToNodeInt(char c)
{

  if ('a'<=c && c<='c') {
    return 0; // 2 numpad
  } else if ('d'<=c && c<='f') {
    return 1; // 3 numpad
  } else if ('g'<=c && c<='i') {
    return 2; // 4 numpad
  } else if ('j'<=c && c<='l') {
    return 3; // 5 numpad
  } else if ('m'<=c && c<='o') {
    return 4; // 6 numpad
  } else if ('p'<=c && c<='s') {
    return 5; // 7 numpad
  } else if ('t'<=c && c<='v') {
    return 6; // 8 numpad
  } else if ('w'<=c && c<='z') {
    return 7; // 9 numpad
  } else if (c=='#') {
    return pound; // # numpad
  } else if (c == '\n') {
    return '\n';
  } else {
    fprintf(stderr, "CAN ONLY CONVERT 'a-z' & '#'!!");
    return -1;

  }

}

//converts the keypad input '2-9' and '#' to a node array position 0-8
int convertKeyToNodeInt(char c) {
  if ('2'<=c && c<='9')
    {
      return c - '0' - keyDisplacement;
    } else if (c == '#')
    {
      return pound; // # numpad
    } else
    {
      fprintf(stderr, "ONLY CHARACTERS '2-9' & '#' ARE ALLOWED!\n");
      return -1;

    }
}
