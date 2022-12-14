
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

#define STUDENT_NUMBER_GJ 400137394
#define STUDENT_NUMBER_CARLOS 400184894
#define STUDENT_NUMBER_RAFI 400182022

typedef struct {
  double arrival_rate;
  int service_time;
  double number_to_serve;
  double max_queue_size;

  double utilization;
  double fraction_served;
  double rejection_probability;
  double mean_number_in_system;
  double mean_delay;
} Simulation_Result;

/*
 * Simulation Parameters
 */

#define RANDOM_SEED_0 5259140
#define RANDOM_SEED_1 3955051
#define RANDOM_SEED_2 8517605
#define RANDOM_SEED_3 4721416
#define RANDOM_SEED_4 2965788
#define RANDOM_SEED_5 3896382
#define RANDOM_SEED_6 7297461
#define RANDOM_SEED_7 1714639
#define RANDOM_SEED_8 9685552
#define RANDOM_SEED_9 1007278

#define NUMBER_TO_SERVE 50e6

#define SERVICE_TIME 10
#define ARRIVAL_RATE 0.1

#define BLIP_RATE 10000

#define MAX_QUEUE_SIZE 20e6 //20 million queue for now we can change this 
#define MAX_QUEUE_SIZES_SIZE_DEFAULT 1

typedef struct {
  char* step_name;

  double* numbers_to_serve;
  int numbers_to_serve_size;

  int* service_times;
  int service_times_size;

  double* arrival_rates;
  int arrival_rates_size;

  int use_max_queue;
  double* max_queue_sizes;
  int max_queue_sizes_size;

  int* random_seeds;
  // int random_seeds_size;

  int md1_or_mm1; // 0: M/D/1, 1: M/M/1

  // TODO: Add additional parameters to handle steps 7 and 8
} Step_Configuration;

double MAX_QUEUE_SIZES_DEFAULT[] = {MAX_QUEUE_SIZE};

double step2_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step2_service_times[] = {10};
double step2_arrival_rates[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09};
int random_seeds[] = {STUDENT_NUMBER_GJ, STUDENT_NUMBER_CARLOS, STUDENT_NUMBER_RAFI, RANDOM_SEED_0, RANDOM_SEED_1, RANDOM_SEED_2, RANDOM_SEED_3, RANDOM_SEED_4, RANDOM_SEED_5, RANDOM_SEED_6};

double step3_numbers_to_serve[] = {10e3, 20e3, 30e3, 40e3, 50e3, 60e3};
int step3_service_times[] = {10};
double step3_arrival_rates[] = {0.2};

double step4_numbers_to_serve[] = {NUMBER_TO_SERVE};
int step4_service_times[] = {30};
double step4_arrival_rates[] = {0.001, 0.004, 0.007, 0.011, 0.014, 0.017, 0.020, 0.023, 0.026, 0.029};

double step7_arrival_rates[] = {0.01, 0.09, 0.11, 0.13, 0.15, 0.17, 0.32, 0.57, 0.79};
double step7_max_queue_sizes[] = {3, 6, 12, 25, 50, 10e1};
const int step7_max_queue_sizes_size = 6;

//double step8_arrival_rates[] = {1/0.01, 1/0.02, 1/0.03, 1/0.04, 1/0.05, 1/0.06, 1/0.07, 1/0.08, 1/0.09};

Step_Configuration steps[] = {
  // {
  //   "Step 2",
  //   step2_numbers_to_serve,
  //   1,
  //   step2_service_times,
  //   1,
  //   step2_arrival_rates,
  //   9,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // },
  // {
  //   "Step 3",
  //   step3_numbers_to_serve,
  //   6,
  //   step3_service_times,
  //   1,
  //   step3_arrival_rates,
  //   1,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // },
  // {
  //   "Step 4",
  //   step4_numbers_to_serve,
  //   1,
  //   step4_service_times,
  //   1,
  //   step4_arrival_rates,
  //   10,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // },
  // {
  //   "Step 6 M/D/1",
  //   step2_numbers_to_serve,
  //   1,
  //   step4_service_times,
  //   1,
  //   step2_arrival_rates,
  //   9,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // },
  //   {
  //   "Step 6 M/M/1",
  //   step2_numbers_to_serve,
  //   1,
  //   step4_service_times,
  //   1,
  //   step2_arrival_rates,
  //   9,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   1,
  // },
  {
    "Step 7",
    step2_numbers_to_serve,
    1,
    step2_service_times,
    1,
    step7_arrival_rates,
    9,
    1,
    step7_max_queue_sizes,
    step7_max_queue_sizes_size,
    random_seeds,
    1,
  }
  // {
  //   "Step 8 Part 2",
  //   step2_numbers_to_serve,
  //   1,
  //   step2_service_times,
  //   1,
  //   step2_arrival_rates,
  //   9,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // },
  // {
  //   "Step 8 Part 3",
  //   step3_numbers_to_serve,
  //   6,
  //   step3_service_times,
  //   1,
  //   step3_arrival_rates,
  //   1,
  //   0,
  //   MAX_QUEUE_SIZES_DEFAULT,
  //   MAX_QUEUE_SIZES_SIZE_DEFAULT,
  //   random_seeds,
  //   0,
  // }
};

int run(Step_Configuration *steps, int steps_size);
int run_step(Step_Configuration step, FILE *fpt);
Simulation_Result run_simulation(
  double number_to_serve,
  int service_time,
  double arrival_rate,
  int* random_seeds,
  int md1_or_mm1,
  int use_max_queue,
  double max_queue_size
);
int flush_results(char* step_name, Simulation_Result *sim_rslts, int sim_rslts_size, FILE *fpt);

int run(Step_Configuration *steps, int steps_size){
 //printf("MADE IT TO RUN!\n");
  FILE *fpt = fopen("simulation_results.csv", "w");
  fprintf(fpt, "Arrival Rate, Service Time, Number to Serve, Utilization, Fraction Served, Customer Rejection Probability, Mean Number in System, Mean Delay\n");

  for(int step_index = 0; step_index < steps_size; step_index++){
    printf("\nSimulating %s\n", steps[step_index].step_name);
    run_step(steps[step_index], fpt);
  }

  fclose(fpt);

  return 0;
}

int run_step(Step_Configuration step, FILE *fpt){
  //printf("MADE IT TO RUN_STEP!\n");
  int sim_rslts_size = step.numbers_to_serve_size * step.service_times_size * step.arrival_rates_size * step.max_queue_sizes_size;
  Simulation_Result* sim_rslts = calloc(
    sim_rslts_size,
    sizeof(Simulation_Result)
  );


  for(int i = 0; i < step.numbers_to_serve_size; i++){
    for(int j = 0; j < step.service_times_size; j++){
      for(int k = 0; k < step.arrival_rates_size; k++){
          for(int l = 0; l < step.max_queue_sizes_size; l++){
          sim_rslts[i*step.service_times_size + j*step.arrival_rates_size +k*step.max_queue_sizes_size + l] = run_simulation(
            step.numbers_to_serve[i],
            step.service_times[j],
            step.arrival_rates[k],
            step.random_seeds,
            step.md1_or_mm1,
            step.use_max_queue,
            step.max_queue_sizes[l]
          );
        }
      }
    }
  }

  flush_results(step.step_name, sim_rslts, sim_rslts_size, fpt);

  return 0;
}

Simulation_Result run_simulation(
  double number_to_serve,
  int service_time,
  double arrival_rate,
  int* random_seeds,
  int md1_or_mm1,
  int use_max_queue,
  double max_queue_size
){
  //printf("RUN_SIMULATION!\n");
  double acc_utilization = 0;
  double acc_fraction_served = 0;
  double acc_mean_number_in_system = 0;
  double acc_mean_delay = 0;
  double acc_rejection_probability = 0;

  printf("ARRIVAL_RATE = %f\tSERVICE_TIME = %d\tMAX_QUEUE_SIZE =%f\n", arrival_rate, service_time, max_queue_size);
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
    long int total_rejected = 0;

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
        next_arrival_time = clock + exponential_generator((md1_or_mm1) ? (double)service_time : (double) 1/arrival_rate); //Step 6
        //exponential_generator((md1_or_mm1) ? (double)service_time : (double) 1/arrival_rate); //Step 6
        //Step 8 change this to clock + 1/arrival_rate

        /* Update our statistics. */
        integral_of_n += number_in_system * (clock - last_event_time);
        last_event_time = clock;

        //Step 7
        if(use_max_queue == 1 && number_in_system > max_queue_size) {
          total_rejected++;
        } else {
          number_in_system++;
        }
        
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
    acc_rejection_probability += (double) total_rejected/total_arrived;
    acc_mean_number_in_system += integral_of_n/clock;
    acc_mean_delay += integral_of_n/total_served;

    printf("RESULTS AFTER RUN #%d - utilization = %f, fraction_served = %f, rejection_probability = %f, mean_number_in_system = %f, mean_delay = %f\n",
      run, total_busy_time/clock, (double) total_served/total_arrived, (double) total_rejected/total_arrived, integral_of_n/clock, integral_of_n/total_served);

  }

  printf("AVERAGED RESULTS - utilization = %f, fraction_served = %f, rejection_probability = %f, mean_number_in_system = %f, mean_delay = %f\n",
    acc_utilization/10, acc_fraction_served/10, (double) acc_rejection_probability/10, acc_mean_number_in_system/10, acc_mean_delay/10);

  printf("\n");

  return (Simulation_Result){
    arrival_rate,
    service_time,
    number_to_serve,
    max_queue_size,

    acc_utilization/10,
    acc_fraction_served/10,
    acc_rejection_probability/10,
    acc_mean_number_in_system/10,
    acc_mean_delay/10
  };
}

int flush_results(char* step_name, Simulation_Result *sim_rslts, int sim_rslts_size, FILE *fpt){
  // export file here
  fprintf(fpt, "\n%s\n", step_name);

  printf("\nRESULTS!\n");
  for (int i=0; i<sim_rslts_size; i++) {
    fprintf(fpt, "%f, %d, %f, %f, %f, %f, %f, %f\n",
      sim_rslts[i].arrival_rate,
      sim_rslts[i].service_time,
      sim_rslts[i].number_to_serve,
      sim_rslts[i].utilization,
      sim_rslts[i].fraction_served,
      sim_rslts[i].rejection_probability,
      sim_rslts[i].mean_number_in_system,
      sim_rslts[i].mean_delay
      );

    // printf("utilization = %f\n", sim_rslts[i].utilization);
    // printf("fraction_served = %f\n", sim_rslts[i].fraction_served);
    // printf("mean_number_in_system = %f\n", sim_rslts[i].mean_number_in_system);
    // printf("mean_delay = %f\n", sim_rslts[i].mean_delay);
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






