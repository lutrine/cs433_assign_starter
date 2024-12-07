/**
 * Assignment 5: Page replacement algorithms
 * @file lru_replacement.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"

LRUReplacement::LRUReplacement(int num_pages, int num_frames)
    : Replacement(num_pages, num_frames) {}

LRUReplacement::~LRUReplacement() {}

void LRUReplacement::touch_page(int page_num) {
  // Move accessed page to front of list
  lru_list.erase(page_map[page_num]);
  lru_list.push_front(page_num);
  page_map[page_num] = lru_list.begin();
}

void LRUReplacement::load_page(int page_num) {
  // Calculate frame number for new page
  int frame_num = total_frames - free_frames;

  // Update page table with frame number and mark page as valid
  page_table[page_num].frame_num = frame_num;
  page_table[page_num].valid = true;

  // Move new page to front of list
  lru_list.push_front(page_num);
  page_map[page_num] = lru_list.begin();
}

int LRUReplacement::replace_page(int page_num) {
  // Least recently used page is at the back of the list
  int victim_page = lru_list.back();
  lru_list.pop_back();

  // Update page table for victim page
  page_table[victim_page].valid = false;

  // Use the frame of the victim page for the new page
  page_table[page_num].frame_num = page_table[victim_page].frame_num;

  // Update page table for new page
  page_table[page_num].valid = true;

  // Move new page to front of list
  lru_list.push_front(page_num);
  page_map[page_num] = lru_list.begin();

  // Remove victim page from map
  page_map.erase(victim_page);

  // Return victim page number
  return victim_page;
}
