#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
  struct node *next;
}*head;

// Function prototypes
void append(int num);
void add(int num);
void addafter(int num, int loc);
void insert(int num);
int delete(int num);
void display(struct node *r);
int count();

// main function
int  main()
{
  int i, num;
  struct node *n;
  head = NULL;

  while (1)
  {
    printf("\nList Operations\n");
    printf("===============\n");
    printf("1.Insert\n");
    printf("2.Display\n");
    printf("3.Size\n");
    printf("4.Delete\n");
    printf("5.Exit\n");
    printf("Enter your choice : ");

    if (scanf("%d", &i) <= 0)
    {
      printf("Enter only an Integer\n");
      exit(0);
    }
    else
    {

      switch (i)
      {

      case 1:
        printf("Enter the number to insert : ");
        scanf("%d", &num);
        insert(num);
        break;
      case 2:
        if (head == NULL)
        {
          printf("List is Empty\n");
        }
        else
        {
          printf("Element(s) in the list are : ");
        }
        display(n);
        break;
      case 3:
        printf("Size of the list is %d\n", count());
        break;
      case 4:
        if (head == NULL)
          printf("List is Empty\n");
        else
        {
          printf("Enter the number to delete : ");
          scanf("%d", &num);

          if (delete(num))
            printf("%d deleted successfully\n", num);
          else
            printf("%d not found in the list\n", num);
        }
        break;
      case 5:
        return 0;
      default:
        printf("Invalid option\n");
      }
    }
  }

  return 0;
}

// Function definitions
void append(int num)
{
  struct node *temp, *right;
  temp = (struct node *)malloc(sizeof(struct node));
  temp->data = num;
  right = (struct node *)head;

  while (right->next != NULL)
    right = right->next;

  right->next = temp;
  right = temp;
  right->next = NULL;
}

// adding a node to the beginning of the linked list
void add(int num)
{
  struct node *temp;
  temp = (struct node *)malloc(sizeof(struct node));
  temp->data = num;

  // only one node on the linked list
  if (head == NULL)
  {
    head = temp;
    head->next = NULL;
  }
  // at least one node on the linked list, update the next pointer
  // the current first node is being set as the second node
  // the new first node is temp
  // update the beginning of the linked list head and set it equal to temp
  // had head
  // created temp
  // move head to node 2
  // make temp node 1
  // reset the head to the beginning which is currently called temp
  else
  {
    temp->next = head;
    head = temp;
  }
}

void addafter(int num, int loc)
{
  int i;
  struct node *temp, *left, *right;
  // set the node right equal to the head, the beginning
  right = head;
  // looping through the linked list until we find the desired location to insert the node
  for (i = 1; i < loc; i++)
  {
    left = right;
    printf("position of the linked list %d\n\n", left->data);
    right = right->next;
  }

  temp = (struct node *)malloc(sizeof(struct node));
  temp->data = num;
  left->next = temp;
  left = temp;
  left->next = right;

  return;
}

void insert(int num)
{
  int c = 0;
  struct node *temp;
  temp = head;
  if (temp == NULL)
  {
    add(num);
  }
  else
  {
    // traverse the linked list while we don't find the end
    while (temp != NULL)
    {
      // sorting data to be in numeric order
      if (temp->data < num)
        c++;
      // this is where we want to put the data, update the pointer for the next node
      temp = temp->next;
    }

    if (c == 0)
      add(num);
    else if (c < count())
      addafter(num, ++c);
    else
      append(num);
  }
}

int delete(int num)
{
  struct node *temp, *prev;
  temp = head;

  while (temp != NULL)
  {
    if (temp->data == num)
    {
      if (temp == head)
      {
        head = temp->next;
        head = (*temp).next;
        free(temp);
        return 1;
      }
      else
      {
        prev->next = temp->next;
        free(temp);
        return 1;
      }
    }
    else
    {
      prev = temp;
      temp = temp->next;
    }
  }
  return 0;
}

void  display(struct node *r)
{
  r = head;

  if (r == NULL)
  {
    return;
  }

  while (r != NULL)
  {
    printf("%d ", r->data);
    r = r->next;
    if (r == NULL)
    {
      printf("found the end of our linked list!");

    }
  }

  printf("\n");
}

int count()
{
  struct node *n;
  int c = 0;
  n = head;

  while (n != NULL)
  {
    n = n->next;
    c++;
  }

  return c;
}