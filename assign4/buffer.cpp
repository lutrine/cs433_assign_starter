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
  for (int i = 0; i < size; i++) {
    buffer[i] = 0;
  }
}

Buffer::~Buffer() {}

bool Buffer::insert_item(buffer_item item) {
  if (is_full()) {
    return false;
  }
  buffer[in] = item;
  in = (in + 1) % BUFFER_SIZE;
  count++;
  return true;
}

bool Buffer::remove_item(buffer_item *item) {
  if (is_empty()) {
    return false;
  }
  *item = buffer[out];
  out = (out + 1) % size;
  count--;
  return true;
}

int Buffer::get_size() { return size; }

int Buffer::get_count() { return count; }

bool Buffer::is_empty() { return count == 0; }

bool Buffer::is_full() { return count == size; }

void Buffer::print_buffer() {
  std::cout << "Buffer: [";
  int index = out;
  for (int i = 0; i < count; i++) {
    std::cout << buffer[index];
    if (i != count - 1) {
      std::cout << ", ";
    }
    index = (index + 1) % size;
  }
  std::cout << "]" << std::endl;
}
