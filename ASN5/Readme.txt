To compile emma-asn5.c, run the command gcc emma-asn5.c -o EMMA-ASN5 -lpthread -lrt

This should create an executable file named EMMA-ASN5. 

Proceed by running the command ./EMMA-ASN3 x y z where x is the sleep time, y is the number of producers and z is the number of consumers.

This should run the program by automatically displaying the contents onto the screen.

The program retrieves arguments x, y and z. It initialises semaphores 'empty' and 'full' as well as the mutex lock.

Buffer is initialised after which producer and consumer threads are created.

Finally, the program will sleep and terminate. 