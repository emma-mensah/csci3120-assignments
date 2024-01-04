/**
 * Author: Emma Mensah
 * Code skeleton adapted from assignment description.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/* Declaring global variables*/
int num, count = 0, p1 = 0, p2 = 0;
int integerList[500];
int sublist1[500], sublist2[500];
int final_sortedArray[500];
pthread_t sort1, sort2, merge;

/* Created a compare function to use in qsort function*/
int compareInt (const void *p0, const void *q0 ){
    int p = *(int *)p0;
    int q = *(int *)q0;

    int value = (p - q);
    return value;
}
/* Define strcut for parameters for merge and sort functions*/
struct parameters
{
    unsigned int length ;
    int intArray[];
};

/* qsort() function from GNU C library used to sort integers*/
void* sorter(void *params) {
    struct parameters param1;

    /**
     * Split IntegerList array into two arrays.
     * If length of IntegerList is even, split equally, else if odd,
     * add the middle number to the first sub array and the remainder in the second array
    */
   int mid;
    if (count%2 == 0)
    {
        mid = count/2;
            for(int i = 0; i < count; i++)  
            {  
                if(i < mid)  {
                    sublist1[p1] = integerList[i];  
                    p1++;
                }
                else {
                    sublist2[p2] = integerList[i];
                    p2++;  
                }
            } 
        qsort(sublist1,mid, sizeof(int), compareInt);
        qsort(sublist2, mid,sizeof(int), compareInt);
    }
    else
    {
        mid = (count+1)/2;
            for(int i = 0; i < count; i++)  
            {  
                if(i < mid)  {
                    sublist1[p1] = integerList[i];  
                    p1++;
                }
                else {
                    sublist2[p2] = integerList[i];
                    p2++;  
                }
            }
        qsort(sublist1, mid, sizeof(int), compareInt);
        qsort(sublist2, (count-mid), sizeof(int), compareInt);
    }
    return NULL;
}

void* merger(void *params) {
    /*merging algorithm implementation using pseudocode provided in assignment description*/
    int x = 0, y = 0, z = 0;
    while (x < p1 && y < p2)
    {
        if (sublist1[x] < sublist2[y])
        {
            final_sortedArray[z] = sublist1[x];
            z++;
            x++;
        }
        else {
            final_sortedArray[z] = sublist2[y];
            z++;
            y++;
        } 
    }

    while (x < p1)
    {
        final_sortedArray[z] = sublist1[x];
            z++;
            x++;
    }

    while (y < p2)
    {
        final_sortedArray[z] = sublist2[y];
            z++;
            y++;
    }

    return NULL;
}

int main (int argc, const char * argv[]) {
    FILE *outputPtr, *inputPtr;    //creates a pointer to the file

    inputPtr = fopen("IntegerList.txt", "r");   //reads from this file.
    outputPtr = fopen("SortedIntegerList.txt","w"); //writes to this file if it exists, otherwise it creates one.

    int index = 0;

    if (inputPtr == NULL) {
        printf("Error opening file");
    }
    else {
        while((fscanf(inputPtr,"%d%*c",&num)) == 1){
            integerList[index]= num;
            index++;
            count++;
        }
        fclose(inputPtr);
    }

    /*create the first sorting thread*/
    pthread_create(&sort1, NULL, sorter, NULL);

    /*create the second sorting thread*/
    // pthread_create(&sort2, NULL, sorter, NULL);

    /*now wait for the 2 sorting threads to finish*/
    pthread_join(sort1, NULL);
    // pthread_join(sort2, NULL);

    /*create merge thread*/
    pthread_create(&merge, NULL, merger, NULL);

    /*wait for the merge thread to finish*/ 
    pthread_join(merge, NULL);

    /*ouput the sorted array*/
    for(int a = 0; a< p1+p2; a++) {
        fprintf(outputPtr, "%d,", final_sortedArray[a]);
    }
    
    return 0;
}
