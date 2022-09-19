
/*
 *
 * Simulation of Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdio.h>
#include "simlib.h"

/*******************************************************************************/

typedef struct {
  double utilization;
  double fraction_served;
  double mean_number_in_system;
  double mean_delay;
} Simulation_Result;

/*
 * Simulation Parameters
 */

#define RANDOM_SEED 5259140
#define NUMBER_TO_SERVE 50e6

#define SERVICE_TIME 10
#define ARRIVAL_RATE 0.1

#define BLIP_RATE 10000

typedef struct {
  char* step_name;

  double* numbers_to_serve;
  int numbers_to_serve_size;

  int* service_times;
  int service_times_size;

  double* arrival_rates;
  int arrival_rates_size;

  int* random_seeds;
  // int random_seeds_size;

  int md1_or_mm1; // 0: M/D/1, 1: M/M/1

  // TODO: Add additional parameters to handle steps 7 and 8
} Step_Configuration;

double step2_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step2_service_times[] = {10};
double step2_arrival_rates[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09};
int step2_random_seeds[] = {RANDOM_SEED, 400137394, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED}; 

double step3_numbers_to_serve[] = {10e3, 20e3, 30e3, 40e3, 50e3, 60e3};
int step3_service_times[] = {10};
double step3_arrival_rates[] = {1.1};
int step3_random_seeds[] = {RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, 400137394, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED}; 

double step4_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step4_service_times[] = {30};
double step4_arrival_rates[] = {0.01, 0.04, 0.07, 0.11, 0.14, 0.17, 0.20, 0.23, 0.26, 0.29};
int step4_random_seeds[] = {RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED, 400137394, RANDOM_SEED, RANDOM_SEED, RANDOM_SEED}; 

Step_Configuration steps[] = {
  {
    "Step 2",
    step2_numbers_to_serve,
    1,
    step2_service_times,
    1,
    step2_arrival_rates,
    9,
    step2_random_seeds,
    0,
  },
  {
    "Step 3",
    step3_numbers_to_serve,
    6,
    step3_service_times,
    1,
    step3_arrival_rates,
    1,
    step3_random_seeds,
    0,
  },
  {
    "Step 4",
    step4_numbers_to_serve,
    1,
    step4_service_times,
    1,
    step4_arrival_rates,
    10,
    step4_random_seeds,
    0,
  },
  {
    "Step 5",
    step2_numbers_to_serve,
    1,
    step2_service_times,
    1,
    step2_arrival_rates,
    9,
    step2_random_seeds,
    1,
  }
};

int run(Step_Configuration *steps, int steps_size);
int run_step(Step_Configuration step);
Simulation_Result run_simulation(double number_to_serve, int service_time, double arrival_rate, int* random_seeds, int md1_or_mm1);
int flush_results(Simulation_Result *sim_rslts, int sim_rslts_size);

int run(Step_Configuration *steps, int steps_size){
 //printf("MADE IT TO RUN!\n");
  for(int step_index = 0; step_index < steps_size; step_index++){
    printf("\nSimulating Step %d\n", step_index+2);
    run_step(steps[step_index]);
  }

  return 0;
}

int run_step(Step_Configuration step){
  //printf("MADE IT TO RUN_STEP!\n");
  int sim_rslts_size = step.numbers_to_serve_size * step.service_times_size * step.arrival_rates_size;
  Simulation_Result* sim_rslts = calloc(
    sim_rslts_size,
    sizeof(Simulation_Result)
  );


  for(int i = 0, sim_run = 0; i < step.numbers_to_serve_size; i++){
    for(int j = 0; j < step.service_times_size; j++){
      for(int k = 0; k < step.arrival_rates_size; k++, sim_run++){
        sim_rslts[i*step.service_times_size + j*step.arrival_rates_size +k] = run_simulation(
          step.numbers_to_serve[i],
          step.service_times[j],
          step.arrival_rates[k],
          step.random_seeds,
          step.md1_or_mm1
        );

      }
    }
  }

  flush_results(sim_rslts, sim_rslts_size);

  return 0;
}

Simulation_Result run_simulation(double number_to_serve, int service_time, double arrival_rate, int* random_seeds, int md1_or_mm1){
  //printf("RUN_SIMULATION!\n");
  double acc_utilization = 0;
  double acc_fraction_served = 0;
  double acc_mean_number_in_system = 0;
  double acc_mean_delay = 0;

  printf("ARRIVAL_RATE = %f\tSERVICE_TIME = %d\n", arrival_rate, service_time);
  //printf("SERVICE_TIME = %d\n", service_time);
  
  for(int run = 0; run < 10; run++){
    double clock = 0; /* Clock keeps track of simulation time. */

    /* System state variables. */
    int number_in_system = 0;
    double next_arrival_time = 0;
    double next_departure_time = 0;

    /* Data collection variables. */
    long int total_served = 0;
    long int total_arrived = 0;

    double total_busy_time = 0;
    double integral_of_n = 0;
    double last_event_time = 0;

    /* Set the seed of the random number generator. Will use McMaster ID as the random seed for a single run*/
    random_generator_initialize(random_seeds[run]);

    /* Process customers until we are finished. */
    while (total_served < number_to_serve) {
        /* Test if the next event is a customer arrival or departure. */
      if(number_in_system == 0 || next_arrival_time < next_departure_time) {

        /*
          * A new arrival is occurring.
          */

        clock = next_arrival_time;
        next_arrival_time = clock + exponential_generator((step.md1_or_mm1) ? (double)service_time : (double) 1/arrival_rate);

        /* Update our statistics. */
        integral_of_n += number_in_system * (clock - last_event_time);
        last_event_time = clock;

        number_in_system++;
        total_arrived++;

        /* If this customer has arrived to an empty system, start its
      service right away. */
        if(number_in_system == 1) next_departure_time = clock + service_time;

      } else {

        /*
          * A customer departure is occuring. 
          */

        clock = next_departure_time;

        /* Update our statistics. */
        integral_of_n += number_in_system * (clock - last_event_time);
        last_event_time = clock;

        number_in_system--;
        total_served++;
        total_busy_time += service_time;

        /* 
          * If there are other customers waiting, start one in service
          * right away.
          */

        if(number_in_system > 0) next_departure_time = clock + service_time;

        /* 
          * Every so often, print an activity message to show we are active. 
          */

        if (total_served % BLIP_RATE == 0)
          printf("Customers served = %ld (Total arrived = %ld)\r",
            total_served, total_arrived);
      }

    }

    acc_utilization += total_busy_time/clock;
    acc_fraction_served += (double) total_served/total_arrived;
    acc_mean_number_in_system += integral_of_n/clock;
    acc_mean_delay += integral_of_n/total_served;

    printf("RESULTS AFTER RUN #%d - utilization = %f, fraction_served = %f, mean_number_in_system = %f, mean_delay = %f\n",
      run, total_busy_time/clock, (double) total_served/total_arrived, integral_of_n/clock, integral_of_n/total_served);

  }

  printf("ACCUMULATED RESULTS - utilization = %f, fraction_served = %f, mean_number_in_system = %f, mean_delay = %f\n",
    acc_utilization, acc_fraction_served, acc_mean_number_in_system, acc_mean_delay);

  printf("AVERAGED RESULTS - utilization = %f, fraction_served = %f, mean_number_in_system = %f, mean_delay = %f\n",
    acc_utilization/10, acc_fraction_served/10, acc_mean_number_in_system/10, acc_mean_delay/10);

  printf("\n");

  return (Simulation_Result){
    acc_utilization/10,
    acc_fraction_served/10,
    acc_mean_number_in_system/10,
    acc_mean_delay/10
  };
}

int flush_results(Simulation_Result *sim_rslts, int sim_rslts_size){
  // export file here
  printf("\nRESULTS!\n");
  for (int i=0; i<sim_rslts_size; i++) {
    printf("utilization = %f\n", sim_rslts[i].utilization);
    printf("fraction_served = %f\n", sim_rslts[i].fraction_served);
    printf("mean_number_in_system = %f\n", sim_rslts[i].mean_number_in_system);
    printf("mean_delay = %f\n", sim_rslts[i].mean_delay);
  }

  
  return 0;
}
/*******************************************************************************/

/*
 * main() uses various simulation parameters and creates a clock variable to
 * simulate real time. A loop repeatedly determines if the next event to occur
 * is a customer arrival or customer departure. In either case the state of the
 * system is updated and statistics are collected before the next
 * iteration. When it finally reaches NUMBER_TO_SERVE customers, the program
 * outputs some statistics such as mean delay.
 */

int main()
{
  run(steps, 1);
  //printf("Steps name = %s", steps[0].step_name);
  // /* Output final results. */
  // printf("\nUtilization = %f\n", total_busy_time/clock);
  // printf("Fraction served = %f\n", (double) total_served/total_arrived);
  // printf("Mean number in system = %f\n", integral_of_n/clock);
  // printf("Mean delay = %f\n", integral_of_n/total_served);

  /* Halt the program before exiting. */
  printf("\nHit Enter to finish ... \n");
  getchar(); 

  return 0;

}






