#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printError(char *reasonOfError)
{
    printf("Error: %s\n", reasonOfError);
    exit(1);
}

void swapLines(char* str[], int firstInd, int secondInd)
{
    char *temp = str[firstInd];
    str[firstInd] = str[secondInd];
    str[secondInd] = temp;
}

void bubbleSort(char* str[], int amountString)
{
for (int i = amountString-1; i >= 0; i--)
  {
    int hasSwapped = 1;
    for (int j = 0; j<i; j++)
    {
        if (strcmp(str[j], str[j+1]) > 0)
        {
            swapLines(str, j, j+1);
            hasSwapped = 0;
        }
    }
    if (hasSwapped)
    {
        break;
    }
  }
}

void insertionSort(char* str[], int amountString)
{
   int i, j;
   char *key;
   for (i = 1; i < amountString; i++)
   {
       key = str[i];
       j = i-1;
       while (j >= 0 && strcmp(str[j] ,key) >0)
       {
           str[j+1] = str[j];
           j = j-1;
       }
       str[j+1] = key;
   }
}

void merge(char *str[], int left, int mid, int right)
{
    int firstSub, secondSub, finalInd;
    int lenOfLeft = mid - left + 1;
    int lenOfRight = right - mid;

    char **Left = malloc(lenOfLeft*sizeof(char*));
    char **Right = malloc(lenOfRight*sizeof(char*));

    if (Left == NULL || Right == NULL)
    {
        printError("Cannot allocate extra memory for merge sort");
    }

    for (firstSub = 0; firstSub < lenOfLeft; firstSub++)
    {
        Left[firstSub] = str[left + firstSub];
    }

    for (secondSub = 0; secondSub < lenOfRight; secondSub++)
    {
        Right[secondSub] = str[mid + 1+ secondSub];
    }

    firstSub = 0;
    secondSub = 0;
    finalInd = left;

    while (firstSub < lenOfLeft && secondSub < lenOfRight)
    {
        if (strcmp(Left[firstSub], Right[secondSub]) < 0)
        {
            str[finalInd] = Left[firstSub];
            firstSub++;
        }
        else
        {
            str[finalInd] = Right[secondSub];
            secondSub++;
        }
        finalInd++;
    }


    while (firstSub < lenOfLeft)
    {
        str[finalInd] = Left[firstSub];
        firstSub++;
        finalInd++;
    }


    while (secondSub < lenOfRight)
    {
        str[finalInd] = Right[secondSub];
        secondSub++;
        finalInd++;
    }

    free(Right);
    free(Left);
}

void mergeSort(char *str[], int left, int right)
{
    if (left < right)
    {
        int mid = left+(right-left)/2;

        mergeSort(str, left, mid);
        mergeSort(str, mid+1, right);

        merge(str, left, mid, right);
    }
}

int partition(char *str[], int low, int high)
{
    char *pivot = str[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (strcmp(str[j],pivot) < 0)
        {
            i++;
            swapLines(str, i, j);
        }
    }

    swapLines(str, i+1, high);

    return (i + 1);
}

void quickSort(char* str[], int low, int high)
{
    if (low < high)
    {
        int parInd = partition(str, low, high);

        quickSort(str, low, parInd - 1);
        quickSort(str, parInd + 1, high);
    }
}

void heapify(char* str[], int amountString, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < amountString && strcmp(str[left], str[largest]) > 0)
    {
        largest = left;
    }

    if (right < amountString && strcmp(str[right], str[largest]) > 0)
    {
        largest = right;
    }

    if (largest != i)
    {
        swapLines(str, i, largest);
        heapify(str, amountString, largest);
    }
}

void heapSort(char *str[], int amountString)
{
    for (int i = amountString / 2 - 1; i >= 0; i--)
    {
        heapify(str, amountString, i);
    }

    for (int i = amountString - 1; i >= 0; i--)
    {
        swapLines(str, 0, i);
        heapify(str, i, 0);
    }
}

int main(int argc, char *argv[])
{
    int amountString = atoi(argv[1]);
    char *fileName = argv[2];
    char algName = argv[3][0];
    if (argc != 4)
    {
        printError("Invalid number of parameters");
    }

    FILE *myFile;
    if ((myFile = fopen(fileName, "r")) == NULL)
    {
        printError("Cannot open file");
    }

    char **str = malloc(amountString*sizeof(char*));
    if (str == NULL)
    {
        printError("Cannot allocate memory for array of lines");
    }

    for (int numStr=0; numStr<amountString; numStr++){
        int lenOfStr = 1;
        str[numStr] = (char*) malloc(lenOfStr*sizeof(char));
        if (str[numStr] == NULL)
        {
            printError("Cannot allocate memory for line firstly");
        }
        char symbBuff;
        for (int currLenOfCurrStr=0; (symbBuff = fgetc(myFile)) != '\n'; currLenOfCurrStr++){
            if  (symbBuff == EOF && ferror(myFile))
            {
                printError("Error of reading file");
            }
            else if (symbBuff == EOF)
            {
                break;
            }

            if (currLenOfCurrStr+1>=lenOfStr)
            {
                lenOfStr *=2;
                str[numStr] = (char*) realloc(str[numStr], lenOfStr*sizeof(char));
                if (str[numStr] == NULL)
                {
                    printError("Cannot allocate memory for line");
                }
            }
            str[numStr][currLenOfCurrStr] = symbBuff;
            str[numStr][currLenOfCurrStr+1] = '\0';
        }
    }
    fclose(myFile);

    switch (algName)
    {
        case 'b':
            bubbleSort(str, amountString);
            break;
        case 'i':
            insertionSort(str, amountString);
            break;
        case 'm':
            mergeSort(str, 0, amountString-1);
            break;
        case 'q':
            quickSort(str, 0, amountString-1);
            break;
        case 'h':
            heapSort(str, amountString);
            break;
        default:
            printError("Invalid name of algorithm");
    }

    for (int numStr=0; numStr<amountString; numStr++)
    {
        printf("%s\n", str[numStr]);
        free(str[numStr]);
    }

    free(str);
    return 0;
}