//Zachary Gill
//COP 3502C Spring 2015
//Section 1
//Assignment 2
//03-06-2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct produceItem { //linked list node
  char produce[20];
  char type[20];
  char soldBy[20];
  float price;
  int quantityInStock;
  struct produceItem *next; //ptr to next node
};

void stockProduce(struct produceItem ** head);
void displayProduce(struct produceItem *head);
void reverseProduce(struct produceItem ** head);
void exportProduce(struct produceItem *head);


int main()
{
  struct produceItem *head = (struct produceItem *)malloc(sizeof(struct produceItem)); //head node;
  head = NULL; //initialize head node to NULL

  int choice = 0;

  while (1) { //loop forever
    printf("\n");
    printf("List Operations\n");
    printf("===============\n");
    printf("1. Stock Produce Department\n");
    printf("2. Display Produce Inventory\n");
    printf("3. Reverse Order of Produce Inventory\n");
    printf("4. Export Produce Inventory\n");
    printf("5. Exit Program\n");
    printf("Enter your choice : ");

    scanf("%d", &choice); //get user input
    switch (choice)
    {
      case 1: //Stock
        stockProduce(&head);
        break;
      case 2: //Display
        displayProduce(head);
        break;
      case 3: //Reverse
        reverseProduce(&head);
        break;
      case 4: //Export
        exportProduce(head);
        break;
      case 5: //Exit
        return 0;
        break;
      default:
        printf("Invalid input\n");
    } //end switch

  } //end loop

  return 0;
}

//load the stock from the file
void stockProduce(struct produceItem **head)
{
  char dataline[120];

  printf("Trying to open file AssignmentTwoInput.txt\n");

  FILE *f;
  f = fopen("AssignmentTwoInput.txt", "r"); //open file AssignmentTwoInput.txt for read

  if (f == NULL) { //failed
    printf("Failed to open file AssignmentTwoInput.txt\n");
  }
  else { //success
    printf("Successfully opened file AssignmentTwoInput.txt\n");

    while (fgets(dataline, 120, f) != NULL) { //read until end of file
      struct produceItem *newProduce = (struct produceItem *)malloc(sizeof(struct produceItem)); //new node

      strcpy(newProduce->produce, strtok(dataline, ","));
      strcpy(newProduce->type, strtok(NULL, ","));
      strcpy(newProduce->soldBy, strtok(NULL, ","));

      newProduce->price = (float)atof(strtok(NULL, ","));
      newProduce->quantityInStock = atoi(strtok(NULL, ","));

      newProduce->next = *head; //put at front of the linked list
      *head = newProduce; //redefine new node as head
    }
  }

  fclose(f); //close file

  return;
}

//enumerates the produce inventory to the screen
void displayProduce(struct produceItem *head)
{
  int count = 1;
  struct produceItem *tmp = (struct produceItem*)malloc(sizeof(struct produceItem)); //new node
  tmp = head; //initialize new node to head

  printf("==========================================================================\n");
  printf(" Item #   Produce       Type             Sold By         Price    In Stock\n");
  printf("==========================================================================\n");
  while (tmp != NULL) { //while node exists
    printf("%5d     %-12s %-16s %-14s %6.2f %7d\n", count, (*tmp).produce, (*tmp).type, (*tmp).soldBy, (*tmp).price, (*tmp).quantityInStock); //format output
    tmp = tmp->next; //incremement node
    count++; //incremement count
  }

  return;
}

//reverse the order of the linked list
void reverseProduce(struct produceItem ** head)
{
  struct produceItem *first; //first node
  struct produceItem *rest; //next node

  if (*head == NULL) //if list is empty
    return;
  
  first = *head; //initialize first to head
  rest = first->next; //initialize rest to next
  
  if (rest == NULL)
    return;
  reverseProduce(&rest); //call function on the smaller list
  first->next->next = first; //reverse direction of .next

  first->next = NULL; //empty pointer to next
  
  *head = rest; //reset head to the rest pointer

  return;
}

//prints produce inventory to file
void exportProduce(struct produceItem *head)
{
  int count = 1;
  struct produceItem *tmp = (struct produceItem*)malloc(sizeof(struct produceItem)); //new node
  tmp = head; //initialize new node to head

  printf("Trying to create file AssignmentTwoOutput.txt\n");

  FILE* f;
  f = fopen("AssignmentTwoOutput.txt", "w"); //open AssignmentTwoOutput.txt for write

  if (f == NULL) { //failed
    printf("Failed to write out file AssignmentTwoOutput.txt\n");
  }
  else { //success
    fprintf(f, "==========================================================================\n");
    fprintf(f, " Item #   Produce       Type             Sold By         Price    In Stock\n");
    fprintf(f, "==========================================================================\n");
    while (tmp != NULL) { //while node exists
      fprintf(f, "%5d     %-12s %-16s %-14s %6.2f %7d\n", count, (*tmp).produce, (*tmp).type, (*tmp).soldBy, (*tmp).price, (*tmp).quantityInStock); //format output
      tmp = tmp->next; //increment node
      count++; //increment count
    }

    printf("Successfully wrote out file AssignmentTwoOutput.txt\n");
  }

  fclose(f); //close file

  return;
}