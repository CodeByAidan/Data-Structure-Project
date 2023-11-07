#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct digit Digit;

struct digit {
    int Data;
    Digit *Next;
    Digit *Pre;
};

typedef struct results Queue;
typedef struct results QueueResults;
typedef struct results QueueMultiply;
typedef struct results QueueRemainder;

struct results {
    Digit *res;
    QueueResults *Next;
    QueueResults *Pre;
};

////////////////// list
Digit *MakeEmpty(Digit *);
void DisposeList(Digit *);
int IsEmpty(Digit *);
int IsLast(Digit *, Digit *);
Digit *FindLast(Digit *);
void InsertLast(int, Digit *L);
void InsertFirst(int, Digit *);
void DeleteList(Digit *);
void PrintList(Digit *);
int Size(Digit *);
Digit *Duplicate(Digit *);
void PrintListToFile(FILE *, Digit *);
///////////// read
int numberCount();
Digit **readFile();
void DisposeArray(Digit **, int);
void PrintNumbers(Digit **, int);
///////////////////// calculator
void mainMenu();
void AddTwoNumbers(Digit *, Digit *, QueueResults *);
int Compare(Digit *, Digit *);
void MultiplyTwoNumbers(Digit *, Digit *, QueueResults *);
void SubtractTwoNumbers(Digit *, Digit *, QueueResults *);
Digit *Subtract(Digit *, Digit *);
Digit *AddNumbers(Digit *, Digit *);
void DivideTwoNumbers(Digit *, Digit *, QueueResults *, QueueRemainder *);
void RemoveZeros(Digit *);
////////// Queue
Queue *MakeEmptyQueue(Queue *);
void DisposeQueue(Queue *);
int IsEmptyQueue(Queue *);
void Enqueue(Digit *, Queue *);
Digit *Dequeue(Queue *);
void DeleteQueue(Queue *);
int IsLastQueue(Queue *, Queue *);
QueueResults *FindLastQueue(Queue *);
void PrintQueue(QueueResults *, QueueRemainder *);

int main() {
    // Get the number of digits for the input numbers
    int nums = 0;

    // Allocate memory for the input numbers and the results queue
    Digit **numbers = NULL;

    // Make Empty Queue to store the results
    QueueResults *Results = NULL;
    Results = MakeEmptyQueue(Results);

    // Make Empty Queue to store the remainders
    QueueResults *Remainders = NULL;
    Remainders = MakeEmptyQueue(Remainders);

    int x;
    int y;

    while (1) // always ask the user for the choice
    {
        int choice;

        // Display the main menu
        mainMenu();

        printf("What do you want to do: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1:
            if (numbers != NULL) // if it was allocated before free it
                DisposeArray(numbers, nums);

            nums = numberCount();

            // Read the input numbers from file
            printf("Reading numbers......\n");
            numbers = readFile();

            if (numbers != NULL)
                printf("The numbers have been read\n");

            // to check if there is empty number and delete it
            for (int i = 0; i < nums; i++) {
                if (numbers[i]->Next == NULL ||
                    (numbers[i]->Next->Data == 1 &&
                     numbers[i]->Next->Next == NULL)) {
                    for (int j = i; j < nums - 1; j++) {
                        numbers[j] = numbers[j + 1];
                    }
                    nums--; // Decrement the number of elements in the array
                    i--;
                }
                RemoveZeros(numbers[i]);
            }

            if (nums < 2) // Check that there are at least two numbers
            {
                printf("\nThis file must have at least two numbers\n");
                exit(0);
            }
            break;

        case 2:
            // Check that input numbers have been read first
            if (numbers == NULL) {
                printf("\nYou should read the numbers first into input file "
                       "(input.txt) then choose the first option...\n");
                break;
            }

            // Get the indices of the numbers to add
            printf("Which numbers do you want to add (1, 2, ...)?\n");

            // print the numbers to the user to choose
            PrintNumbers(numbers, nums);

            printf("First number: ");
            scanf("%d", &x);

            while (x > nums || x < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("First number: ");
                scanf("%d", &x);
            }
            printf("Second number: ");
            scanf("%d", &y);

            while (y > nums || y < 0) // to check if the second number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Add the numbers and store the result in the results queue
            AddTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL, Remainders);

            break;

        case 3:
            // Check that input numbers have been read first
            if (numbers == NULL) {
                printf("\nYou should read the numbers first...\n");
                break;
            }

            // Get the indices of the numbers to add

            printf("Which numbers do you want to subtract (1, 2, ...)?\n");

            // print the numbers to the user to choose
            PrintNumbers(numbers, nums);

            printf("First number: ");
            scanf("%d", &x);

            while (x > nums || x < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while (y > nums || y < 0) // to check if the second number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("Second number: ");
                scanf("%d", &y);
            }
            // Add the numbers and store the result in the results queue
            SubtractTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL, Remainders);

            break;

        case 4:
            // Check that input numbers have been read first
            if (numbers == NULL) {
                printf("\nYou should read the numbers first...\n");
                break;
            }

            // Get the indices of the numbers to multiply
            printf("Which numbers do you want to multiply (1, 2, ...)?\n");

            // print the numbers to the user to choose
            PrintNumbers(numbers, nums);

            printf("First number: ");
            scanf("%d", &x);

            while (x > nums || x < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while (y > nums || y < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Multiply the numbers and store the result in the results queue
            MultiplyTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL, Remainders);

            break;

        case 5:
            // Check that input numbers have been read first
            if (numbers == NULL) {
                printf("\nYou should read the numbers first...\n");
                break;
            }

            // Get the indices of the numbers to Divide

            printf("Which numbers do you want to Divide (1, 2, ...)?\n");

            // print the numbers to the user to choose
            PrintNumbers(numbers, nums);

            printf("First number: ");
            scanf("%d", &x);

            while (x > nums || x < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while (y > nums || y < 0) // to check if the first number is exists
                                      // if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n", nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Divide the numbers and store the result in the results queue
            DivideTwoNumbers(numbers[--x], numbers[--y], Results, Remainders);

            break;

        case 6:

            // Print the results queue
            PrintQueue(Results, Remainders);

            printf("\nThe results Have been printed to the output file!\n");

            break;

        case 7:

            // Free the memory allocated for the input numbers and the results
            // queue
            if (numbers != NULL) {
                printf("....Disposing Lists\n");
                DisposeArray(numbers, nums);
                DisposeQueue(Results);
            }

            exit(0);

            break;

        default:
            printf("Enter a choice between 1 and 7\n");
        }
    }

    return 0;
}

/*
 * Function: MakeEmpty
 * --------------------
 * Creates a new empty doubly linked list and returns a pointer to it.
 *
 * Returns:
 *      A pointer to the newly created empty linked list.
 */
Digit *MakeEmpty(Digit *L) {
    if (L != NULL)
        DeleteList(L);

    L = (Digit *)malloc(sizeof(Digit));

    if (L == NULL)
        printf("Out Of Memory");

    L->Next = NULL;
    L->Pre = NULL;
    return L;
}

/*
 * Function: IsEmpty
 * -----------------
 * Checks if the given linked list is empty.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 *
 * Returns:
 *      1 if the list is empty, 0 otherwise.
 */
int IsEmpty(Digit *L) {
    return L->Next == NULL; // returns 1 if the list is empty
}

/*
 * Function: IsLast
 * ----------------
 * Checks if the given node in the linked list is the last node.
 *
 * Parameters:
 *      P: Pointer to the node in the linked list.
 *      L: Pointer to the linked list.
 *
 * Returns:
 *      1 if the node is the last node, 0 otherwise.
 */
int IsLast(Digit *P, Digit *L) { return P->Next == NULL; }

/*
 * Function: DeleteList
 * --------------------
 * Frees memory occupied by all nodes in the linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 */
void DeleteList(Digit *L) {
    Digit *P, *temp;

    P = L->Next;
    L->Next = NULL;

    while (P != NULL) {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

/*
 * Function: PrintList
 * -------------------
 * Prints the data of all nodes in the linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 */
void PrintList(Digit *L) {
    Digit *P = L->Next;

    if (IsEmpty(L)) {
        printf("\nThe List Is Empty\n");
    } else {

        if (P->Data == 1) {
            printf("-");
        }

        do {
            P = P->Next;
            printf("%d", P->Data);
        } while (!IsLast(P, L));
    }
}

/*
 * Function: InsertLast
 * --------------------
 * Inserts a new node with data X at the end of the linked list.
 *
 * Parameters:
 *      X: Data to be inserted.
 *      L: Pointer to the linked list.
 */
void InsertLast(int X, Digit *L) {
    Digit *temp;
    temp = (Digit *)malloc(sizeof(Digit));
    temp->Data = X;
    if (!IsEmpty(L)) {
        Digit *P = FindLast(L);

        temp->Next = P->Next;
        P->Next = temp;
        temp->Pre = P;
    } else {
        temp->Pre = L;
        temp->Next = NULL;
        L->Next = temp;
    }
}

/*
 * Function: InsertFirst
 * ---------------------
 * Inserts a new node with data X at the beginning of the linked list.
 *
 * Parameters:
 *      X: Data to be inserted.
 *      L: Pointer to the linked list.
 */
void InsertFirst(int X, Digit *L) {
    Digit *temp;

    temp = (Digit *)malloc(sizeof(Digit));
    temp->Data = X;
    if (!IsEmpty(L)) {
        Digit *SignNode = L->Next;
        if (!IsEmpty(SignNode)) {
            SignNode->Next->Pre = temp;
            temp->Pre = SignNode;
            temp->Next = SignNode->Next;
            SignNode->Next = temp;
        } else {
            temp->Pre = SignNode;
            SignNode->Next = temp;
            temp->Next = NULL;
        }
    } else {

        temp->Pre = L;
        L->Next = temp;
        temp->Next = NULL;
    }
}

/*
 * Function: Size
 * --------------
 * Returns the number of digits in the linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 *
 * Returns:
 *      Number of digits in the linked list.
 */
int Size(Digit *L) {
    int count = 0;
    Digit *P = L;

    while (P->Next != NULL) {
        count++;
        P = P->Next;
    }
    return --count;
}

/*
 * Function: FindLast
 * ------------------
 * Returns the last node in the linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 *
 * Returns:
 *      Pointer to the last node in the linked list.
 */
Digit *FindLast(Digit *L) {

    Digit *P = L;

    while (P->Next != NULL)
        P = P->Next;

    return P;
}

/*
 * Function: DisposeList
 * ---------------------
 * Frees memory occupied by the linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list.
 */
void DisposeList(Digit *L) {
    DeleteList(L);
    free(L);
}

/*
 * Function: numberCount
 * ---------------------
 * Counts the number of lines in the input file, indicating the number of numbers.
 *
 * Returns:
 *      Number of lines (numbers) in the input file.
 */
int numberCount() {
    FILE *fin = fopen("input.txt", "r");
    char ch;
    int lines = 0;
    if (fin == NULL) {
        printf("Failed to open file: \n");
        return 1;
    }
    while ((ch = fgetc(fin)) != EOF) {
        // If we find a newline character, increment the line counter
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(fin);
    return lines;
}

/*
 * Function: readFile
 * ------------------
 * Reads numbers from the input file and stores them in an array of linked lists.
 *
 * Returns:
 *      Array of pointers to the linked lists containing the read numbers.
 */
Digit **readFile() {
    int numcount = numberCount();
    Digit **numbers = (Digit **)malloc(sizeof(Digit *) * numcount);

    for (int i = 0; i < numcount; i++) {
        numbers[i] = MakeEmpty(NULL);
    }

    FILE *fin = fopen("input.txt", "r");
    if (fin == NULL) {
        printf("Failed to open file: \n");
        exit(1);
    }

    char c = fgetc(fin);
    int i = 0, flagNewNum = 1;
    while (c != EOF) {
        if (c == '\n') {
            i++;
            flagNewNum = 1;
        } else {
            if (flagNewNum == 1 && c == '-')
                InsertFirst(1, numbers[i]);
            else if (flagNewNum == 1)
                InsertFirst(0, numbers[i]);

            flagNewNum = 0;
            int dig = c - 48;
            if (dig >= 0 && dig <= 9)
                InsertLast(dig, numbers[i]);
        }
        c = fgetc(fin);
    }
    fclose(fin);

    return numbers;
}

/*
 * Function: PrintNumbers
 * ----------------------
 * Prints the list of digits along with their order numbers.
 *
 * Parameters:
 *      Numbers: Array of pointers to the linked lists containing the numbers.
 *      length: Number of numbers in the array.
 */
void PrintNumbers(Digit **Numbers, int length) {

    for (int i = 0; i < length; i++) {

        printf("number %d): ", i + 1);

        PrintList(Numbers[i]);
        printf("\n");
    }
}

/*
 * Function: Duplicate
 * -------------------
 * Creates a copy of the given linked list and returns a pointer to the new list.
 *
 * Parameters:
 *      L: Pointer to the linked list to be duplicated.
 *
 * Returns:
 *      Pointer to the duplicated linked list.
 */
Digit *Duplicate(Digit *L) {
    Digit *t = NULL, *P;
    P = L;
    t = MakeEmpty(t);

    while (P->Next != NULL) {
        InsertLast(P->Next->Data, t);
        P = P->Next;
    }
    return t;
}

/*
 * Function: DisposeArray
 * ----------------------
 * Frees memory occupied by the array of linked lists.
 *
 * Parameters:
 *      arr: Array of pointers to the linked lists.
 *      length: Number of linked lists in the array.
 */
void DisposeArray(Digit **arr, int length) {

    for (int i = 0; i < length; i++) {

        DisposeList(arr[i]);
    }
    free(arr);
}

/*
 * Function: mainMenu
 * ------------------
 * Prints the main menu options to the console.
 */
void mainMenu() {
    printf("\nChoose from the below operations:\n\n");
    printf("1. Read the numbers from File\n");
    printf("2. Add Numbers\n");
    printf("3. Subtract Numbers\n");
    printf("4. Multiply Numbers\n");
    printf("5. Divide Numbers\n");
    printf("6. print the results to	an output file\n");
    printf("7. Exit\n");
}

/*
 * Function: AddNumbers
 * --------------------
 * Adds two numbers represented by linked lists and enqueues the result.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *      Results: Pointer to the results queue.
 */
Digit *AddNumbers(Digit *FirstNum, Digit *SecondNum) {
    Digit *result = MakeEmpty(NULL);
    InsertFirst(0, result);
    Digit *num1 = FindLast(FirstNum);
    Digit *num2 = FindLast(SecondNum);
    int res;
    int Cin = 0; // carry in

    while (num1 != FirstNum->Next &&
           num2 != SecondNum->Next) // iterates until reaching sign node in
                                    // first number or the second
    {

        res = num1->Data + num2->Data + Cin;
        if (res < 10) {
            InsertFirst(res, result);
            Cin = 0;
        } else {
            res -= 10;
            InsertFirst(res, result);
            Cin = 1;
        }
        num1 = num1->Pre;
        num2 = num2->Pre;
    }

    // if it reach the sign node in the first number but not in the second i it
    // iterates until reaching the sign node in the second number
    while (num1 == FirstNum->Next && num2 != SecondNum->Next) {
        res = num2->Data + Cin;
        if (res < 10) {
            InsertFirst(res, result);
            Cin = 0;
        } else {
            res -= 10;
            InsertFirst(res, result);
            Cin = 1;
        }

        num2 = num2->Pre;
    }
    // if it reach the sign node in the second number but not in the second i it
    // iterates until reaching the sign node in the first number
    while (num1 != FirstNum->Next && num2 == SecondNum->Next) {
        res = num1->Data + Cin;
        if (res < 10) {
            InsertFirst(res, result);
            Cin = 0;
        } else {
            res -= 10;
            InsertFirst(res, result);
            Cin = 1;
        }
        num1 = num1->Pre;
    }

    // if there was carry after finishing the digits just insert it after the
    // sign node
    if (Cin != 0)
        InsertFirst(Cin, result);
    else
        result->Next->Data = 0;

    return result;
}

/*
 * Function: AddTwoNumbers
 * -----------------------
 * Takes two numbers from the user, decides the appropriate operation based on their signs,
 * performs addition, enqueues the result, and prints it.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *      Results: Pointer to the results queue.
 */
void AddTwoNumbers(Digit *FirstNum, Digit *SecondNum, QueueResults *Results) {

    Digit *result = MakeEmpty(NULL);

    if (FirstNum->Next->Data == 0 && SecondNum->Next->Data == 0) {
        result = AddNumbers(FirstNum, SecondNum);
    } else if (FirstNum->Next->Data == 1 && SecondNum->Next->Data == 1) {
        result = AddNumbers(FirstNum, SecondNum);
        result->Next->Data = 1;
    } else if (FirstNum->Next->Data == 0 && SecondNum->Next->Data == 1) {
        if (Compare(FirstNum, SecondNum) > 0)
            result = Subtract(FirstNum, SecondNum);
        else if (Compare(FirstNum, SecondNum) < 0) {
            result = Subtract(SecondNum, FirstNum);
            result->Next->Data = 1;
        } else {
            InsertFirst(0, result);
            InsertFirst(0, result);
        }
    } else {
        if (Compare(FirstNum, SecondNum) > 0) {
            result = Subtract(FirstNum, SecondNum);
            result->Next->Data = 1;
        } else if (Compare(FirstNum, SecondNum) < 0)
            result = Subtract(SecondNum, FirstNum);

        else {
            InsertFirst(0, result);
            InsertFirst(0, result);
        }
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");

    Enqueue(result, Results);
}

/*
 * Function: Compare
 * -----------------
 * Compares two numbers represented by linked lists.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *
 * Returns:
 *      1 if the first number is greater, -1 if the second number is greater, 0 if equal.
 */
int Compare(Digit *FirstNum, Digit *SecondNum) // num1 bigger return 1 , smaller
                                               // return -1 , equal return 0
{
    // we can decide which number is bigger based on number of digits in each
    // already zeros at the beginning were deleted
    if (Size(FirstNum) > Size(SecondNum))
        return 1;

    else if (Size(FirstNum) < Size(SecondNum))
        return -1;

    // if numbers of digits are equal it iterates to compare digit by digit from
    // the most significant digit
    else {
        Digit *num1 = FirstNum->Next->Next;
        Digit *num2 = SecondNum->Next->Next;

        while (num1 != NULL && num2 != NULL) {
            if (num1->Data > num2->Data)
                return 1;

            else if (num1->Data < num2->Data)
                return -1;

            num1 = num1->Next;
            num2 = num2->Next;
        }

        return 0;
    }
}

/*
 * Function: MultiplyNumbers
 * -------------------------
 * Multiplies two numbers represented by linked lists and stores the result in a pointer.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *      result: Pointer to store the result.
 */
void MultiplyNumbers(Digit *FirstNum, Digit *SecondNum, Digit **result) {
    int i = 0;

    Digit *PrevResult = NULL;

    Digit *CurrResult = MakeEmpty(NULL);
    InsertFirst(0, CurrResult);
    InsertFirst(0, CurrResult);

    Digit *num1;
    Digit *num2 = FindLast(SecondNum);

    while (num2 != SecondNum->Next) {
        PrevResult = MakeEmpty(PrevResult);
        InsertFirst(0, PrevResult);

        num1 = FindLast(FirstNum);
        int Cin = 0;
        while (num1 != FirstNum->Next) {

            int noderesult = num1->Data * num2->Data;

            noderesult += Cin;
            Cin = noderesult / 10;
            noderesult %= 10;
            InsertFirst(noderesult, PrevResult);
            num1 = num1->Pre;
        }

        if (Cin != 0)
            InsertFirst(Cin, PrevResult);

        if (i > 0) // adding zeros to the last of the multiplication result
                   // (multiplying by 10 based on the number of the digit)
        {
            for (int z = 0; z < i; z++)
                InsertLast(0, PrevResult);
        }

        CurrResult = AddNumbers(CurrResult, PrevResult);

        i++;

        num2 = num2->Pre;
    }

    *result = Duplicate(CurrResult);

    DisposeList(PrevResult);
    DisposeList(CurrResult);
}

/*
 * Function: MultiplyTwoNumbers
 * ----------------------------
 * Takes two numbers from the user, performs multiplication, enqueues the result,
 * and prints it along with the operation type.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *      Results: Pointer to the results queue.
 */
void MultiplyTwoNumbers(Digit *FirstNum, Digit *SecondNum,
                        QueueResults *Results) {

    Digit *result;

    MultiplyNumbers(FirstNum, SecondNum, &result);

    if (FirstNum->Next->Data == SecondNum->Next->Data) {
        result->Next->Data = 0;
    } else {
        result->Next->Data = 1;
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");

    Enqueue(result, Results);
}

/*
 * Function: Subtract
 * ------------------
 * Subtracts two numbers represented by linked lists (FirstNum - SecondNum) and returns the result.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *
 * Returns:
 *      Pointer to the linked list representing the subtraction result.
 */
Digit *Subtract(Digit *FirstNum, Digit *SecondNum) {

    Digit *num1 = FindLast(FirstNum);
    Digit *num2 = FindLast(SecondNum);

    Digit *result = NULL;
    result = MakeEmpty(result);

    int Borrow = 0;
    int res;
    InsertFirst(0, result);

    while (num1 != FirstNum->Next && num2 != SecondNum->Next) {
        res = num1->Data - num2->Data - Borrow;

        // if the result of the subtraction was negative then here we want a
        // borrow from the next digit
        if (res >= 0) {
            InsertFirst(res, result);
            Borrow = 0;
        } else {
            res += 10;
            InsertFirst(res, result);
            Borrow = 1;
        }
        num1 = num1->Pre;
        num2 = num2->Pre;
    }
    // because the first number in bigger either they have the same number of
    // digits or the first has more
    while (num1 != FirstNum->Next && num2 == SecondNum->Next) {
        res = num1->Data - Borrow;
        if (res >= 0) {
            InsertFirst(res, result);
            Borrow = 0;
        } else {
            res += 10;
            InsertFirst(res, result);
            Borrow = 1;
        }
        num1 = num1->Pre;
    }

    RemoveZeros(result);
    return result;
}

/*
 * Function: SubtractTwoNumbers
 * ---------------------------
 * Takes two numbers from the user, decides the appropriate operation based on their signs,
 * performs subtraction, enqueues the result, and prints it.
 *
 * Parameters:
 *      FirstNum: Pointer to the first number's linked list.
 *      SecondNum: Pointer to the second number's linked list.
 *      Results: Pointer to the results queue.
 */
void SubtractTwoNumbers(Digit *FirstNum, Digit *SecondNum,
                        QueueResults *Results) {
    Digit *result = NULL;
    result = MakeEmpty(result);

    if (FirstNum->Next->Data == 0 && SecondNum->Next->Data == 0) {

        if (Compare(FirstNum, SecondNum) > 0)
            result = Subtract(FirstNum, SecondNum);

        else if (Compare(FirstNum, SecondNum) < 0) {
            result = Subtract(SecondNum, FirstNum);
            result->Next->Data = 1;
        } else {
            InsertFirst(0, result);
            InsertFirst(0, result);
        }
    } else if (FirstNum->Next->Data == 0 && SecondNum->Next->Data == 1) {
        result = AddNumbers(FirstNum, SecondNum);
    } else if (FirstNum->Next->Data == 1 && SecondNum->Next->Data == 0) {
        result = AddNumbers(FirstNum, SecondNum);
        result->Next->Data = 1;
    } else {

        if (Compare(FirstNum, SecondNum) > 0) {
            result = Subtract(FirstNum, SecondNum);
            result->Next->Data = 1;
        } else if (Compare(FirstNum, SecondNum) < 0) {
            result = Subtract(SecondNum, FirstNum);
        } else {
            InsertFirst(0, result);
            InsertFirst(0, result);
        }
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");

    Enqueue(result, Results);
}

/*
 * Function: RemoveZeros
 * ---------------------
 * Removes insignificant zeros from the given number represented by a linked list.
 *
 * Parameters:
 *      L: Pointer to the linked list representing the number.
 */
void RemoveZeros(Digit *L) {

    Digit *current = L->Next->Next;
    Digit *prev = NULL;

    while (current->Data == 0 && current->Next != NULL) {
        prev = current;
        current = current->Next;
        prev->Pre->Next = current;
        current->Pre = prev->Pre;
        free(prev);
    }
}

/*
 * Function: DivideTwoNumbers
 * --------------------------
 * Takes two numbers from the user, performs division, enqueues the quotient and remainder,
 * and prints them along with the operation type.
 *
 * Parameters:
 *      Dividend: Pointer to the first number's linked list.
 *      Divisor: Pointer to the second number's linked list.
 *      Results: Pointer to the results queue.
 *      Remainders: Pointer to the remainders queue.
 */
void DivideTwoNumbers(Digit *Dividend, Digit *Divisor, QueueResults *Results,
                      QueueRemainder *Remainders) {
    // if the divisor was zero so that is error
    if (Divisor->Next->Next->Data == 0) {
        printf("\ndivide by 0... nah\n");
        return;
    }

    Digit *quotient = NULL;
    quotient = MakeEmpty(quotient);
    InsertFirst(0, quotient);

    Digit *divPart = MakeEmpty(NULL);
    InsertFirst(0, divPart);

    Digit *ptrDig = Dividend->Next->Next;

    Digit *test = MakeEmpty(NULL);
    Digit *MulRes = MakeEmpty(NULL);
    Digit *subRes = NULL;

    while (ptrDig != NULL) {
        InsertLast(ptrDig->Data, divPart);
        RemoveZeros(divPart);

        for (int i = 9; i >= 0; i--) {
            test = MakeEmpty(test);
            MulRes = MakeEmpty(MulRes);

            InsertFirst(0, test);
            InsertFirst(i, test);

            if (i == 0) {
                InsertLast(0, quotient);

                continue;
            }

            MultiplyNumbers(Divisor, test, &MulRes);

            if (Compare(MulRes, divPart) > 0) {
                continue;
            }

            InsertLast(i, quotient);
            subRes = MakeEmpty(subRes);
            subRes = Subtract(divPart, MulRes);
            divPart = Duplicate(subRes);

            break;
        }

        ptrDig = ptrDig->Next;
    }

    if (Dividend->Next->Data != Divisor->Next->Data)
        quotient->Next->Data = 1;

    DisposeList(test);
    DisposeList(subRes);
    DisposeList(MulRes);

    RemoveZeros(quotient);
    RemoveZeros(divPart);

    printf("\n");
    printf("The Result = ");
    PrintList(quotient);
    printf("\tThe Remainder = ");
    PrintList(divPart);
    printf("\n");

    Enqueue(divPart, Remainders);
    Enqueue(quotient, Results);
}

/*
 * Function: MakeEmptyQueue
 * ------------------------
 * Creates a new empty queue for storing linked lists and returns a pointer to it.
 *
 * Returns:
 *      A pointer to the newly created empty queue.
 */
Queue *MakeEmptyQueue(Queue *Q) {
    if (Q != NULL)
        DeleteQueue(Q);

    Q = (Queue *)malloc(sizeof(Queue));

    if (Q == NULL)
        printf("Out Of Memory");

    Q->Next = NULL;
    Q->Pre = NULL;
    return Q;
}

/*
 * Function: DisposeQueue
 * ----------------------
 * Disposes the queue and the linked lists stored in it.
 *
 * Parameters:
 *      Q: Pointer to the queue to be disposed.
 */
void DisposeQueue(Queue *Q) {
    DeleteQueue(Q);

    free(Q);
}

/*
 * Function: IsEmptyQueue
 * ----------------------
 * Checks if the given queue is empty.
 *
 * Parameters:
 *      Q: Pointer to the queue.
 *
 * Returns:
 *      1 if the queue is empty, 0 otherwise.
 */
int IsEmptyQueue(Queue *Q) { return Q->Next == NULL; }

/*
 * Function: Enqueue
 * -----------------
 * Enqueues the given linked list into the queue.
 *
 * Parameters:
 *      X: Pointer to the linked list to be enqueued.
 *      Q: Pointer to the queue.
 */
void Enqueue(Digit *X, Queue *Q) {

    Queue *temp;
    temp = (Queue *)malloc(sizeof(Queue));
    temp->res = X;

    if (!IsEmptyQueue(Q)) {
        Queue *P = FindLastQueue(Q);
        temp->Next = P->Next;
        P->Next = temp;
        temp->Pre = P;
    } else {
        temp->Pre = Q;
        temp->Next = NULL;
        Q->Next = temp;
    }
}

/*
 * Function: Dequeue
 * -----------------
 * Dequeues a linked list from the queue and returns a pointer to it.
 *
 * Parameters:
 *      Q: Pointer to the queue.
 *
 * Returns:
 *      Pointer to the dequeued linked list.
 */
Digit *Dequeue(Queue *Q) {
    if (Q->Next == NULL) {
        printf("List is empty");
        exit(0);
    }
    Digit *temp;
    temp = Q->Next->res;

    QueueResults *P = Q->Next;
    if (!IsLastQueue(P, Q)) {
        Q->Next = P->Next;
        P->Next->Pre = Q;
        free(P);
    } else {
        Q->Next = NULL;
        free(P);
    }
    return temp;
}

/*
 * Function: DeleteQueue
 * ---------------------
 * Deletes the queue and the linked lists stored in its nodes.
 *
 * Parameters:
 *      Q: Pointer to the queue.
 */
void DeleteQueue(Queue *Q) {
    QueueResults *P;
    P = Q->Next;

    while (P != NULL) {
        Q->Next = P->Next;
        free(P->res);
        free(P);
        P = Q->Next;
    }
    Q->Next = NULL;
}

/*
 * Function: IsLastQueue
 * ---------------------
 * Checks if the given node in the queue is the last node.
 *
 * Parameters:
 *      P: Pointer to the node in the queue.
 *      Q: Pointer to the queue.
 *
 * Returns:
 *      1 if the node is the last node, 0 otherwise.
 */
int IsLastQueue(Queue *P, Queue *Q) { return P->Next == NULL; }

/*
 * Function: FindLastQueue
 * -----------------------
 * Returns a pointer to the last node in the queue.
 *
 * Parameters:
 *      Q: Pointer to the queue.
 *
 * Returns:
 *      Pointer to the last node in the queue.
 */
Queue *FindLastQueue(Queue *Q) {
    QueueResults *P = Q;

    while (P->Next != NULL)
        P = P->Next;

    return P;
}

/*
 * Function: PrintListToFile
 * -------------------------
 * Prints the linked list to the specified file in an appropriate format.
 *
 * Parameters:
 *      file: Pointer to the file where the linked list is to be printed.
 *      L: Pointer to the linked list to be printed.
 */
void PrintListToFile(FILE *file, Digit *L) {
    Digit *P = L->Next;

    if (IsEmpty(L)) {
        fprintf(file, "\nThe List Is Empty\n");
    } else {
        if (P->Data == 1) {
            fprintf(file, "-");
        }

        do {
            P = P->Next;
            fprintf(file, "%d", P->Data);
        } while (!IsLast(P, L));
    }
}

/*
 * Function: PrintQueue
 * --------------------
 * Prints the linked lists in the queue along with their operation numbers
 * to the "output.txt" file.
 *
 * Parameters:
 *      Results: Pointer to the results queue.
 *      Remainders: Pointer to the remainders queue.
 */
void PrintQueue(QueueResults *Results, QueueRemainder *Remainders) {
    FILE *fout = fopen("output.txt", "w");
    if (fout == NULL) {
        printf("Failed to open file: \n");
        exit(1);
    }

    Digit *rem, *res;
    int counter = 1;

    while (!IsEmptyQueue(Results) && !IsEmptyQueue(Remainders)) {
        fprintf(fout, "operation %d. = ", counter);
        res = Dequeue(Results);

        PrintListToFile(fout, res);

        rem = Dequeue(Remainders);
        if (rem != NULL) {
            fprintf(fout, "\tRemainder  = ");
            PrintListToFile(fout, rem);
        }

        fprintf(fout, "\n");

        counter++;
    }

    fclose(fout);
}