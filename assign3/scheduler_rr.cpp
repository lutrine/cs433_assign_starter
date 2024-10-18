/**
 * Assignment 3: CPU Scheduler
 * @file scheduler_rr.h
 * @author Caden Jamason and Adrian Reyes
 * @brief This Scheduler class implements the RoundRobin (RR) scheduling
 * algorithm.
 * @version 0.1
 */

#include "scheduler_rr.h"

// TODO: add implementation of SchedulerRR constructor, destructor, and
// member functions init, print_results, and simulate here

// Constructor
SchedulerRR::SchedulerRR(int time_quantum) {
  current_time = 0;
  total_waiting_time = 0;
  total_turnaround_time = 0;
  avg_waiting_time = 0;
  avg_turnaround_time = 0;
  time_slice = time_quantum;
}

// Deconstructor
SchedulerRR::~SchedulerRR() {}

// Initialize the scheduler with an array of incoming processes
void SchedulerRR::init(std::vector<PCB> &process_list) {
  for (PCB &process : process_list) {
    ready_queue.push_back(process);
  }
}

// After
void SchedulerRR::print_results() {
  for (PCB &process : ready_queue) {
    std::cout << "T" << process.id + 1 << " ";
    std::cout << "turn-around time = " << process.turnaround_time << ", ";
    std::cout << "waiting time = " << process.waiting_time << std::endl;
  }
  std::cout << "Average turn-around time = " << avg_turnaround_time << ", ";
  std::cout << "average waiting time = " << avg_waiting_time << std::endl;
}

void SchedulerRR::simulate() {

  // Store the initial size of the ready queue (used to calculate the average
  // waiting time and turnaround time)

  int num_of_processes = ready_queue.size();
  int i = 0, o = 0;
  int slice = time_slice;
  // Holds starting burst values for waiting time calculation
  int start_burst[num_of_processes];
  bool lock = true;

  // Fills start_burst array with the processes starting burst values
  PCB &process = ready_queue[o];
  for (o; o < num_of_processes; o++)
    start_burst[o] = ready_queue[o].burst_time;

  while (lock) {
    // Starting from first process
    PCB &process = ready_queue[i];

    if (process.burst_time >
        slice) // If process has more than a slice's worth of time left
    {
      process.burst_time -= slice;
      cout << "Running Process T" << process.id + 1 << " for " << slice
           << " time units" << endl;

      current_time += slice;
    } else if (process.burst_time == 0) // If process is finished, ignore.
    {
      ;
    } else { // If process finishes

      cout << "Running Process T" << process.id + 1 << " for "
           << process.burst_time << " time units" << endl;

      current_time += process.burst_time;
      process.turnaround_time = current_time;

      process.waiting_time = current_time - start_burst[i];
      process.burst_time = 0;

      total_waiting_time += process.waiting_time;
      total_turnaround_time += process.turnaround_time;

      lock = false;
    }

    i = (i + 1) % (num_of_processes); // Move on to next process

    // Checks if all of the burst times have expired, if they have, unlock loop
    for (int j = 0; j < num_of_processes; j++) {
      if (ready_queue[j].burst_time > 0)
        lock = true;
    }
  }
  // After all processes are executed, calculate averages (we cast the total
  // times as doubles so that integer division does not occur)
  avg_waiting_time = static_cast<double>(total_waiting_time) / num_of_processes;
  avg_turnaround_time =
      static_cast<double>(total_turnaround_time) / num_of_processes;
}