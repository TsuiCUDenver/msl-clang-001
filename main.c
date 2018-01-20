#include<stdlib.h>
#include<stdio.h>


struct bin_tree {
    char* data;
    struct bin_tree * right, * left;
};
typedef struct bin_tree node;

//Prototype
void delTree(node *tree);
void printPostorder(node *tree);
void printInorder(node *tree);
void printPreorder(node *tree);
void insert(node ** tree, char* val);
void toOutput(node * tree, FILE *fileOutput);
node* search(node ** tree, char* val);//WIP, only searches head. Might not need function


int main() {

    node *root;
    node *temp;
    root = NULL;

    int i;
    char *lines[54];//54 words in input02
    FILE *fileInput = fopen("input02.txt", "r");//Open the file to read mode

    for (i = 0; i < 54; ++i) {
        lines[i] = malloc (128); /* allocate a memory slot of 128 chars */
        fscanf (fileInput, "%127s", lines[i]);//store the data into lines[i]
    }

    fclose(fileInput);//Close the file

    for (i = 0; i < 54; ++i) {//Move the array into the Btree.

        /* Inserting nodes into tree */
        insert(&root, lines[i]);

    }


    //////////Need to sort the B tree

    printf("Inorder Traversal: \n");//Print out current BTree
    printInorder(root);


    //Store data into the Output file.
    FILE *fileOutput = fopen ("output03.txt", "w");//Open the file to write mode
    toOutput(root, fileOutput);//Store to file
    fclose(fileOutput);//Close the file after saving

    /* Deleting all nodes of tree */
    delTree(root);

    return 0;
}


void toOutput(node * tree, FILE *fileOutput)
{

    if (tree)
    {

        fprintf (fileOutput, "%s\n", tree->data);//Save the data to file
        toOutput (tree->left, fileOutput);//recursive call to save left child
        toOutput (tree->right, fileOutput);//recursive call to save right child

    }

}

void insert(node ** tree, char* val)
{
    node *temp = NULL;
    if(!(*tree))//If there is no tree, created a head/parent.
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        *tree = temp;
        return;
    }

    if(val < (*tree)->data)//If tree is already created, add a child to left.
    {
        insert(&(*tree)->left, val);
    }
    else if(val > (*tree)->data)//If tree is already created, add a child to right.
    {
        insert(&(*tree)->right, val);
    }

}

void printPreorder(node *tree)
{
    if (tree)
    {
        printf("%s\n",tree->data);//Process current
        printPreorder(tree->left);//Visit Left sub tree
        printPreorder(tree->right);//Visit Right sub tree.
    }

}

void printInorder(node *tree)
{
    if (tree)
    {
        printInorder(tree->left);//Visit left sub tree
        printf("%s\n",tree->data);//Process current node
        printInorder(tree->right);//Visit right sub tree
    }
}

void printPostorder(node *tree)
{
    if (tree)
    {
        printPostorder(tree->left);//Visit left sub tree
        printPostorder(tree->right);//visit right sub tree
        printf("%s\n",tree->data);//process current node
    }
}

void delTree(node *tree)
{
    if (tree)
    {
        delTree(tree->left);//Delete left
        delTree(tree->right);//Delete right
        free(tree);//Free the tree
    }
}

node* search(node ** tree, char* val)
{
    if(!(*tree))//If there is no tree, then stop
    {
        return NULL;
    }

    if(val < (*tree)->data)
    {
        search(&((*tree)->left), val);//Recursive search left
    }
    else if(val > (*tree)->data)
    {
        search(&((*tree)->right), val);//recursive search right
    }
    else if(val == (*tree)->data)
    {
        return *tree;//If found return it.
    }


}


