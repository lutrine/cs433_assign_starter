/**
 * Assignment 5: Page replacement algorithms
 * @file lifo_replacement.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief A class implementing the Last in First Out (LIFO) page replacement
 * algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

LIFOReplacement::LIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

LIFOReplacement::~LIFOReplacement() {}

void LIFOReplacement::load_page(int page_num) {
  // Calculate frame number for new page
  int frame_num = total_frames - free_frames;

  // Update page table with frame number and mark page as valid
  page_table[page_num].frame_num = frame_num;
  page_table[page_num].valid = true;

  // Push page number onto stack
  stack.push(page_num);
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
  // Get most recently loaded page as victim page
  int victim_page = stack.top();
  stack.pop();

  // Update page table to mark victim page as invalid
  page_table[victim_page].valid = false;

  // Use frame of victim page for new page
  page_table[page_num].frame_num = page_table[victim_page].frame_num;

  // Update page table to mark new page as valid
  page_table[page_num].valid = true;

  // Push new page number onto stack
  stack.push(page_num);

  // Return victim page number
  return victim_page;
}
