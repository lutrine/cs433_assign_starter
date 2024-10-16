/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Caden Jamason and Adrian Reyes
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority.h"
#include <algorithm>

// Constructor
SchedulerPriority::SchedulerPriority() {}

// Destructor
SchedulerPriority::~SchedulerPriority() {}

// Initialize the scheduler with an array of incoming processes
void SchedulerPriority::init(std::vector<PCB> &process_list) {
  for (PCB &process : process_list) {
    ready_queue.push_back(process);
  }
  // Sort the ready queue by priority
  // We use a lambda function to compare the priority of two PCBs
  std::sort(ready_queue.begin(), ready_queue.end(),
            [](const PCB &a, const PCB &b) { return a.priority > b.priority; });
}

// Print out the statistics, including the turn-around and waiting time of each
// process and the average turn-around and waiting time
void SchedulerPriority::print_results() {
  for (PCB &process : ready_queue) {
    std::cout << "T" << process.id + 1 << " ";
    std::cout << "turn-around time = " << process.turnaround_time << ", ";
    std::cout << "waiting time = " << process.waiting_time << std::endl;
  }
  std::cout << "Average turn-around time = " << avg_turnaround_time << ", ";
  std::cout << "average waiting time = " << avg_waiting_time << std::endl;
}

// Simulate the scheduling of processes in an SJF ready-queue
void SchedulerPriority::simulate() {
  // Store the initial size of the ready queue (used to calculate the average
  // waiting time and turnaround time)
  int num_of_processes = ready_queue.size();
  int i = 0;

  while (i < num_of_processes) {
    // Get the front process from the queue and remove it from the queue
    PCB &process = ready_queue[i];

    // Print out the process that is being executed
    cout << "Running Process T" << process.id + 1 << " for "
         << process.burst_time << " time units" << endl;

    // If the current time is less than the arrival time...
    if (current_time < process.arrival_time) {
      // Update the current time to the arrival time of the process
      current_time = process.arrival_time;
    }

    // Calculate the waiting time and turnaround time
    process.waiting_time = current_time - process.arrival_time;
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
