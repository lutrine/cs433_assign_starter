/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_sjf.h"
#include <algorithm>

// TODO: add implementation of SchedulerSJF constructor, destructor, and
// member functions init, print_results, and simulate here

// Constructor
SchedulerSJF::SchedulerSJF() {
  current_time = 0;
  total_waiting_time = 0;
  total_turnaround_time = 0;
  avg_waiting_time = 0;
  avg_turnaround_time = 0;
}

// Destructor
SchedulerSJF::~SchedulerSJF() {}

// Initialize the scheduler with an array of incoming processes
void SchedulerSJF::init(std::vector<PCB> &process_list) {
  for (PCB &process : process_list) {
    ready_queue.push_back(process);
  }
  // Sort the ready queue by burst time
  std::sort(
      ready_queue.begin(), ready_queue.end(),
      [](const PCB &a, const PCB &b) { return a.burst_time < b.burst_time; });
}

// Print out the statistics, including the turn-around and waiting time of each
// process and the average turn-around and waiting time
void SchedulerSJF::print_results() {
  for (PCB &process : ready_queue) {
    std::cout << "T" << process.id + 1 << " ";
    std::cout << "turn-around time = " << process.turnaround_time << ", ";
    std::cout << "waiting time = " << process.waiting_time << std::endl;
  }
  std::cout << "Average turn-around time = " << avg_turnaround_time << ", ";
  std::cout << "average waiting time = " << avg_waiting_time << std::endl;
}

// Simulate the scheduling of processes in an SJF ready-queue
void SchedulerSJF::simulate() {
  // Store the initial size of the ready queue (used to calculate the average
  // waiting time and turnaround time)
  int num_of_processes = ready_queue.size();
  int i = 0;

  while (i < num_of_processes) {
    // Get the front process from the queue and remove it from the queue
    PCB &process = ready_queue[i];
    cout << "Running Process T" << process.id + 1 << " for "
         << process.burst_time << " time units" << endl;

    // If the current time is less than the arrival time, wait for the process
    // to arrive
    if (current_time < process.arrival_time) {
      // Move the current time to the arrival time
      current_time = process.arrival_time;
    }

    // Calculate waiting time
    process.waiting_time = current_time - process.arrival_time;

    // Calculate turnaround time
    process.turnaround_time = process.waiting_time + process.burst_time;

    // Update statistics
    total_waiting_time += process.waiting_time;
    total_turnaround_time += process.turnaround_time;

    // Update current time
    current_time += process.burst_time;

    // Update the completion time of the process
    process.completion_time = current_time;

    i++;
  }

  // After all processes are executed, calculate averages (we cast the total
  // times as doubles so that integer division does not occur)
  avg_waiting_time = static_cast<double>(total_waiting_time) / num_of_processes;
  avg_turnaround_time =
      static_cast<double>(total_turnaround_time) / num_of_processes;
}
