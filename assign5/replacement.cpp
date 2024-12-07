/**
 * Assignment 5: Page replacement algorithms
 * @file replacement.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include "replacement.h"
#include <iostream>

// TODO: add implementation of Replacement member functions

// Constructor
Replacement::Replacement(int num_pages, int num_frames)
    : page_table(num_pages) {
  free_frames = num_frames;
  total_pages = num_pages;
  total_frames = num_frames;
}

// Destructor
Replacement::~Replacement() {}

// Simulate a single page access
bool Replacement::access_page(int page_num, bool is_write) {
  num_references++; // Increment number of page references no matter what

  if (page_table[page_num].valid) {
    // Call touch_page function if page is valid
    touch_page(page_num);
    // Return false because no page fault occurred
    return false;
  } else {
    // Increment number of page faults since page is not valid
    num_page_faults++;
    if (free_frames > 0) {
      // Call load_page function if there are free frames
      load_page(page_num);
      // Decrement number of free frames since a page was loaded
      free_frames--;
    } else {
      // Increment number of page replacements since there are no free frames
      num_page_replacements++;
      // Call replace_page function if there are no free frames
      replace_page(page_num);
    }
    // Return true because a page fault occurred
    return true;
  }
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
  std::cout << "Number of references: \t\t" << num_references << std::endl;
  std::cout << "Number of page faults: \t\t" << num_page_faults << std::endl;
  std::cout << "Number of page replacements: \t" << num_page_replacements
            << std::endl;
}
