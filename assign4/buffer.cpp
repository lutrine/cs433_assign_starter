/**
 * Assignment 4: Producer Consumer Problem
 * @file buffer.cpp
 * @author Caden Jamason, Adrian Reyes
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

#include "buffer.h"
#include <iostream>

Buffer::Buffer(int size) : size(BUFFER_SIZE), count(0), in(0), out(0) {
  // Initialize all buffer elements to 0
  for (int i = 0; i < size; i++) {
    buffer[i] = 0;
  }
}

Buffer::~Buffer() {} // Destructor

bool Buffer::insert_item(buffer_item item) {
  // Return false if buffer is full
  if (is_full()) {
    return false;
  }

  // Buffer is not full, so insert item
  buffer[in] = item;    // Insert item into buffer
  in = (in + 1) % size; // Increment in index and wrap if necessary
  count++;              // Increment count

  return true;
}

bool Buffer::remove_item(buffer_item *item) {
  // Return false if buffer is empty
  if (is_empty()) {
    return false;
  }

  // Buffer is not empty, so remove item
  *item = buffer[out];    // Get item from buffer
  out = (out + 1) % size; // Increment out index and wrap if necessary
  count--;                // Decrement count

  return true;
}

int Buffer::get_size() { return size; }

int Buffer::get_count() { return count; }

bool Buffer::is_empty() { return count == 0; }

bool Buffer::is_full() { return count == size; }

void Buffer::print_buffer() {
  std::cout << "Buffer: [";
  int index = out; // Start at out index
  for (int i = 0; i < count; i++) {
    std::cout << buffer[index];
    if (i != count - 1) { // Print comma and space if not last element
      std::cout << ", ";
    }
    index = (index + 1) % size; // Increment index and wrap if necessary
  }
  std::cout << "]" << std::endl;
}
