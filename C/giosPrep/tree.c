// tree.c -- use structs and pointers to build a tree of nodes
/* compile with:
cc -g -Wall -o tree tree.c
*/
#include <stdio.h> // for printf()
#include <stdlib.h> // for malloc()
#include <string.h> //for strcat()
typedef struct TreeNode {
    int value;
    struct TreeNode *left; //left value is lesser. Also, we cannot delcare Treenode inside its own declaration & can use 'struct <name> <var>'
    struct TreeNode *right; //right value is more
} TreeNode;

void addValue (TreeNode *node, int value)
{
    if (value < node->value) {
        // left side
        if (node->left == NULL) {
            TreeNode *newNode = malloc (sizeof(TreeNode));
            newNode->value = value;
            newNode->left = newNode->right = NULL;
            node->left = newNode;
        } else {
            addValue (node->left, value); //browse further
        }
    } else {
    // right side
        if (node->right == NULL) {
            TreeNode *newNode = malloc (sizeof(TreeNode));
            newNode->value = value;
            newNode->left = newNode->right = NULL;
            node->right = newNode;
        } else {
            addValue (node->right, value);
        }
    }
} // addValue

#define TRUE 1
#define FALSE 0

int findValue (TreeNode *node, int value)
{
    if (node == NULL) {
        return (FALSE);
    } else if (node->value == value) {
        return (TRUE);
    } else {
        if (value < node->value) {
            return (findValue(node->left, value));
        } else {
            return (findValue(node->right, value));
        }
    }
} // findValue

void printTree (TreeNode *node, int lvl) {
    if (node!=NULL) {
        if (node->right!=NULL) { printTree(node->right,lvl+1) ; }
        char ind[100]="";
        for(int i=0;i<lvl;i++) {strcat(ind,"\t");}
        printf("%s%d\n",ind,node->value);
        if (node->left!=NULL) { printTree(node->left,lvl+1) ; }
    }
}

int main (int argc, char *argv[])
{
    for(int i=0;i<=argc;i++) {
        printf("ARG:%d:%s\n",i,*(argv+i));
    }
    TreeNode root;
    // put 23 in manually to bootstrap the tree
    root.value = 23;
    root.left = root.right = NULL;
    // now add some stuff
    addValue (&root, 5);
    addValue (&root, 50);
    addValue (&root, 8);
    addValue (&root, 2);
    addValue (&root, 34);
    if (findValue(&root, 23)) {
        printf ("23 lives in the tree\n");
    } else {
        printf ("23 does not live in the tree\n");
    }
    if (findValue(&root, 42)) {
        printf ("42 lives in the tree\n");
    } else {
        printf ("42 does not live in the tree\n");
    }

    printTree(&root,0);
    return (0);
} // main