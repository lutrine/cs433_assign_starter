/**
 * Assignment 5: Page replacement algorithms
 * @file pagetable.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#include "pagetable.h"

// TODO: Add your implementation of PageTable

// Constructor
PageTable::PageTable(int num_pages) {
  PageEntry temp;

  temp.frame_num = 0;
  temp.valid = false;
  temp.dirty = false;

  pages.resize(num_pages, temp);
}

// Destructor
PageTable::~PageTable() {
  // TODO: add code
}
