
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

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/*******************************************************************************/

void output_progress_msg_to_screen(Simulation_Run_Ptr this_simulation_run)
{
  double percentagedone;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(this_simulation_run);

  sim_data->blip_counter++;

  if((sim_data->blip_counter >= BLIPRATE)
     ||
     (sim_data->number_of_calls_processed >= RUNLENGTH))
    {
      sim_data->blip_counter = 0;

      percentagedone =
	100 * (double) sim_data->number_of_calls_processed/RUNLENGTH;

      printf("%3.0f%% ", percentagedone);

      printf("Call Count = %ld \r", sim_data->number_of_calls_processed);

      fflush(stdout);
    }
}

/*******************************************************************************/

void output_results(Simulation_Run_Ptr this_simulation_run)
{
  double xmtted_fraction;
  double prob_of_hang_up;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(this_simulation_run);

  printf("\n");

  printf("random seed = %d \n", sim_data->random_seed);
  printf("call arrival count = %ld \n", sim_data->call_arrival_count);
  //printf("blocked call count = %ld \n", sim_data->blocked_call_count);
  printf("Hang Up Count = %d \n", sim_data->hang_up); //step 4

  prob_of_hang_up = (double)sim_data->hang_up/sim_data->call_arrival_count;

  printf("Probability = %.5f \n", prob_of_hang_up);

  printf("Amount in Queue = %d \n", sim_data->in_queue); 
  printf("Mean Queue Wait Times = %.5f \n", sim_data->mean_time/(double)sim_data->in_queue);
  printf("Amt of Customers to for t < T_SEC = %d \n", sim_data->amt_wait_t_sec);
  printf("Average Caller Waiting Time = %.20f \n", sim_data->mean_time/(double)sim_data->call_arrival_count);
  printf("Probability to Wait Less than T sec = %.5f \n", sim_data->amt_wait_t_sec/(double)sim_data->in_queue);


  // xmtted_fraction = (double) (sim_data->call_arrival_count -
  //     sim_data->blocked_call_count)/sim_data->call_arrival_count;

  // printf("Blocking probability = %.5f (Service fraction = %.5f)\n",
	// 1-xmtted_fraction, xmtted_fraction);
 
  

  printf("\n");
}



