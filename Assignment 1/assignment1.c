//Zachary Gill
//COP 3502C Spring 2015
//Section 1
//Assignment 1
//02-08-2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char name[50];
  int id;
  struct node *next;
} *head;

void addNode(char[50], int);
void deleteNode(int);
void loadDataFile();
void insert();
void display();
void deleteId();
void deleteName();

int main()
{
  loadDataFile(); //loads AssignmentOneInput.txt into linked list
  int choice = 0;

  while (1) { //loop forever
    printf("List Operations\n");
    printf("===============\n");
    printf("1 - Insert\n");
    printf("2 - Display\n");
    printf("3 - Delete by ID\n");
    printf("4 - Delete by Name\n");
    printf("5 - Exit\n");
    printf("Enter your choice : ");

    scanf("%d", &choice); //get user input
    switch (choice)
    {
      case 1 : //Insert
        insert();
        break;
      case 2 : //Display
        display();
        break;
      case 3 : //Delete by ID
        deleteId();
        break;
      case 4 : //Delete by Name
        deleteName();
        break;
      case 5 : //Exit
        return 0;
        break;
      default : 
        printf("Invalid input\n");
    } //end switch
  
  } //end loop

  return 0;
}

//adds a new node to the end of the linked list
void addNode(char name[50], int id)
{
  struct node* tmp = (struct node *)head;
  struct node* newNode = (struct node *)malloc(sizeof(struct node)); //new node
  strcpy(newNode->name, name); //name element of new node
  newNode->id = id; //id element of new node
  newNode->next = NULL;

  if (tmp == NULL) { //if head is NULL
    head = newNode;
  }
  else {
    while (tmp->next != NULL)
      tmp = tmp->next; //increment list by one node
    tmp->next = newNode; //link new node
  }
}

//removes a node from the linked list by index
void deleteNode(int index)
{
  struct node *tmp, *prev;
  tmp = (struct node *)head;
  prev = NULL;

  int count = 0;
  while (tmp != NULL) {
    if (count == index) { //test index against desired index
      if (tmp == head) {
        head = tmp->next; //change head to 1st index node
        free(tmp); //free head
        return;
      }
      else {
        prev->next = tmp->next; //close gap created by deleting node
        free(tmp); //free node
        return;
      }
    }
    else {
      prev = tmp;
      tmp = tmp->next; //increment list by one node
      count++; //increase index
    }

  }
}

//initializes the linked list with the data file
void loadDataFile()
{
  char line[50] = { 0 };

  printf("Trying to open file AssignmentOneInput.txt\n\n");

  FILE* f = fopen("AssignmentOneInput.txt", "r"); //open AssignmentOneInput.txt for input
  if (f == NULL) { //test file pointer
    printf("There was an error reading the file\n");
    return;
  }

  while ((fgets(line, 50, f)) != NULL) { //read until eof
    
    char name[50] = { 0 }, idStr[50] = { 0 };
    int id = 0;

    int foundComma = 0;
    for (size_t i = 0; i < strlen(line); i++) { //loop through line char by char
      if (foundComma == 0) {
        if (line[i] == ',') {
          foundComma = i;
          i++;
        }
        else {
          name[i] = line[i]; //add to name
        }
      }
      else {
        idStr[i - foundComma - 2] = line[i]; //add to id
      }
    }
    id = atoi(idStr); //store id as an int

    addNode(name, id); //create new node with name and id
  }

  fclose(f); //close file
}

//inserts a new node to the end of the linked list
void insert()
{
  char name[50] = { 0 };
  int id;

  printf("Enter the name to insert: ");
  scanf(" %[^\n]s", name); //get full line of input
  printf("What is the id number for %s? ", name);
  scanf("%d", &id);

  addNode(name, id); //add new node to list
  printf("Added student %s with id number %d\n\n", name, id);
}

//displays the contents of the linked list
void display()
{
  struct node* tmp = head;

  printf("Element(s) in the list are :\n");
  
  if (tmp == NULL) //if head is NULL
    return;

  do {
    printf("Student %s has id %d\n", tmp->name, tmp->id); //print node elements
    tmp = tmp->next; //progress list by one node
  } while (tmp != NULL);

  printf("\n\n");
}

//deletes a node from the linked list by id
void deleteId()
{
  struct node *tmp = (struct node *)head;
  int id;

  printf("Enter the ID number to delete : ");
  scanf("%d", &id);
  printf("Checking for id %d ...\n", id);

  int count = 0;
  while (tmp != NULL) {
    if (tmp->id == id) { //compare user id to node id
      printf("Found %d!\n", id);
      deleteNode(count); //remove node at index count
      printf("%d deleted successfully\n\n", id);
      return;
    }
    else {
      tmp = tmp->next; //incremement list by one node
      count++; //increase index
    }
  }

  printf("%d could not be found\n\n", id);
}

//deletes a node from the linked list by name
void deleteName()
{
  struct node *tmp = (struct node *)head;
  char name[50] = { 0 };

  printf("Enter the name to delete : ");
  scanf(" %[^\n]s", name); //get full line of input
  printf("Checking for name %s ...\n", name);

  int count = 0;
  while (tmp != NULL) {
    if (strcmp(tmp->name, name) == 0) { //compare user string and node name
      printf("Found %s!\n", name);
      deleteNode(count); //remove node at index count
      printf("%s deleted successfully\n\n", name);
      return;
    }
    else {
      tmp = tmp->next; //incrememnt list by one node
      count++; //increase index
    }
  }

  printf("%s could not be found\n\n", name);
}