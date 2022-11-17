
/*
 * Simulation_Run of the ALOHA Protocol
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/*******************************************************************************/

void
output_blip_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentagedone;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_processed >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentagedone =
      100 * (double) data->number_of_packets_processed/RUNLENGTH;

    printf("%3.0f%% ", percentagedone);

    printf("Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r", 
	   data->number_of_packets_processed, 
	   data->arrival_count);

    fflush(stdout);
  }
}

/**********************************************************************/

void output_results(Simulation_Run_Ptr this_simulation_run)
{
  int i;
  double xmtted_fraction;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(this_simulation_run);

  printf("\n");
  printf("SIMULATION INPUT PARAMS\n");
  printf("Number of stations = %d \n", sim_data->number_of_stations);
  printf("Mean Backoff Duration = %d \n", sim_data->mean_backoff_duration);
  printf("Random Seed = %d \n", sim_data->random_seed);
  printf("\n");
  printf("Pkt Arrivals = %ld \n", sim_data->arrival_count);

  xmtted_fraction = (double) sim_data->number_of_packets_processed /
    sim_data->arrival_count;

  printf("Xmtted Pkts  = %ld (Service Fraction = %.5f)\n",
	 sim_data->number_of_packets_processed, xmtted_fraction);

  printf("Throughput  = %.5f\n",
    (double) sim_data->number_of_packets_processed/simulation_run_get_time(this_simulation_run));

  printf("Mean Delay   = %.1f \n",
	 sim_data->accumulated_delay/sim_data->number_of_packets_processed);

  printf("Mean collisions per packet = %.3f\n",
	 (double) sim_data->number_of_collisions / 
	 sim_data->number_of_packets_processed);

  for(i=0; i<sim_data->number_of_stations; i++) {

    printf("Station %2i Mean Delay = %8.1f \n", i,
	   (sim_data->stations+i)->accumulated_delay / 
	   (sim_data->stations+i)->packet_count);
  }
  printf("\n\n");
}

FILE* create_step5_csv(){
  FILE* fpt = fopen("step6_run_results.csv", "w");
  fprintf(fpt, "number of stations, mean backoff duration, service fraction, mean delay, mean collisions per packet\n");
  return fpt;
}

void write_step5(
  FILE* fpt,
  int number_of_stations, 
  int mean_backoff_duration,
  double acc_service_fraction,
  double acc_mean_delay,
  double acc_mean_collisions_per_packet,
  double acc_throughput,
  int number_of_sims
){
  fprintf(
    fpt,
    "%d, %d, %f, %f, %f %f\n",
    number_of_stations,
    mean_backoff_duration,
    acc_service_fraction/number_of_sims,
    acc_mean_delay/number_of_sims,
    acc_mean_collisions_per_packet/number_of_sims,
    acc_throughput/number_of_sims
  );
}


