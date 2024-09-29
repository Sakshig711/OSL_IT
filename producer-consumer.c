#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // For sleep()

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 2
#define CONSUMER_COUNT 2

// Shared buffer and indices
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

// Semaphores and mutex
sem_t full;
sem_t empty;
pthread_mutex_t mutex;

// Producer and consumer IDs
int producer_ids[PRODUCER_COUNT] = {1, 2}; 
int consumer_ids[CONSUMER_COUNT] = {1, 2}; 

// Function to simulate producing an item
int produce_item(int producer_id) {
    return producer_id * 100 + rand() % 100; 
}

// Function to simulate consuming an item
void consume_item(int item, int consumer_id) {
    printf("Consumer %d consumed item: %d\n", consumer_id, item);
}

// Producer function
void* producer(void* arg) {
    int id = *(int*)arg; // Producer ID

    while (1) {
        int item = produce_item(id); // Produce an item

        sem_wait(&empty);   // Decrement the count of empty slots
        pthread_mutex_lock(&mutex);   // Enter critical section

        // Add item to buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE; // Update index

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&full);    // Increment the count of full slots

        printf("Producer %d produced item: %d\n", id, item);
        sleep(1); // Simulate time taken to produce an item
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int id = *(int*)arg; // Consumer ID

    while (1) {
        sem_wait(&full);    // Decrement the count of full slots
        pthread_mutex_lock(&mutex);   // Enter critical section

        // Remove item from buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE; // Update index

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&empty);   // Increment the count of empty slots

        consume_item(item, id); // Consume the item
        sleep(1); // Simulate time taken to consume an item
    }
    return NULL;
}

int main() {
    pthread_t producers[PRODUCER_COUNT];
    pthread_t consumers[CONSUMER_COUNT];
    int producer_ids[PRODUCER_COUNT] = {1, 2};
    int consumer_ids[CONSUMER_COUNT] = {1, 2};

    // Initialize semaphores and mutex
    sem_init(&full, 0, 0);        // No items in the buffer initially
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer is initially empty
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    // Join producer threads (this example will run indefinitely)
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }

    // Join consumer threads (this example will run indefinitely)
    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Cleanup (not reached in this example but good practice)
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);

    return 0;
}

