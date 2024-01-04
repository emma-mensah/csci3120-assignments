To compile emma-asn3.c, run the command gcc emma-asn3.c -o EMMA-ASN3 -lpthread

This should create an executable file named EMMA-ASN3. 

Proceed by running the command ./EMMA-ASN3

This should run the program by automatically retrieving integers from a file named "IntegerList.txt".
Note: File must be named exactly as IntegerList.txt, else program won't run.

The program creates sorting threads and waits for them to finish.

The program also creates a merging thread and waits for it to finish.

Finally, the sorted array is outputted into a file in the same directory called "SortedIntegerList.txt". Each integer is separated by commas

To view the file's content, run the command nano SortedIntegerList.txt and hit enter. 