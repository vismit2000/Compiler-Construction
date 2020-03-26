/***************************************
                |GROUP-09|
  Aditya Upadhyay      -   2017A7PS0083P
  Harpider Jot Singh   -   2017A7PS0057P
  Jaladi Lakshmi Teja  -   2017A7PS0068P
  Vishal Mittal        -   2017A7PS0080P
  Yash Vijay           -   2017A7PS0072P
*****************************************/
#ifndef TREE_ADT_DEF_H
#define TREE_ADT_DEF_H

#include<stdbool.h>
#include "parserDef.h"
#include "driver.h"

extern char non_terminal_string[NUM_OF_NONTERMINALS][MAX_SYMBOL_LENGTH];
extern char terminal_string[NUM_OF_TERMINALS][MAX_SYMBOL_LENGTH];

/**
 * @brief n-ary tree node structure
 *
 */
typedef struct TREENODE
{
	struct TREENODE *parent;
	struct TREENODE *sibling;
  struct TREENODE *leftmost_child;
  struct TREENODE *rightmost_child;

  struct TREENODE *node_inh;
  struct TREENODE *node_syn;

  symbol sym;
  TOKEN token;
  int rule_num;
  bool visited;
} tree_node;

#endif