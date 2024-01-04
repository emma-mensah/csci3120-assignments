#include <stdio.h>
#include <string.h>

int main()
{ 
    FILE *outputPtr;    //creates a pointer to the file

    outputPtr = fopen("Output.txt","w"); //writes to this file if it exists, otherwise it creates one.

    char sentence[100]; 
    
    printf("Please Enter Your Sentence: "); //prompt user to input sentence
    
    scanf("%[^\n]s", sentence); //reads in user input until end of line

    char * splitWords = strtok(sentence, " ");   //split words with space delimiter 
    
    while (splitWords != NULL) {
        printf("%s\n", splitWords);
        fprintf(outputPtr, "%s\n", splitWords); //write each word to the text file
        splitWords = strtok(NULL," ");      
    }

    fclose(outputPtr);
    return 0;
}
