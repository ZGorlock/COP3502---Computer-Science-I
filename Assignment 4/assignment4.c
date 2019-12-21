//Zachary Gill
//COP 3502C Spring 2015
//Section 1
//Assignment 4
//04-19-2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binTreeNode //binary tree structure
{
  int data;
  struct binTreeNode* right;
  struct binTreeNode* left;
};
struct queueNode //queue structure
{
  struct binTreeNode* data;
  struct queueNode* next;
};

void loadFile(struct binTreeNode**);
struct binTreeNode* insert(struct binTreeNode*, struct binTreeNode*);
void printPreOrder(struct binTreeNode*);
void printInOrder(struct binTreeNode*);
void printPostOrder(struct binTreeNode*);
void printBreadthFirst(struct binTreeNode*);
void findNode(struct binTreeNode*);
struct binTreeNode* findNodeHelper(struct binTreeNode*, int);
void minNode(struct binTreeNode*);
struct binTreeNode* minNodeHelper(struct binTreeNode*);
void maxNode(struct binTreeNode*);
struct binTreeNode* maxNodeHelper(struct binTreeNode*);
void averageNodes(struct binTreeNode*);
void medianNode(struct binTreeNode*);
int medianNodeHelper(struct binTreeNode*, int, int*);
void sumNodes(struct binTreeNode*);
int sumNodesHelper(struct binTreeNode*);
void countNodes(struct binTreeNode*);
int countNodesHelper(struct binTreeNode*);
void deleteNode(struct binTreeNode**);
struct binTreeNode* deleteNodeHelper(struct binTreeNode*, int);
struct binTreeNode* parent(struct binTreeNode*, struct binTreeNode*);
int isLeaf(struct binTreeNode*);
int hasOnlyLeftChild(struct binTreeNode*);
int hasOnlyRightChild(struct binTreeNode*);

int main()
{
  struct binTreeNode* root = (struct binTreeNode*)malloc(sizeof(struct binTreeNode)); //allocate space for root node
  root = NULL; //set root to null

  while (1) { //loop forever
    int choice = 0;

    printf("What would you like to do?\n");
    printf("1.  Generate Binary Search Tree\n");
    printf("2.  Print the BST in pre-order format\n");
    printf("3.  Print the BST in in-order format\n");
    printf("4.  Print the BST in post-order format\n");
    printf("5.  Print the BST in breadth-first format\n");
    printf("6.  Find a value in the BST\n");
    printf("7.  Find the minimum value in the BST nodes\n");
    printf("8.  Find the maximum value in the BST nodes\n");
    printf("9.  Calculate the average value of the BST nodes\n");
    printf("10. Find the median value of the BST nodes\n");
    printf("11. Calculate the sum of the BST nodes\n");
    printf("12. Count the number of BST nodes\n");
    printf("13. Delete a value in the BST\n");
    printf("14. Exit Program\n:");

    scanf("%d", &choice); //get user input

    switch (choice) //conditional over user input
    {
      case 1: //Generate Binary Search Tree
        loadFile(&root);
        break;
      case 2: //Print the BST in pre-order format
        printPreOrder(root);
        printf("\n");
        break;
      case 3: //Print the BST in in-order format
        printInOrder(root);
        printf("\n");
        break;
      case 4: //Print the BST in post-order format
        printPostOrder(root);
        printf("\n");
        break;
      case 5: //Print the BST in breadth-first format
        printBreadthFirst(root);
        break;
      case 6: //Find a value in the BST
        findNode(root);
        break;
      case 7: //Find the minimum value in the BST nodes
        minNode(root);
        break;
      case 8: //Find the maximum value in the BST nodes
        maxNode(root);
        break;
      case 9: //Calculate the average value of the BST nodes
        averageNodes(root);
        break;
      case 10: //Find the median value of the BST nodes
        medianNode(root);
        break;
      case 11: //Calculate the sum of the BST nodes
        sumNodes(root);
        break;
      case 12: //Count the number of BST nodes
        countNodes(root);
        break;
      case 13: //Delete a value in the BST
        deleteNode(&root);
        break;
      case 14: //Exit Program
        return 0;
        break;
    }
    printf("\n");
  }

  return 0;
}

//reads data from AssignmentFourInput.txt into binary tree
void loadFile(struct binTreeNode** root)
{
  FILE* f;
  f = fopen("AssignmentFourInput.txt", "r"); //open AssignmentFourInput.txt for read

  int data = 0;
  while (!feof(f)) { //while there is still data
    if (fscanf(f, "%d", &data)) { //scan it in
      struct binTreeNode* newNode = (struct binTreeNode*)malloc(sizeof(struct binTreeNode)); //allocate memory for a new node
      newNode->data = data;
      newNode->left = NULL;
      newNode->right = NULL;
      *root = insert(*root, newNode); //insert the new node into the tree
    }
  }

  fclose(f); //close the file
}

//inserts a node into the binary search tree
struct binTreeNode* insert(struct binTreeNode* root, struct binTreeNode* element)
{
  if (root == NULL) { //if the "root" is empty
    return element; //put the element in that location
  }
  else {
    if (element->data > root->data) //if new data is larger than root data
      root->right = insert(root->right, element); //move right
    else
      root->left = insert(root->left, element); //otherwise move left
    return root;
  }
}

//prints the nodes of the binary tree in pre-order
void printPreOrder(struct binTreeNode* root)
{
  if (root != NULL) {
    printf("%d ", root->data); //print the root first
    printPreOrder(root->left); //recursively call its left subtree
    printPreOrder(root->right); //recursively call its right subtree
  }
}

//prints the nodes of the binary tree in in-order
void printInOrder(struct binTreeNode* root)
{
  if (root != NULL) {
    printInOrder(root->left); //recursively call its left subtree
    printf("%d ", root->data); //print the root in the middle
    printInOrder(root->right); //recursively call its right subtree
  }
}

//prints the nodes of the binary tree in post-order
void printPostOrder(struct binTreeNode* root)
{
  if (root != NULL) {
    printPostOrder(root->left); //recursively call its left subtree
    printPostOrder(root->right); //recursively call its right subtree
    printf("%d ", root->data); //print the root last
  }
}

//prints the nodes of the binary tree in breadth-first order
void printBreadthFirst(struct binTreeNode* root)
{
  struct queueNode* head = (struct queueNode*)malloc(sizeof(struct queueNode)); //allocate space for head of queue
  struct queueNode* traverse = (struct queueNode*)malloc(sizeof(struct queueNode)); //allocate space for traverser of queue
  head->data = root; //put root in queue
  head->next = NULL;
  traverse = NULL;

  while (head != NULL) { //while there is an element in the queue
    printf("%d ", head->data->data); //print the data of the tree node in the queue

    if (head->data->left != NULL) { //if the queued node has a left node
      traverse = head;
      while (traverse->next != NULL) //move through queue to find end
        traverse = traverse->next;
      struct queueNode* newNode = (struct queueNode*)malloc(sizeof(struct queueNode)); //allocate new memory for a queue node
      newNode->data = head->data->left;
      newNode->next = NULL;
      traverse->next = newNode; //put new node in the queue
    }
    if (head->data->right != NULL) { //if the queued node has a right node
      traverse = head;
      while (traverse->next != NULL) //move through queue to find end
        traverse = traverse->next;
      struct queueNode* newNode = (struct queueNode*)malloc(sizeof(struct queueNode)); //allocate new memory for a queue node
      newNode->data = head->data->right;
      newNode->next = NULL;
      traverse->next = newNode; //put new node in the queue
    }

    head = head->next; //move the head of the queue over
  }

  printf("\n");
}

//determines if the user value exists as a node in the binary tree
void findNode(struct binTreeNode* root)
{
  int value = 0;
  printf("Enter a value to search for: ");
  scanf("%d", &value); //get user input

  if (findNodeHelper(root, value) == NULL) //if it was not found
    printf("The value %d does not exist as a node in the binary search tree.\n", value);
  else
    printf("The value %d exists as a node in the binary search tree.\n", value);
}
struct binTreeNode* findNodeHelper(struct binTreeNode* root, int value)
{
  while (root != NULL) { //while the "root" exists
    if (root->data == value) //if its value is the search value
      return root; //return it
    else if (value < root->data) //if the search value is less than the node value
      return findNodeHelper(root->left, value); //move left
    else
      return findNodeHelper(root->right, value); //otherwise move right
  }
  return NULL;
}

//displays the minimum node in the binary tree
void minNode(struct binTreeNode* root)
{
  struct binTreeNode* min = (struct binTreeNode*)malloc(sizeof(struct binTreeNode)); //allocate memory for new node
  min = minNodeHelper(root); //get minimum node

  if (min == NULL) //if the tree is empty
    printf("The binary search tree is empty.\n");
  else
    printf("The minimum node is %d.\n", min->data);
}
struct binTreeNode* minNodeHelper(struct binTreeNode* root)
{
  while (root->left != NULL) //while you can move left
    root = root->left; //do so
  return root;
}

//displays the maximum node in the binary tree
void maxNode(struct binTreeNode* root)
{
  struct binTreeNode* max = (struct binTreeNode*)malloc(sizeof(struct binTreeNode)); //allocate memory for a new node
  max = maxNodeHelper(root); //get the maximum node
  
  if (max == NULL) //if the tree is empty
    printf("The binary search tree is empty.\n");
  else
    printf("The maximum node is %d.\n", max->data);
}
struct binTreeNode* maxNodeHelper(struct binTreeNode* root)
{
  while (root->right != NULL) //while you can move right
    root = root->right; //do so
  return root;
}

//calculates the average of the nodes in the binary tree
void averageNodes(struct binTreeNode* root)
{
  printf("The average of the nodes in the tree is %f.\n", (double)sumNodesHelper(root) / countNodesHelper(root)); //sum / num = average
}

//calculates the median node in the binary tree
void medianNode(struct binTreeNode* root)
{
  int count = 0;
  double median = 0.0;
  int target = countNodesHelper(root); //get number of nodes in tree
  
  if (target % 2 == 1) { //if there is an odd number of nodes
    median = medianNodeHelper(root, target / 2 + 1, &count); //get the middle node
  }
  else { //if there is an even number of nodes
    median = medianNodeHelper(root, target / 2, &count); //get first middle node
    count = 0;
    median += medianNodeHelper(root, target / 2 + 1, &count); //get second middle node
    median /= 2; //average them
  }

  printf("The median node in the tree is %f.\n", median);
}
int medianNodeHelper(struct binTreeNode* root, int target, int* count)
{
  int tmp = 0;
  if (root != NULL) {
    tmp = medianNodeHelper(root->left, target, count); //see if you reach the median by going left
    if (tmp != 0)
      return tmp;

    (*count)++; //increment number of nodes visited (in-order)
    if ((*count) == target) //if you have reached the taget
      return root->data; //return the node you are on

    tmp = medianNodeHelper(root->right, target, count); //see if you reach the median by going right
    if (tmp != 0)
      return tmp;
  }

  return 0;
}

//sums the nodes in the binary tree
void sumNodes(struct binTreeNode* root)
{
  printf("The sum of the nodes in the binary tree is %d.\n", sumNodesHelper(root));
}
int sumNodesHelper(struct binTreeNode* root)
{
  if (root != NULL) //if node exists
    return root->data + sumNodesHelper(root->left) + sumNodesHelper(root->right); //return node value + sum of left nodes + sum of right nodes
  return 0;
}

//counts the number of nodes in the binary tree
void countNodes(struct binTreeNode* root)
{
  printf("The number of nodes in the binary tree is %d.\n", countNodesHelper(root));
}
int countNodesHelper(struct binTreeNode* root)
{
  if (root != NULL) //if node exists
    return 1 + countNodesHelper(root->left) + countNodesHelper(root->right); //return 1 + number of nodes to the left + number of nodes to the right
  return 0;
}

//deletes the user value from the binary tree if it exists
void deleteNode(struct binTreeNode** root)
{
  int value = 0;
  printf("Enter a value to delete: ");
  scanf("%d", &value); //get user input

  if (findNodeHelper(*root, value) == NULL) { //if node does not exist
    printf("The value %d does not exist as a node in the binary search tree.\n", value);
  }
  else {
    *root = deleteNodeHelper(*root, value); //delete node and update root
    printf("The value %d was deleted in the binary search tree.\n", value);
  }
}
struct binTreeNode* deleteNodeHelper(struct binTreeNode* root, int value)
{
  struct binTreeNode *delnode, *new_del_node, *save_node;
  struct binTreeNode *par;
  int save_val;

  delnode = findNodeHelper(root, value); //find the node you want to delete and store ptr in delnode
  par = parent(root, delnode); //get parent of delnode

  if (isLeaf(delnode)) { //if the node is a leaf
    if (par == NULL) { //if it is the only node in the tree
      free(root); //free the tree
      return NULL;
    }
    if (value < par->data) { //if it is the left node of its parent
      free(par->left); //free it
      par->left = NULL; //set parent's left pointer to NULL
    }
    else {
      free(par->right); //otherwise free node
      par->right = NULL; //set right pointer of parent to NULL
    }
    return root;
  }

  if (hasOnlyLeftChild(delnode)) { //only left child node
    if (par == NULL) { //if it is the root node
      save_node = delnode->left; //its left child is saved
      free(delnode); //the node is freed
      return save_node; //the new root is the saved child
    }
    if (value < par->data) { //if the value is less than the parent node
      save_node = par->left; //save the left child
      par->left = par->left->left; //the parents new left child is the left grandchild
      free(save_node); //free the left child
    }
    else {
      save_node = par->right; //save the right child
      par->right = par->right->left; //the right child is now the right's left child
      free(save_node); //free the right child
    }
    return root;
  }

  if (hasOnlyRightChild(delnode)) { //if it only has a right child
    if (par == NULL) { //if it is the root nodde
      save_node = delnode->right; //save the right child
      free(delnode); //free it
      return save_node; //the new root is the right child
    }
    if (value < par->data) { //if the value is less than the parent node
      save_node = par->left; //save the left child
      par->left = par->left->right; //the new left child is the left's right child
      free(save_node); //free the left child
    }
    else {
      save_node = par->right; //save the right child
      par->right = par->right->right; //new right is the right child's right
      free(save_node); //free the right child
    }
    return root;
  }

  //if it has two children
  new_del_node = minNodeHelper(delnode->right); //find the minimum node to the right of the node to be deleted
  save_val = new_del_node->data; //save the value of the minimum node
  deleteNodeHelper(root, save_val); //delete the minimum node
  delnode->data = save_val; //replace the value of the old node to be deleted with the minimum value

  return root;
}

//returns the parent node of a node
struct binTreeNode* parent(struct binTreeNode* root, struct binTreeNode* node)
{
  if (root == NULL || root == node) //if root is NULL or the node is the root
    return NULL;
  
  if (root->left == node || root->right == node) //if the roots left or right node is the node
    return root; //we found the parent

  if (node->data < root->data) //if the node is less than the root
    return parent(root->left, node); //move left
  else
    return parent(root->right, node); //otherwise move right

  return NULL;
}

//returns if a node is a lead or not
int isLeaf(struct binTreeNode* node)
{
  return (node->left == NULL && node->right == NULL); //return if the left child is NULL and the right child is NULL
}

//returns if a node has only a left child or not
int hasOnlyLeftChild(struct binTreeNode* node)
{
  return (node->left != NULL && node->right == NULL); //return if the left child is not NULL ad the right child is NULL
}

//returns if a node has only a right child or not
int hasOnlyRightChild(struct binTreeNode* node)
{
  return (node->left == NULL && node->right != NULL); //return if the left child is NULL and the right child is not NULL
}