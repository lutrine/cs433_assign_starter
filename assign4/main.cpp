/**
 * Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Caden Jamason, Adrian Reyes
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */

#include "buffer.h"
#include <iostream>
#include <unistd.h>

using namespace std;

// global buffer object
Buffer buffer(BUFFER_SIZE);
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// Producer thread function
void *producer(void *param) {
  // Each producer insert its own ID into the buffer
  // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
  buffer_item item = *((int *)param);

  while (true) {
    usleep(rand() % 1000000); // Sleep for a random period of time

    sem_wait(&empty); // Wait for an empty slot
    pthread_mutex_lock(&mutex);

    if (buffer.insert_item(item)) {
      cout << "Producer " << item << ": Inserted item " << item << endl;
      buffer.print_buffer();
    } else {
      cout << "Producer error condition" << endl; // shouldn't come here
    }

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
}

// Consumer thread function
void *consumer(void *param) {
  buffer_item item;

  while (true) {
    usleep(rand() % 1000000); // Sleep for a random period of time

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    if (buffer.remove_item(&item)) {
      cout << "Consumer " << item << ": Removed item " << item << endl;
      buffer.print_buffer();
    } else {
      cout << "Consumer error condition" << endl; // shouldn't come here
    }

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}

int main(int argc, char *argv[]) {
  /* 1. Get command line arguments argv[1],argv[2],argv[3] */

  // If the command is used wrong, display its usage and terminate the program
  if (argc != 4) {
    cerr << "Usage: " << argv[0]
         << " <sleep_time> <num_producers> <num_consumers>" << endl;
    exit(EXIT_FAILURE);
  }

  // Associate each argument with a variable
  int sleep_time = atoi(argv[1]);
  int num_producers = atoi(argv[2]);
  int num_consumers = atoi(argv[3]);

  /* 2. Initialize buffer and synchronization primitives */

  // Initialize mutex and semaphores
  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, buffer.get_size());
  sem_init(&full, 0, 0);

  /* 3. Create producer thread(s) */

  // Create producer threads and associated IDs
  pthread_t *producers = new pthread_t[num_producers];
  int *producer_ids = new int[num_producers];
  for (int i = 0; i < num_producers; ++i) {
    producer_ids[i] = i + 1;
    pthread_create(&producers[i], NULL, producer, (void *)&producer_ids[i]);
  }

  /* 4. Create consumer thread(s) */

  // Create consumer threads and associated IDs
  pthread_t *consumers = new pthread_t[num_consumers];
  int *consumer_ids = new int[num_consumers];
  for (int i = 0; i < num_consumers; ++i) {
    consumer_ids[i] = i + 1;
    pthread_create(&consumers[i], NULL, consumer, (void *)&consumer_ids[i]);
  }

  /* 5. Main thread sleep */

  sleep(sleep_time);

  /* 6. Exit */

  // Cancel all threads
  for (int i = 0; i < num_producers; i++) {
    pthread_cancel(producers[i]);
  }
  for (int i = 0; i < num_consumers; i++) {
    pthread_cancel(consumers[i]);
  }

  // Join threads back together
  for (int i = 0; i < num_producers; ++i) {
    pthread_join(producers[i], NULL);
  }
  for (int i = 0; i < num_consumers; ++i) {
    pthread_join(consumers[i], NULL);
  }

  // Delete dynamically allocated memory
  delete[] producers;
  delete[] consumers;
  delete[] producer_ids;
  delete[] consumer_ids;

  return 0;
}
