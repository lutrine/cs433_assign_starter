/**
 * Assignment 5: Page replacement algorithms
 * @file fifo_replacement.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

FIFOReplacement::FIFOReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

FIFOReplacement::~FIFOReplacement() {}

void FIFOReplacement::load_page(int page_num) {
  // Calculate frame number for new page
  int frame_num = total_frames - free_frames;

  // Update page table with frame number and mark page as valid
  page_table[page_num].frame_num = frame_num;
  page_table[page_num].valid = true;

  // Add page number to queue
  queue.push(page_num);
}

int FIFOReplacement::replace_page(int page_num) {
  // Get oldest page as victim page
  int victim_page = queue.front();
  queue.pop();

  // Update the page table for the victim page
  page_table[victim_page].valid = false;

  // Use the frame of the victim page for the new page
  page_table[page_num].frame_num = page_table[victim_page].frame_num;

  // Update the page table for the new page
  page_table[page_num].valid = true;

  // Enqueue the new page
  queue.push(page_num);

  // Return victim page number
  return victim_page;
}
