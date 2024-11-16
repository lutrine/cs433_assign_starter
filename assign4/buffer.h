/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.h
 * @author Caden Jamason, Adrian Reyes
 * @brief header file for the buffer class
 * @version 0.1
 */

#ifndef ASSIGN4_BUFFER_H
#define ASSIGN4_BUFFER_H

#include <pthread.h>
#include <semaphore.h>

// Define the data type of the buffer items
typedef int buffer_item;
#define BUFFER_SIZE 5

/**
 * @brief The bounded buffer class. The number of items in the buffer cannot
 * exceed the size of the buffer.
 */
class Buffer {
private:
  buffer_item buffer[BUFFER_SIZE]; // The buffer
  int size;                        // Size of the buffer
  int count;                       // Number of items in the buffer
  int in;                          // Index for inserting items
  int out;                         // Index for removing items

public:
  /**
   * @brief Construct a new Buffer object
   * @param size the size of the buffer
   */
  Buffer(int size = BUFFER_SIZE);

  /**
   * @brief Destroy the Buffer object
   */
  ~Buffer();

  /**
   * @brief Insert an item into the buffer
   * @param item the item to insert
   * @return `true` if successful, else `false`
   */
  bool insert_item(buffer_item item);

  /**
   * @brief Remove an item from the buffer
   * @param item the item to remove
   * @return `true` if successful, else `false`
   */
  bool remove_item(buffer_item *item);

  /**
   * @brief Get the size of the buffer
   * @return the size of the buffer
   */
  int get_size();

  /**
   * @brief Get the number of items in the buffer
   * @return the number of items in the buffer
   */
  int get_count();

  /**
   * @brief Check if the buffer is empty
   * @return `true` if the buffer is empty, else `false`
   */
  bool is_empty();

  /**
   * @brief Check if the buffer is full
   * @return `true` if the buffer is full, else `false`
   */
  bool is_full();

  /**
   * @brief Print the buffer
   */
  void print_buffer();
};

#endif // ASSIGN4_BUFFER_H
