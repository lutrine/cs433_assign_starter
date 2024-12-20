/**
 * Driver (main) program for SJF scheduling algorithm.
 * The input file is a text file containing the process information in the
 * following format: [name] [priority] [CPU burst]
 */

#include "scheduler_sjf.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  std::cout << "CS 433 Programming assignment 3" << std::endl;
  std::cout << "Author: Caden Jamason and Adrian Reyes" << std::endl;
  std::cout << "Date: 10/25/2024" << std::endl;
  std::cout << "Course: CS433 (Operating Systems)" << std::endl;
  std::cout << "Description : test SJF scheduling algorithm " << std::endl;
  std::cout << "=================================" << std::endl;

  // Make sure the user has provided the input file name
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <input_file>" << endl;
    exit(1);
  }

  // Read the input file
  ifstream input_file(argv[1]);
  // Make sure the file is open
  if (!input_file.is_open()) {
    cerr << "Error: Unable to open file " << argv[1] << endl;
    exit(1);
  }
  string line;
  vector<PCB> process_list;
  int id = 0;
  while (getline(input_file, line)) {
    // Split the line into tokens
    istringstream ss(line);
    string name;
    // Parse out the name
    getline(ss, name, ',');
    // Parse out the priority
    string token;
    getline(ss, token, ',');
    unsigned int priority = stoi(token);
    // Parse out the burst time
    getline(ss, token, ',');
    unsigned int burst_time = stoi(token);

    // Create a PCB object and add it to the process list
    PCB pcb(name, id, priority, burst_time);
    id++;
    pcb.print();
    process_list.push_back(pcb);
  }

  // Create a scheduler object
  SchedulerSJF scheduler;
  // Run the scheduler
  scheduler.init(process_list);
  scheduler.simulate();
  scheduler.print_results();
}
