/**
 * Author: Emma Mensah
 * Code skeleton adapted from assignment description.
 * References: 
 * https://www.geeksforgeeks.org/producer-consumer-problem-using-semaphores-set-1/
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 5 
typedef int buffer_item; 
buffer_item buffer[BUFFER_SIZE];

//declaring variables
int produced = 0, consumed = 0;
int in = 0, out = 0;
pthread_mutex_t mutex;
sem_t full;
sem_t empty;

void insert() {
    buffer[in] = produced;
    printf("Producer X inserted item %d into buffer[%d]\n", produced, in);
    in = (in + 1) % BUFFER_SIZE;
    
}

void removed() {
    if  (buffer[out] == -1) {

    }
    consumed = buffer[out];
    printf("Consumer Y consumed item %d from buffer[%d]\n", consumed, out);
    buffer[out] = -1;
    out = (out + 1) % BUFFER_SIZE;

    
}

void *producer(void *param) { 
    while (1) {
        sleep(rand() % 5);      
        
        produced = rand();      //generate a random number

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        insert();       //insert an item

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    } 
}

void *consumer(void *param) { 
    while (1) {
        
        sleep(rand() % 5);      //sleep for a random period of time: 0-4 seconds

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        removed();      //remove an item 

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    } 
}


int main(int argc, char *argv[]) {
    /* Get command-line arguments argv[1],argv[2],argv[3] */
    int sleepTime = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);
    
    /* Initialize semaphores and mutex lock */
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    /* Initialize buffer */
    for(int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1; 
    }

    /* Create producer thread(s) */
    pthread_t th_producer[num_producers];

    for(int i = 0; i < num_producers; i++) {
        pthread_create(&th_producer[i], NULL, &producer, NULL);
    }

    /* Create consumer thread(s) */
    pthread_t th_consumer[num_consumers];

    for(int i = 0; i < num_consumers; i++) {
        pthread_create(&th_consumer[i], NULL, &consumer, NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    // Sleep and thereafter terminate the C program 
    sleep(sleepTime);
    return(0);
}