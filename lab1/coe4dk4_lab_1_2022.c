
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

struct Simulation_Result {
  double utilization,
  double fraction_served,
  double mean_number_in_system,
  double mean_delay,
}

/*
 * Simulation Parameters
 */

#define RANDOM_SEED 5259140
#define NUMBER_TO_SERVE 50e6

#define SERVICE_TIME 10
#define ARRIVAL_RATE 0.1

#define BLIP_RATE 10000

struct Step_Configuration {
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
};

double step2_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step2_service_times[] = {10};
double step2_arrival_rates[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09};
int step2_random_seeds[] = {400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394}; 

double step3_numbers_to_serve[] = {10e3, 20e3, 30e3, 40e3, 50e3, 60e3};
int step3_service_times[] = {10};
double step3_arrival_rates[] = {1.1};
int step3_random_seeds[] = {400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394}; 

double step4_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step4_service_times[] = {30};
double step4_arrival_rates[] = {0.01, 0.04, 0.07, 0.11, 0.14, 0.17, 0.20, 0.23, 0.26, 0.29};
int step4_random_seeds[] = {400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394, 400137394}; 

struct Step_Configuration steps[] = {
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

int run(struct Step_Configuration *steps, int steps_size);
int run_step(struct Step_Configuration step);
struct Simulation_Result run_simulation(double number_to_serve, int service_time, double arrival_rate, int* random_seeds, int md1_or_mm1);
int flush_results(struct Simulation_Result *sim_rslts, int sim_rslts_size);

int run(struct Step_Configuration *steps, int steps_size){
  for(int step_index = 0; step_index < steps_size; step_index++){
    run_step(steps[step_index]);
  }

  return 0;
}

int run_step(struct Step_Configuration step){
  int sim_rslts_size = step.numbers_to_serve_size * step.service_times_size * step.arrival_rates_size;
  struct Simulation_Result* sim_rslts = calloc(
    sim_rslts_size,
    sizeof(struct Simulation_Result)
  );
  double acc_mean_delay;


  for(int i = 0; i < step.numbers_to_serve_size; i++){
    for(int j = 0; j < step.service_times_size; j++){
      for(int k = 0; k < step.arrival_rates_size; k++){
        sim_rslts[(i+1)*(j+1)*(j+1)] = run_simulation(
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

  /* Set the seed of the random number generator. */
  random_generator_initialize(RANDOM_SEED);

  /* Process customers until we are finished. */
  while (total_served < NUMBER_TO_SERVE) {

    /* Test if the next event is a customer arrival or departure. */
   if(number_in_system == 0 || next_arrival_time < next_departure_time) {

     /*
      * A new arrival is occurring.
      */

     clock = next_arrival_time;
     next_arrival_time = clock + exponential_generator((double) 1/ARRIVAL_RATE);

     /* Update our statistics. */
     integral_of_n += number_in_system * (clock - last_event_time);
     last_event_time = clock;

     number_in_system++;
     total_arrived++;

     /* If this customer has arrived to an empty system, start its
	service right away. */
     if(number_in_system == 1) next_departure_time = clock + SERVICE_TIME;

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
     total_busy_time += SERVICE_TIME;

     /* 
      * If there are other customers waiting, start one in service
      * right away.
      */

     if(number_in_system > 0) next_departure_time = clock + SERVICE_TIME;

     /* 
      * Every so often, print an activity message to show we are active. 
      */

     if (total_served % BLIP_RATE == 0)
       printf("Customers served = %ld (Total arrived = %ld)\r",
	      total_served, total_arrived);
   }

  }

  /* Output final results. */
  printf("\nUtilization = %f\n", total_busy_time/clock);
  printf("Fraction served = %f\n", (double) total_served/total_arrived);
  printf("Mean number in system = %f\n", integral_of_n/clock);
  printf("Mean delay = %f\n", integral_of_n/total_served);

  /* Halt the program before exiting. */
  printf("Hit Enter to finish ... \n");
  getchar(); 

  return 0;

}






