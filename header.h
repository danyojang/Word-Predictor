/* Daniel Jang
 * CSE 374 Homework 5
 * 3/2/14
 * T9 Text Prediction
 * header.h
 */


#ifndef HEADER_H_
#define HEADER_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sizeNodeArray 9
#define pound 8
#define keyDisplacement 2
#define maxWordLength 20
#define maxInput 100

struct T9node
{
  char * data;
  struct T9node * next[9];
};

struct T9node * newEmptyNode();
struct T9node * newNode(char * word);
void freeNode(struct T9node * root);
void addToNode(struct T9node * node, char * word);
struct T9node * insertWord(struct T9node * root, char * word, int wordLength);
int convertCharToNodeInt(char c);
int convertKeyToNodeInt(char c);
struct T9node * traverse(struct T9node * root, char * input);
void printNotFound(char c);
void readNode(struct T9node * node);

#endif /* HEADER_H_ */
