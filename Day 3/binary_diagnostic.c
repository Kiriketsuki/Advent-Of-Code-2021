#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _listnode
{
    char* string;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, char* item);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);

int length_of_array(char array[][128]);

int main(int argc, char const *argv[]) {
    // read from input
    FILE *fp = fopen("input.txt", "r");
    char line[128];
    char file[1000][128];

    int i = 0;
    while(fgets(line, sizeof(line), fp)) {
        strcpy(file[i], line);
        i++;
    }

    // first 12 digits in line are the values
    int values[12];
    for (int bit_position = 0; bit_position < 12; bit_position++) {
        int number_of_ones = 0;
        for (int j = 0; j < i; j++) {
            int value = file[j][bit_position];
            if (value == '1') {
                number_of_ones++;
            }
        }
        values[bit_position] = number_of_ones;
    }

    // sum up
    int sum = 0;
    int gamma_bits[12];
    int epsi_bits[12];
    for (int j = 0; j < 12; j++) {
        int value = values[j];
        if (value < 500) {
            gamma_bits[j] = 0;
            epsi_bits[j] = 1;
        } else {
            gamma_bits[j] = 1;
            epsi_bits[j] = 0;
        }
    }

    // convert to decimal
    int gamma = 0;
    int epsi = 0;
    for (int j = 0; j < 12; j++) {
        gamma += gamma_bits[j] * pow(2, 11 - j);
        epsi += epsi_bits[j] * pow(2, 11 - j);
    }

    printf("%d\n", gamma * epsi);


    // second part
    // move into linked list
    LinkedList ll;
    ll.size = 0;
    ll.head = NULL;
    for (int j = 0; j < 1000; j++) {
        insertNode(&ll, file[j]);
    }
    LinkedList temp;
    temp.size = 0;
    temp.head = NULL;

    // start main loop
    for (int bit_position = 0; bit_position < 12; bit_position++) {
        int digit_to_check = values[bit_position] >= 500; // 1 if greater than 500, 0 if less than 500
        // loop through linked list, checking if each string's bit at position is equal to digit_to_check
        ListNode *current = ll.head;
        while (current != NULL) {
            int value = current->string[bit_position];
            if (value == digit_to_check + '0') {
                // add to temp
                insertNode(&temp, current->string);
            }
            current = current->next;
        }

        // remove all nodes from ll
        removeAllNodes(&ll);
        // move temp into ll
        ll.head = temp.head;
        ll.size = temp.size;
        temp.head = NULL;
        temp.size = 0;
        free(temp.head);
        if (ll.size == 1) {
            break;
        }
    }

    // convert to decimal
    int result = 0;
    ListNode *current = ll.head;
    for (int i = 0; i < 12; i++) {
        int value = current->string[i] - '0';
        value = value * pow(2, 11 - i);
        result += value;
    }

    printf("%d\n", result);

    // restart 
    removeAllNodes(&ll);
    for (int i = 0; i < 1000; i++) {
        insertNode(&ll, file[i]);
    };

    LinkedList temp2;
    temp2.size = 0;
    temp2.head = NULL;

    for (int bit_position = 0; bit_position < 12; bit_position++) {
        int digit_to_check = values[bit_position] <= 500; // 1 if smaller than 500, 0 if greater than 500
        ListNode *current = ll.head;
        while (current != NULL) {
            char* string = current->string;
            int value = string[bit_position];
            if (value == digit_to_check + '0') {
                insertNode(&temp2, current->string);
            }
            current = current->next;
        }
        removeAllNodes(&ll);
        ll.head = temp2.head;
        ll.size = temp2.size;
        temp2.head = NULL;
        temp2.size = 0;
        if (ll.size == 1 || ll.size == 3) {
            printf("%d\n", bit_position);
            printf("broken\n");
            break;
        }
    }
    printf("%d\n", ll.size);
    printf("%d\n", values[3]);
    // print ll
    current = ll.head;
    while (current != NULL) {
        printf("%s\n", current->string);
        current = current->next;
    }

    // convert to decimal
    result = 0;
    current = ll.head;
    char* string = current->string;
    for (int i = 0; i < 12; i++) {
        int value = string[i] - '0';
        value = value * pow(2, 11 - i);
        result += value;
    }

    printf("%d\n", result);


}

void insertNode(LinkedList *LLPtr, char* item) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);
    newNode->string = item;
    // strcpy(newNode->string, item);
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

