
/*
 * 
 * Call Blocking in Circuit Switched Networks
 * 
 * Copyright (C) 2014 Terence D. Todd
 * Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "trace.h"
#include "simparameters.h"
#include "cleanup.h"
#include "call_arrival.h"
#include "main.h"

/*******************************************************************************/

int main(void)
{
  int i;
  double block_prob;

  Simulation_Run_Ptr simulation_run;
  Simulation_Run_Data data; /* Simulation_Run_Data is defined in main.h. */

  /* 
   * Get the list of random number generator seeds defined in simparameters.h.
   */

  unsigned RANDOM_SEEDS[] = {RANDOM_SEED_LIST, 0};
  unsigned random_seed;

  /* 
   * Loop for each random number generator seed, doing a separate
   * simulation_run run for each.
   */

  FILE* out_csv = create_step2_csv();
  for(double call_arrival_rate = 1; call_arrival_rate <=11; call_arrival_rate++){
    for(int number_of_channels = 1, j = 0; number_of_channels < 20; number_of_channels++){
      j = 0;
      double acc_block_prob = 0;
      while ((random_seed = RANDOM_SEEDS[j++]) != 0) {

        /* Create a new simulation_run. This gives a clock and eventlist. */
        simulation_run = simulation_run_new();

        /* Add our data definitions to the simulation_run. */
        simulation_run_set_data(simulation_run, (void *) & data);

<<<<<<< HEAD
    /* Initialize our simulation_run data variables. */
    data.blip_counter = 0;
    data.call_arrival_count = 0;
    data.calls_processed = 0;
    data.blocked_call_count = 0;
    data.number_of_calls_processed = 0;
    data.accumulated_call_time = 0.0;
    data.random_seed = random_seed;
    data.hang_up = 0; //step 4
    data.mean_time = 0; //step 4
    data.in_queue = 0; //step 4
    data.amt_wait_t_sec = 0; //step 5
    data.buffer = fifoqueue_new(); //step 4
=======
        /* Initialize our simulation_run data variables. */
        data.blip_counter = 0;
        data.call_arrival_count = 0;
        data.calls_processed = 0;
        data.blocked_call_count = 0;
        data.number_of_calls_processed = 0;
        data.accumulated_call_time = 0.0;
        data.random_seed = random_seed;
        data.call_arrival_rate = call_arrival_rate;
        data.number_of_channels = number_of_channels;
>>>>>>> origin/master

        /* Create the channels. */
        data.channels = (Channel_Ptr *) xcalloc((int) number_of_channels,
                  sizeof(Channel_Ptr));

        /* Initialize the channels. */
        for (i=0; i<number_of_channels; i++) {
          *(data.channels+i) = server_new(); 
        }

        /* Set the random number generator seed. */
        random_generator_initialize((unsigned) random_seed);

        /* Schedule the initial call arrival. */
        schedule_call_arrival_event(simulation_run,
          simulation_run_get_time(simulation_run) +
          exponential_generator((double) 1/call_arrival_rate));
        
        /* Execute events until we are finished. */
        while(data.number_of_calls_processed < RUNLENGTH) {
          simulation_run_execute_event(simulation_run);
        }
        
        // todo: Check where results are stored, and accumulate them to compute the average
        /* Print out some results. */
        output_results(simulation_run);
        acc_block_prob += block_fraction(simulation_run);

        /* Clean up memory. */
        cleanup(simulation_run);
      }
      block_prob = acc_block_prob/j;
      printf("acc_block_prob = %f, blocking probability = %f\n", acc_block_prob, block_prob);
      write_step2(out_csv, call_arrival_rate, number_of_channels, block_prob);
    }
  }
  fclose(out_csv);
  /* Pause before finishing. */
  printf("Press any key to finish\n");
  getchar();
  return 0;
}


double block_fraction(Simulation_Run_Ptr this_simulation_run){
  Simulation_Run_Data_Ptr sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(this_simulation_run);
  return 1 - (double) (sim_data->call_arrival_count -
    sim_data->blocked_call_count)/sim_data->call_arrival_count;
}